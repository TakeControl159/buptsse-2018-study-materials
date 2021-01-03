#include <iostream>
#include <stdlib.h>
#include <stdio.h>
int n; 
int c[1000][1000];
unsigned int mincost = 100000; //设置的初始值,大于可能的成本 
int task[1000],temp[1000],worker[1000];
int main()
{ 
	void Plan(int k,unsigned int cost);
	int i,j;	 
	printf("请输入任务数和人数:");
	scanf("%d%d",&n,&n);
	printf("输入每个人完成各个任务的成本矩阵:\n");  
	for(i=0;i<n;i++)
	{  
	    /*task[i]:值为0表示任务i未分配,值为j表示任务i分配给人员j;
	      worker[k]:值为0表示人员k未分配任务,值为1表示人员k已分配任务;*/
	      worker[i] = 0;  
	      task[i]   = 0; 
	      temp[i]   = 0; 
	      for(j=0;j<n;j++) 
		  scanf("%d",&c[i][j]);
	} 
	Plan(0,0);    //从任务0开始分配
	printf("最小总费用:%d\n",mincost);
	for(i=0;i<n;i++)
		printf("人员:%d执行任务:%d\n",i+1,temp[i]+1);
	
	return 0;
} 
void Plan(int k,unsigned int cost)
{
	int i; 
	if(k>=n && cost<mincost) 
	{
		mincost = cost;   
		for(i=0;i<n;i++)  
			temp[i] = task[i]; //人员i完成任务temp[i] 
	}
	else 
	{ 
		for(i=0;i<n;i++) 
		{ 
			//分配任务k  
			if(worker[i]==0) 	
			{ worker[i] = 1;
			  task[k] = i;
			  Plan(k+1,cost+c[k][i]); 
			  worker[i] = 0; 
			  task[k] = 0;  
			}  
		} 
	}
}

