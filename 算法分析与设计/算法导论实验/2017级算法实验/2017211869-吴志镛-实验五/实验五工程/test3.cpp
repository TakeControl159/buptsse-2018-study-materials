#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
#include<cstring>
#include<stdlib.h>
int min(int x, int y)
{
	return x < y ? x : y;
}
int f[2][105][105][12];//第一维滚动 二三维坐标 第四维是还剩多少油
int g[105][105];
int ans = 0x7fffffff;
int main()
{
	memset(f, 0x3f, sizeof(f));
	int n, k, a, b, c;
	scanf("%d%d%d%d%d", &n, &k, &a, &b, &c);
	f[0][1][1][k] = 0;//初始化
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			scanf("%d", &g[i][j]);
	int up = 33333 / n;
	for (int t = 1; t <= up; t++)//这是一个不爆时间的范围
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
			{
				if (g[i][j] == 0)//没有强制消费
				{
					for (int l = 1; l <= k; l++)
					{
						f[t & 1][i][j][l - 1] = 0x3f3f3f3f;//滚动数组优化时间（也可以不用这一行，因为越到后面越费钱）
						if (i > 1)
							f[t & 1][i][j][l - 1] = min(f[t & 1][i][j][l - 1], f[t & 1 ^ 1][i - 1][j][l]);
						if (i < n)
							f[t & 1][i][j][l - 1] = min(f[t & 1][i][j][l - 1], f[t & 1 ^ 1][i + 1][j][l] + b);
						if (j > 1)
							f[t & 1][i][j][l - 1] = min(f[t & 1][i][j][l - 1], f[t & 1 ^ 1][i][j - 1][l]);
						if (j < n)
							f[t & 1][i][j][l - 1] = min(f[t & 1][i][j][l - 1], f[t & 1 ^ 1][i][j + 1][l] + b);
						if (i == j && j == n)//更新答案
							ans = ans < f[t & 1][i][j][l - 1] ? ans : f[t & 1][i][j][l - 1];
					}
					if (i > 1)
						f[t & 1][i][j][k] = min(f[t & 1][i][j][k], f[t & 1 ^ 1][i - 1][j][1] + c + a);
					if (i < n)
						f[t & 1][i][j][k] = min(f[t & 1][i][j][k], f[t & 1 ^ 1][i + 1][j][1] + c + a + b);
					if (j > 1)
						f[t & 1][i][j][k] = min(f[t & 1][i][j][k], f[t & 1 ^ 1][i][j - 1][1] + c + a);
					if (j < n)
						f[t & 1][i][j][k] = min(f[t & 1][i][j][k], f[t & 1 ^ 1][i][j + 1][1] + c + a + b);
					if (i == j && j == n)
						ans = ans < f[t & 1][i][j][k] ? ans : f[t & 1][i][j][k];
				}
				else//有强制消费
				{
					for (int l = 1; l <= k; l++)
					{
						if (i > 1)
							f[t & 1][i][j][k] = min(f[t & 1][i][j][k], f[t & 1 ^ 1][i - 1][j][l] + a);
						if (i < n)
							f[t & 1][i][j][k] = min(f[t & 1][i][j][k], f[t & 1 ^ 1][i + 1][j][l] + a + b);
						if (j > 1)
							f[t & 1][i][j][k] = min(f[t & 1][i][j][k], f[t & 1 ^ 1][i][j - 1][l] + a);
						if (j < n)
							f[t & 1][i][j][k] = min(f[t & 1][i][j][k], f[t & 1 ^ 1][i][j + 1][l] + a + b);
					}
				}
			}
	printf("%d\n", ans);

	system("pause");
	return 0;
}

/*?
9 3 2 3 6
0 0 0 0 1 0 0 0 0
0 0 0 1 0 1 1 0 0
1 0 1 0 0 0 0 1 0
0 0 0 0 0 1 0 0 1
1 0 0 1 0 0 1 0 0
0 1 0 0 0 0 0 1 0
0 0 0 0 1 0 0 0 1
1 0 0 1 0 0 0 1 0
0 1 0 0 0 0 0 0 0
*/

/*

*/