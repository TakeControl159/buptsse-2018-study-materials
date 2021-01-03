/*
*算法分析实验一
* 
*蛮力法解决0/1背包问题
*by TY 20181018 
*
*题目设置：由用户输入背包的容量与物品的容量以及
*价格（默认数量为一），然后给出价值最高的组合
*并显示价值 
*
*/
#include<stdio.h>

int n;//物品总个数
int b;//背包承重
int nos;//最优子集的物品数量
int t[50];//记录该子集的物品编号及重量
int sum_v=0,sum_w=0;
 
//定义一个结构体表示物品 
struct goods
{
	int w;
	int v;
	int flag;
} a[100];

//记录当前子集
int record (int sum_v)
{
	int i;
	int count=0;
	t[0]=sum_v;
	for(i=0;i<=n;i++)
	{
		if(a[i].flag)
		t[++count]=i+1;
	}
	return count;
} 

//计算最优解
void super_v(int x)
{
	int i;
	if(sum_w>b)
	return;
	if(sum_v>t[0])
	nos=record(sum_v);
	for(i=x;i<=n;i++)
	{
		sum_v=sum_v+a[i].v;
		sum_w=sum_w+a[i].w;
		a[i].flag=1;
		
		super_v(i+1);
		
		sum_v=sum_v-a[i].v;
		sum_w=sum_w-a[i].w;
		a[i].flag=0;
	}
} 

int main()
{
	int i;
	printf("请输入物品总数： ");
	scanf("%d",&n);
	printf("请输入背包承重： ");
	scanf("%d",&b);
	printf("请输入各个物体的重量以及价值： ");
	for(i=0;i<n;i++)
	{
		scanf("%d %d",&a[i].w,&a[i].v);
		a[i].flag=0;
	} 

super_v(0);

printf("当你选择这几个物品，获得最有价值的子集：\n");
for(i=1;i<=nos;i++)
printf("%d\n",t[i]); 
printf("总价值为 %d\n",t[0]);

}
