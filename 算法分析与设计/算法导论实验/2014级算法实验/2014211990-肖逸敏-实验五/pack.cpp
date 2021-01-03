/*
*
*实验五 动态规划解决01背包问题
*
*BY TianYu
*
*2018 12 20
*
*
*/

#include<stdio.h>
int bag_w, num;
int goods_v[5], goods_w[5];
int bag_v[5][11];
void Start()
{
	printf("请输入背包容量：");
	scanf("%d", &bag_w);
	printf("请输入物品数目：");
	scanf("%d", &num);
	printf("请分别输入每个物品的价值：\n");
	for (int i = 1; i <= num; i++)
	{
		scanf("%d", &goods_v[i]);
	}
	printf("请分别输入每个物品的体积：\n");
	for (int j = 1; j <= num; j++)
	{
		scanf("%d", &goods_w[j]);
	}
}

void Max()
{
	for (int i = 1; i <= num; i++)
	{
		for (int j = 1; j <= bag_w; j++)
		{
			if (j<goods_w[i])//装不进去
			{
				bag_v[i][j] = bag_v[i - 1][j];
			}
			else //可以装 
			{
				//不装价值大 
				if (bag_v[i - 1][j]>bag_v[i - 1][j - goods_w[i]] + goods_v[i])
				{
					bag_v[i][j] = bag_v[i - 1][j];
				}
				//前i-1个物品的最优解与第i个物品的价值之和更大
				else
				{
					bag_v[i][j] = bag_v[i - 1][j - goods_w[i]] + goods_v[i];
				}
			}
		}
	}
}

int item[5];

void Find(int i, int j)
{
	if (i >= 0)
	{
		if (bag_v[i][j] == bag_v[i - 1][j])//相等说明没装
		{
			item[i] = 0;//全局变量，标记未被选中
			Find(i - 1, j);
		}
		else if (j - goods_w[i] >= 0 && bag_v[i][j] == bag_v[i - 1][j - goods_w[i]] + goods_v[i])
		{
			item[i] = 1;//标记已被选中
			Find(i - 1, j - goods_w[i]);//回到装包之前的位置
		}
	}
}

void Print()
{
	printf("最终最大价值为：%d", bag_v[num][bag_w]);
	printf("\n分别是物品：\n");
	for (int i = 1; i <= num; i++)
	{
		if (item[i] != 0)
			printf("第%d个商品\n", i);
	}
}

int main()
{
	Start();
	Max();
	Find(num, bag_w);
	Print();
	return 0;
}