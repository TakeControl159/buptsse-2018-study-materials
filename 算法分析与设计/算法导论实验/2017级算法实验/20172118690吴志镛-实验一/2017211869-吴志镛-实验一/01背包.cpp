#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;

int n;//物品总个数
int b;//背包承重
int nos;//最优子集的物品数量
int t[50];//记录该子集的物品编号及重量
int sum_v = 0, sum_w = 0;


class goods
{
public:
	int weight;
	int value;
	int flag;
	goods();
	~goods();

private:

};

goods::goods()
{
}

goods::~goods()
{
}

goods goodlist[100];

//记录当前子集
int record(int sum_v)
{
	int i;
	int count = 0;
	t[0] = sum_v;
	for (i = 0; i <= n; i++)
	{
		if (goodlist[i].flag)
			t[++count] = i + 1;
	}
	return count;
}

//计算最优解
void findbest(int x)
{
	int i;
	if (sum_w > b)
		return;
	if (sum_v > t[0])
		nos = record(sum_v);
	for (i = x; i <= n; i++)
	{
		sum_v = sum_v + goodlist[i].value;
		sum_w = sum_w + goodlist[i].weight;
		goodlist[i].flag = 1;

		findbest(i + 1);

		sum_v = sum_v - goodlist[i].value;
		sum_w = sum_w - goodlist[i].weight;
		goodlist[i].flag = 0;
	}
}

int main()
{
	int i;
	printf("请输入物品总数： ");
	cin >> n ;
	printf("请输入背包承重： ");
	cin >> b;
	printf("请输入各个物体的重量以及价值： ");
	for (i = 0; i < n; i++)
	{
		cin>>goodlist[i].weight>>goodlist[i].value;
		
		goodlist[i].flag = 0;
	}

	findbest(0);

	printf("当你选择这几个物品，获得最有价值的子集：\n");
	for (i = 1; i <= nos; i++)
		printf("%d\n", t[i]);
	printf("总价值为 %d\n", t[0]);
	system("pause");

}
/*
7 42
3 12
4 40
5 25
*/