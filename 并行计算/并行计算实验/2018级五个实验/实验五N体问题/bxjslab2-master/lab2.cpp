// bx2.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<ctime>
#include<vector>
#include "mpi.h"
#pragma comment (lib,"msmpi.lib")
#include<Windows.h>
#pragma comment( lib,"winmm.lib" )
using namespace std;
int vmax = 20;
int max = 10000000;

int carsize = 10;
int timesize = 100;
int p = 25;//0.25
class car
{
public:
	car();
	car(int, int, int, int);
	int v;
	int posi;
};

car::car()
	:v(0), posi(0)
{

}
car::car(int _v, int _posi, int _next, int _back)
	: v(_v), posi(_posi)
{

}
void runtime(int myid, int *point, int cycle, car *gcar,int numprocs,int step)
{
	while (cycle--)
	{
		for (int i = point[myid]; i < point[myid + 1]; i++)//计算速度
		{
			int d;
			if (i == 0) d = max;
			else d = gcar[i - 1].posi - gcar[i].posi;

			if (gcar[i].v < vmax)
				gcar[i].v += 1;
			if (gcar[i].v >= d)
				gcar[i].v = d - 1;
			if ((rand() % 100) < p && gcar[i].v > 0)
				gcar[i].v -= 1;
		}
		for (int i = point[myid]; i < point[myid + 1]; i++)//计算位置
		{
			gcar[i].posi += gcar[i].v;
		}
		MPI_Barrier(MPI_COMM_WORLD);
		for (int i = 0; i < numprocs - 1; i++)//广播每个线程中最后一辆车的位置
		{
			MPI_Bcast(&gcar[(i+1)*step-1].posi, 1, MPI_INT, i, MPI_COMM_WORLD);
		}
		MPI_Barrier(MPI_COMM_WORLD);
	}
}
int main(int argc, char * argv[])
{
	LARGE_INTEGER nFreq;
	LARGE_INTEGER nBeginTime;
	LARGE_INTEGER nEndTime;
	double timeduring;
	QueryPerformanceFrequency(&nFreq);

	srand(time(0));
	int myid, numprocs;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	if (myid == 0)
	{
		cout << "input carsize: "; cin >> carsize;
		cout <<endl<< "input timecycle: "; cin >> timesize;
		cout << endl;
		QueryPerformanceCounter(&nBeginTime);//time start
	}
	MPI_Bcast(&carsize, 1, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Bcast(&timesize, 1, MPI_INT, 0, MPI_COMM_WORLD);

	car *gcar = new car[carsize];
	for (int i = 0; i < carsize; i++)
	{
		gcar[i].posi = -i;
	}
	int point[10] = { 0 };
	int step = carsize / numprocs;
	if (myid == 0)
	{
		for (int i = 0; i < numprocs; i++)
		{
			point[i] = i*step;
		}
		point[numprocs] = carsize;
	}
	MPI_Bcast(&point, numprocs + 1, MPI_INT, 0, MPI_COMM_WORLD);

	//cout << point[myid] << endl;
	MPI_Barrier(MPI_COMM_WORLD);
	runtime(myid, point, timesize, gcar, numprocs,step);


	if (myid == 0)
	{
		QueryPerformanceCounter(&nEndTime);//time end
		timeduring = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;
		cout << "time cost:" << timeduring << "s; " << endl;
		/*for (int i = 0; i < carsize; i++)
		{
			cout << gcar[i].posi << " ";
		}*/
	}


	for (int i = 0; i < numprocs; i++)
	{
		for (int j = point[i]; j < point[i + 1]; j++)
		{
			MPI_Bcast(&gcar[j].posi, 1, MPI_INT, i, MPI_COMM_WORLD);
		}
	}
	MPI_Barrier(MPI_COMM_WORLD);
	if (myid == 0)
	{
		int swit = 0;
		cout << "show car result? yes(1),no(0)" << endl;
		cin >> swit;
		if (swit == 1)
		{
			for (int i = 0; i < carsize; i++)
			{
				cout << gcar[i].posi << " ";
			}
		}
	}
	MPI_Finalize();
	return 0;
}

