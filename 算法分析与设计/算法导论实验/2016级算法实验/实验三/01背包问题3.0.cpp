/*
*
*分支限界法求解01背包问题 
*
*BY Tian Yu 2018 11 22
*
*
*
*/
#include<stdio.h>
#include<windows.h> 

int n;//物品总个数
int b;//背包承重
int nos;//最优子集的物品数量
int t[50];//记录该子集的物品编号及重量
int sum_v=0,sum_w=0;
int state;//算法选择 
 
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
void super_vWithMLF(int x)
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
		
		super_vWithMLF(i+1);
		
		sum_v=sum_v-a[i].v;
		sum_w=sum_w-a[i].w;
		a[i].flag=0;
	}
} 

void super_vWithHSF(int x)
{
	if(x>=n){
		if(sum_v>t[0])
		nos=record(sum_v);
		return;
	}
	else if(sum_w+a[x].w<=b)
	{
		a[x].flag=1;
		sum_v=sum_v+a[x].v;
		sum_w=sum_w+a[x].w;
		super_vWithHSF(x+1);
		sum_v=sum_v-a[x].v;
		sum_w=sum_w-a[x].w;
		a[x].flag=0;
		super_vWithHSF(x+1);
	}
	else{
		a[x].flag=0;
		super_vWithHSF(x+1);
	}
}

void super_vWithFZF(int x)
{
	
}

int main()
{
	int i;
	printf("请输入物品总数： ");
	scanf("%d",&n);
	printf("请输入背包承重： ");
	scanf("%d",&b);
	printf("请输入各个物体的重量： ");
	for(i=0;i<n;i++)
	{
		scanf("%d %d",&a[i].w,&a[i].v);
		a[i].flag=0;
	} 
	printf("请选择算法：\n");
	printf("1.蛮力法；2.回溯法 ;3.分支法\n"); 
	scanf("%d",&state);
	
	switch(state)
	{
		case 1:super_vWithMLF(0);
		case 2:super_vWithHSF(0);
		case 3:super_vWithFZF(0); 
	}


printf("当你选择这几个物品，获得最有价值的子集：\n");
for(i=1;i<=nos;i++)
printf("%dth\n",t[i]); 
printf("总价值为 %d\n",t[0]);

}
