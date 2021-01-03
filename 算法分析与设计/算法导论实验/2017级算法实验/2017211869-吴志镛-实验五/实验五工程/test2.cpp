#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<string.h>
using namespace std;
//类似于01背包问题(当前状态下选与不选取最大)
int dp[1005];
struct node
{
	int s, e, v;
}a[1005];
bool cmp(node a, node b)
{
	if (a.s == b.s) return a.e < b.e;
	return a.s < b.s;
}
int m, r;
int main()
{

	printf("请输入区间调度的数量和重启间隔时间：");
	cin  >> m >> r;

	for (int i = 0; i < m; i++) {
		printf("请输入区间的开始时间，结束时间和权值");
		cin >> a[i].s >> a[i].e >> a[i].v;
	}
	sort(a, a + m, cmp);
	for (int i = 0; i < m; i++)
	{
		dp[i] = a[i].v;
		for (int j = 0; j <= i; j++)
		{
			if (a[j].e + r <= a[i].s)
				dp[i] = max(dp[i], dp[j] + a[i].v);//转移方程：i是枚举每一个区间,每一次外层循环
				//求出来枚举这个区间情况下的最大效益（内存循环控制这个区间之前的不冲突的区间）
				//也就是dp[i]代表枚举这个区间当前最大效益和
		}
	}
	int res = 0;
	for (int i = 0; i < m; i++)
		res = max(res, dp[i]);

	cout<<"最大收益为：" << res;

	system("pause");
	return 0;
}

/*
6 0
0 1 2
2 3 5
4 5 7
7 8 10
5 7 9
5 9 5
*/
