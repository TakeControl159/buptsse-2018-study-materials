
#include<iostream>
#include<cstdio>
using namespace std;

int f[11][11] = { 0 }, w[11], p[11];//假设控制最大的数量在10个物品以内,质量在10以内
void knap9(int m, int n)
{
	int i = 0, j = 0;
	//初始化
	for (j = 0; j <= m; ++j)
	{
		f[n][j] = 0;
	}
	//将第n个物品加入
	for (j = w[n]; j <= m; ++j)
	{
		f[n][j] = p[n];
	}
	//进行动态规划
	for (i = n - 1; i > 1; --i)
	{
		//考虑不加次物品进去的情况
		for (j = 0; j <= m; ++j)
		{
			f[i][j] = f[i + 1][j];
		}
		//将此物品加入其中
		for (j = w[i]; j <= m; ++j)
		{
			if (f[i + 1][j] > f[i + 1][j - w[i]] + p[i])
				f[i][j] = f[i + 1][j];
			else
				f[i][j] = f[i + 1][j - w[i]] + p[i];
		}
	}
	if (m >= w[1])
	{
		if (f[1][m] > f[2][m - w[1]] + p[1])
			f[1][m] = f[2][m];
		else
			f[1][m] = f[2][m - w[1]] + p[1];
	}
}
int main()
{
	int m, n, i, s;
	int currw, currp;
	cout << "请输入背包的最大容量:";
	cin >> m;
	cout << "请输入物品的个数:";
	cin >> n;
	//初始化物品的质量和利润
	n = n - 1;
	i = 1;
	s = 0;
	cout << "请输入质量和利润:";
	cin >> currw >> currp;
	while (i <= n && currw > 0 && currp > 0)
	{
		s = s + currw;
		if (currw <= m)
		{
			w[i] = currw;
			p[i] = currp;
			i = i + 1;
		}
		else
		{
			cout << "物品质量超过背包容量!不处理" << endl;
		}
		cout << "请输入质量和利润:";
		cin >> currw >> currp;
	}
	if (s <= m)
	{
		cout << "whloe choose" << endl;
		return 0;
	}
	knap9(m, n);
	printf("The max value is %d\n", f[1][m]);


	system("pause");

}
/*
10
5
2 3
4 5
2 6
3 5
4 2
*/