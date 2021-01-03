#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

void main()
{
	int i, j, k, p, q, x, y;
	int N, K, A, B, C;
	int map[81][81];//记录各个点的信息
	int cost[81][81][10];
	int min;
	int s[4][3];//4种行走方式
	FILE *fp;
	//从输入文件中读数据
	fp = fopen("input.txt", "rt");
	fscanf(fp, "%d%d%d%d%d", &N, &K, &A, &B, &C);
	for (i = 1; i <= N; i++)
		for (j = 1; j <= N; j++)
			fscanf(fp, "%d", &map[i][j]);
	fclose(fp);

	//初始化行走方式的数组
	s[0][0] = -1;
	s[0][1] = 0;
	s[0][2] = 0;

	s[1][0] = 0;
	s[1][1] = -1;
	s[1][2] = 0;

	s[2][0] = 1;
	s[2][1] = 0;
	s[2][2] = B;

	s[3][0] = 0;
	s[3][1] = 1;
	s[3][2] = B;

	for (i = 1; i <= N; i++)
		for (j = 1; j <= N; j++)
			for (k = 0; k <= K + 1; k++) //注意这里！！！！
				cost[i][j][k] = 10000;
	//走到1,1点的费用为0
	for (k = 0; k <= K; k++)
		cost[1][1][k] = 0;
	y = 1;

	while (y != 0)//修改的行数，当y等于0时说明所有数据为最优数据，跳出循环
	{
		//printf("%d\n",y);
		y = 0;
		for (i = 1; i <= N; i++)
		{
			for (j = 1; j <= N; j++)
			{
				if (i != 1 || j != 1) //i,j同时为0时跳到下一次循环
				{
					for (p = 0; p <= K; p++)//剩余的油量

					{
						min = 10000;
						for (q = 0; q<4; q++)//4种走法
						{
							if ((i == 1 && q == 0) || (j == 1 && q == 1) || (i == N&&q == 2) || (j == N&&q == 3))//边界情况
								continue;
							if (cost[i + s[q][0]][j + s[q][1]][p + 1] + s[q][2]<min)
								min = cost[i + s[q][0]][j + s[q][1]][p + 1] + s[q][2];
						}

						if (min<10000)//说明有路可以走过去
						{
							if (cost[i][j][p]>min + A*map[i][j]) //花费等于min+A*map[i][j]是合理情况，不合理情况时y++ 用来做标记
								y++;

							cost[i][j][p] = min;
							if (map[i][j] == 1)
							{
								cost[i][j][0] += A;
								for (x = 1; x <= K; x++)
									cost[i][j][x] = cost[i][j][0];
								break;
							}
						}
						else //没有路可以过去
						{
							cost[i][j][p] = cost[i][j][0] + C + A;
							for (x = p + 1; x <= K; x++)
								cost[i][j][x] = cost[i][j][p];
							break;
						}
					}
				}
			}
		}
	}
	fp = fopen("output.txt", "w");
	fprintf(fp, "%d\n", cost[N][N][0]);
	fclose(fp);
	system("pause");

}