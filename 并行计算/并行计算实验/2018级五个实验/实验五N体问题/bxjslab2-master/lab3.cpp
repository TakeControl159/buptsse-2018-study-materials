

#include "stdafx.h"
#include<iostream>
#include<ctime>
#include<vector>
#include "mpi.h"
#pragma comment (lib,"msmpi.lib")
#include<Windows.h>
#pragma comment( lib,"winmm.lib" )
#include<memory>
using namespace std;
const double G = 6.67E-7;//cm
const double M = 10000;
const double deltatime = 0.01;
const int nsize = 256;
const int mapsize = sqrt(nsize);
const int tmapsize = 30;
int map[tmapsize][tmapsize] = { 0 };
class vet
{
public:
	vet();
	vet(double,double);
	double get2Value();
	void setVet(double, double);
	void showxy();
	double getx() { return x; };
	double gety() { return y; };
	void setx(double _x) { x = _x; };
	void sety(double _y) { y = _y; };
	vet &operator+(const vet&);
	vet &operator-(const vet&);
	vet &operator*(double);
	vet px(double);
private:
	double x;
	double y;
};

vet::vet():x(0),y(0)
{
}
vet::vet(double _x,double _y) : x(_x), y(_y)
{
}
void vet::setVet(double _x, double _y)
{
	x = _x;
	y = _y;
}
double vet::get2Value()
{
	return x*x + y*y;
}
void vet::showxy()
{
	cout << "(" << x << "," << y << "),";
}
vet &vet::operator+(const vet &rt)
{
	vet result(x + rt.x, y + rt.y);
	return result;
}
vet &vet::operator-(const vet &rt)
{
	vet result(x - rt.x, y - rt.y);
	return result;
}
vet &vet::operator*(double scale)
{
	vet result(x*scale, y*scale);
	return result;
}
vet vet::px(double val)//加速度的矢量分配
{
	vet result(0,0);
	double d = sqrt(x*x + y*y);
	if (d == 0)
		return result;
	else
	{
		result.setVet(val / d*x, val / d*y);
		return result;
	}
}

class ball
{
public:
	ball(void);
	ball(vet,vet,vet);
	static void init(int);
	vet getposi() { return posi; };
	void compute_force(int,int,int,double);
	void compute_velocities();
	void compute_positions();
	void showball();
private:
	vet posi;
	vet velo;
	vet forc;
}gball[nsize];
ball::ball():posi(0,0),velo(0,0),forc(0,0)
{
}
ball::ball(vet _p,vet _v,vet _f) 
	: posi(_p), velo(_v), forc(_f)
{
}
void ball::init(int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			gball[i*n + j].posi.setVet(i, j);
		}
	}
}
void ball::compute_force(int ni,int np, int myid,double step)
{
	vet sumforce(0, 0);
	for (int i = myid * step; i < (myid+1) * step; i++)//在这里并行化ok
	{
		vet distance = gball[i].posi - gball[ni].posi;
		sumforce = sumforce + distance.px(G*M / distance.get2Value());
	}
	double ax = sumforce.getx();
	double ay = sumforce.gety();
	double bx = 0;
	double by = 0;
	MPI_Reduce(&ax, &bx, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
	MPI_Reduce(&ay, &by, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
	forc.setx(bx);
	forc.sety(by);
}
void ball::compute_velocities()//计算速度
{
	vet vtemp = forc * deltatime;
	velo = velo + vtemp;
}
void ball::compute_positions()//计算位置
{
	vet ptemp = velo * deltatime;
	posi = posi + ptemp;
}
void ball::showball()
{
	posi.showxy();
}
int main(int argc, char * argv[])
{
	int myid, numprocs;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	int timeclock = clock();
	double t = 5;
	ball::init(mapsize);
	while (t>0)
	{
		t -= deltatime;
		int step = nsize / numprocs;
		for (int i = 0; i < nsize; i++)
		{
			gball[i].compute_force(i, numprocs,myid,step);//计算力(加速度)
		}
		MPI_Barrier(MPI_COMM_WORLD);
		for (int i = 0; i < nsize; i++)
		{
			gball[i].compute_velocities();//计算速度
			gball[i].compute_positions();//计算位置
		}
	}
	if (myid == 0)
	{
		cout << " time cost:" << (double)(clock() - timeclock) / 1000 << endl;
	}
	/*if (myid == 0)
	{
		for (int i = 0 ; i< mapsize; i++)
		{
			for (int j = 0; j < mapsize; j++)
			{
				gball[i*mapsize + j].showball();
			}
			cout << endl;
		}
		cout << " time cost:" << (double)(clock() - timeclock)/1000 << endl;
	}*/
	MPI_Finalize();
	return 0;
}

