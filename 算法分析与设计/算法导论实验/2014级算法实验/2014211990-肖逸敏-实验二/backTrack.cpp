#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#define N 100

struct goods
{
	int wight;
	int value;
	int sign;
}good[N];

int n;//总的种类数量
int maxValue, maxWight;//最大价值，最大重量
int cw, cv;//目前的重量，目前的价值
int X[N], cx[N];//最优路径，当前路径

int BackTrack(int i)
{
	if (i > n - 1)//把所有物品都加进去之后
	{
		if (maxValue < cv)
		{
			for (int k=0; k < n; k++)
				X[k] = cx[k];
			maxValue = cv;
		}
		return maxValue;
	}
	if (cw + good[i].wight <= maxWight)//进入左子树
	{
		cw = cw + good[i].wight;
		cv = cv + good[i].value;
		cx[good[i].sign] = 1;//装入为1
		BackTrack(i + 1);
		cw -= good[i].wight;//回溯进入右子树
		cv -= good[i].value;
	}
	cx[good[i].sign] = 0;//不装入为0
	BackTrack(i + 1);
}

int BackPack(int n,goods good[],int maxWight,int x[])
{
	for (int i = 0; i < n; i++)//初始化
	{
		x[i] = 0;
		good[i].sign = i;
	}
	BackTrack(0);
	return maxValue;
}

int main()
{
		printf("物品种数n: ");
		scanf("%d", &n);	//输入物品种数
		printf("背包容量C: ");
		scanf("%d", &maxWight);	//输入背包容量
		for (int i = 0; i<n; i++)	//输入物品i的重量w及其价值v
		{
			printf("物品%d的重量w[%d]及其价值v[%d]:  ", i + 1, i + 1, i + 1);
			scanf("%d%d", &good[i].wight, &good[i].value);
		}
		int sum = BackPack(n, good, maxWight, X);//调用回溯法求0/1背包问题
		printf("回溯法求解0/1背包问题:\nX=[ ");
		for (int i = 0; i<n; i++)
			cout << X[i] << " ";//输出所求X[n]矩阵
		printf("]	装入总价值%d\n", sum);
		system("pause");
		return 0;
	}
