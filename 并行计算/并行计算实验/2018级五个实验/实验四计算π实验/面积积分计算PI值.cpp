#include<math.h>
#include<iostream>
#include<random>
#include <ctime>
#include <iomanip>
#include "windows.h"
#include "mpi.h"
using std::cout; using std::endl;


//记录π的值
long double PI = 0.0;
//记录每个进程所计算结果的和
long double ValueSum = 0.0;
//整个计算PI的开始时间与结束时间
long double StartTime, EndTime;
//进程数量,进程ID
int Size, MyID;
//PI计算累加次数,  （可修改用于测试）
long double N = 1e8; 
//实际PI值
long double Actual_PI = 3.141592653589793238462643;


//1.面积积分计算PI值
inline void areaIntegral() {
	long double X;
	//计算矩形宽度
	long double rectangleWide = 1.0 / N;
	//根据进程ID 计算每个矩形的高度,并求和 myid = 0 分配 第1 5 9 14 ... myid = 2 分配 第2 6 10 15... 
	for (int i = MyID + 1; i <= N; i += Size) {       //i = myid* n/size; i<= (myid+1) * n/size; i++也行.   
		X = rectangleWide * ((long double)i - 0.5);       //第i个矩形x坐标            
		ValueSum = ValueSum + (4.0 / (1 + X * X));      //矩形高度累加               
	}
	//计算总面积 长*宽
	ValueSum *= rectangleWide;
}


inline long double arctg(int i, int value)
{
	double result = pow(-1, (i % 2)) / ((2.0 * i + 1.0) * pow(value, 2 * i + 1));
	return result;
}

//2.幂级数(MyID + 1) * N / Size
inline void powerSeries() {
	for (long double i = MyID * N / Size; i < (MyID + 1) * N / Size; i++)
		ValueSum += arctg((int)i, 1);
			
	ValueSum *= 4;
}


//3.改进的幂级数
inline void powerSeriesImprove()
{
	for (long double i = MyID * N / Size; i < (MyID + 1) * N / Size; i++)
		ValueSum += 4 * arctg((int)i,5) - arctg((int)i, 239);

	ValueSum *= 4;
}

//4.蒙特卡洛的方式
inline void MonteCarlo()
{
	long double randomFrequency = N / Size;
	long double count = 0.0;
	long double x, y;

	for (int i = 0; i < randomFrequency; i++)
	{
		x = rand() / double(RAND_MAX); //产生随机数0~1
		y = rand() / double(RAND_MAX);
		if (sqrt(x * x + y * y) <= 1)
			count++;
	}
	ValueSum = 4.0 * count / (randomFrequency * Size);
}

//5.随机积分的方法
inline void powerSeriesIm()
{
	long double randomFrequency = N / Size;
	long double X = 0.0;
	long double rectangleWide = 1.0 / N;
	for (int i = 0; i < randomFrequency; i++)
	{
		X = rand() / double(RAND_MAX);  //产生随机数0~1
		ValueSum = ValueSum + (4.0 / (1.0 + X * X));//矩形高度累加
	}
	// 计算面积 长*宽
	ValueSum *= rectangleWide;
}

//6.金田康正算法
inline void JinTianKangZheng()
{
	for (long double i = ceil(MyID * N / Size); i < ceil((MyID + 1) * N / Size); i++)
	{
		ValueSum += 12 * arctg((int)i, 49) + 32 * arctg((int)i, 57) - 5 * arctg((int)i, 239) + 12 * arctg((int)i, 110443);
	}
	ValueSum *= 4;
}

inline long double fac(int n)
{
	long double sum = 1;
	for (int i = 1; i <= n; i++)
		sum *= i;
	return sum;
}

//7.Chudnovsky算法
inline void Chudnovsky()
{
	long double part1 = 0;
	long double part2 = 0;
	long double P61 = sqrt(61);
	long double A = 1657145277365 + 212175710912 * P61;
	long double B = 107578229802750 + 13773980892672 * P61;
	long double C = 5280 * (236674 + 30303 * P61);

	for (int i = (int)(MyID * N / Size); i < (MyID + 1) * N / Size; i++)
	{
		part1 = pow(-1, (i % 2)) * fac(6 * i) / 3.0 * fac(i) * pow(fac(i), 3);
		part2 = A * i + B / pow(C, 3 * i + 1.5);
		cout << "part1:" << part1 << "   part2:" << part2 << endl;
		ValueSum += part1 * part2;
	}
	ValueSum *= 12;
	ValueSum = 1/ValueSum;
}


int main(int argc, char* argv[]) {
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &MyID);
	MPI_Comm_size(MPI_COMM_WORLD, &Size);
	cout << "进程" << MyID << "启动" << endl;

	if (0 == MyID) { StartTime = MPI_Wtime(); 	srand((int)time(0));}
	MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);  //将N广播到所有进程中
	//1.面积积分计算PI值 测试N的范围 1e3~1e7
	areaIntegral();

	//2.幂级数积分计算PI值 测试N的范围 1e3~1e7
	//powerSeries();

	//3.改进幂级数 测试N的范围 1e3~1e7
	//powerSeriesImprove()

	//4.蒙特卡洛计算PI值 测试N的范围 1e3~1e7
	//MonteCarlo();

	//5.随机积分的方法 测试N的范围 1e3~1e7
	//powerSeriesIm();

	//6.金田康正算法 测试N的范围 2~10
	//JinTianKangZheng()

	//7.Chudnovsky算法 测试N的范围 1~5
	//Chudnovsky();

	//利用Reduce函数将所有进程的ValueSum累加到root进程(0)的PI变量当中
	MPI_Reduce(&ValueSum, &PI, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);  


	if (0 == MyID) {
		EndTime = MPI_Wtime();
		auto deviation = PI - Actual_PI;
		cout << endl;
		cout << "计算的PI值为:" << std::setprecision(24) << PI << endl;
		cout << "实际的PI值为:" << Actual_PI << endl;
		cout << "PI的误差为:" << std::setprecision(24) << deviation << endl;
		cout << "总共用时为:" << EndTime - StartTime << endl;
	}
	MPI_Finalize();
	return 0;
}