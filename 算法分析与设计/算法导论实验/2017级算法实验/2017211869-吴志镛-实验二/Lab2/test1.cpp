#include<stdlib.h>
#include <stdio.h>
int goods[4];//原本想用goods[1/2/3]


int flag[3];//不过可以将goods[1/2/3]作为中间变量转存给flag
			

int w[3] = { 20,15,10 };//物品重量
int v[3] = { 20,30,25 };//物品价值
int c = 25;//背包容量
int value = 0;//储存上一节点的总价值
int weight = 0;//储存上一节点的总重量
int k = 0;//计数器
void Select(int a)
{
	int i = 0;
	if (weight > c) return;
	if (value > goods[0])
		//因为下面的那个循环最后完全循环完毕之后
		//会将value和goods标志位再减回0 
		//所以要在比当前最优还优的时候先记录下来 
	{
		goods[0] = value;
		for (int j = 0; j < 3; j++)
		{
			if (goods[j + 1]) flag[j] = 1;
		}
	}

	for (i = a; i <= 3; i++)
		//一套下来value和goods都置成0了
		//毕竟代码这么对称，先加后减 
		//这个循环最绝妙的地方就是将Select(a)的a作为
		//此循环计数器i的初值，这样就可以直接从上一个节点开始搞
		//尤其是在此节点的下一个节点被剪枝剪掉的时候
		//回溯时就可以直接将a节点回退返回上一层 
	{
		value += v[i];
		weight += w[i];
		goods[i + 1] = 1;

		Select(i + 1);

		value -= v[i];
		weight -= w[i];
		goods[i + 1] = 0;
	}

}
void Print()
{
	printf("选择的物品是：\n");
	for (int j = 0; j < 3; j++)
	{
		if (flag[j])
			printf("物品%d ", j + 1);
	}
	printf("\n总价值：%d", goods[0]);
}
int main()
{
	Select(k);
	Print();
	system("pause");
}
