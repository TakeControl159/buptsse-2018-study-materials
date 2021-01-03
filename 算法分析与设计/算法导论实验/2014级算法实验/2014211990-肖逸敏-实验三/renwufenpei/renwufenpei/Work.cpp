#include "Work.h"
#include <iostream>
#include <fstream>
using namespace std;

Work::Work()
{
	init();
}

Work::~Work()
{

}
void Work::init()
{
	count = 0;
	cc = 0;
	minc = 1000;
	int i, j;
	char fname[256];
	cout << "请输入文件名:" << endl;
	cin >> fname;
	ifstream in(fname, ios_base::in);
	if (!in)
	{
		cout << "无法找到该文件!" << endl;
		exit(0);
	}
	in >> n;
	work = new int[n];
	for (i = 0; i<n; i++)
		work[i] = i;
	c = new int*[n];
	for (i = 0; i<n; i++)
		c[i] = new int[n];
	tmp = new int[n];
	for (i = 0; i<n; i++)
		tmp[i] = 0;
	while (in)
	{
		for (i = 0; i<n; i++)
			for (j = 0; j<n; j++)
				in >> c[i][j];
	}
	in.close();
	showArray();
	cout << endl;
	highest = getHighest();
	cout << "highest:" << highest << endl;
}
int Work::getHighest()
{
	int i, j, min, loc, sum, flag, k, p;
	sum = 0;
	bool *b = new bool[n];
	for (i = 0; i<n; i++)
		b[i] = false;
	for (i = 0; i<n; i++)
	{
		//cout<<"i:"<<i<<endl;
		flag = 0;
		min = c[i][0];
		for (j = 0; j<n; j++)
		{
			if (c[i][j] <= min&&b[j] == false)
			{
				loc = j;
				min = c[i][j];
				flag++;
			}
			if (b[j] == false)
				k = j;
		}
		//cout<<"flag:"<<flag<<"k:"<<k<<endl;
		if (flag == 0)
			sum += c[i][k];
		//cout<<loc<<endl;
		if (b[loc] == false)
		{
			sum += min;
			b[loc] = true;
			//cout<<"aaa:"<<sum<<endl;
		}
	}
	return sum;
}
void Work::showArray()
{
	int i, j;
	cout << "work:" << endl;
	for (i = 0; i<n; i++)
		cout << work[i] << "  ";
	cout << endl << "c:" << endl;
	for (i = 0; i<n; i++)
	{
		for (j = 0; j<n; j++)
			cout << c[i][j] << "  ";
		cout << endl;
	}
}
void Work::show()
{
	for (int i = 0; i<n; i++)
		cout << work[i] << "  ";
	cout << endl;
}
void Work::swap(int &a, int &b)
{
	int tmp;
	tmp = a;
	a = b;
	b = tmp;
}
void Work::find(int i)
{

	if (i >= n)
	{
		if (cc<minc)
		{
			minc = cc;
			cout << minc << endl;
			for (int k = 0; k<n; k++)
				tmp[k] = work[k] + 1;
			return;
		}
	}
	for (int j = i; j<n; j++)
	{
		if (cc<minc)
		{
			swap(work[i], work[j]);
			cc += c[i][work[i]];
			//cout<<"cc:"<<cc<<endl;

			if (cc <= highest)
			{
				count++;
				find(i + 1);
			}
			cc -= c[i][work[i]];
			swap(work[j], work[i]);
			//cout<<"new cc:"<<cc<<endl;
		}
	}
}
void Work::output()
{
	cout << "count:" << count << endl;
	cout << "总共所需最短时间: " << minc << endl;
	cout << endl << "分配:" << endl;
	for (int i = 0; i<n; i++)
		cout << tmp[i] << "  ";
	cout << endl;
}