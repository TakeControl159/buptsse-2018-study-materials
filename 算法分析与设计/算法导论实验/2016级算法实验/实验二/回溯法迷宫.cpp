/*
*算法分析实验二
*
*回溯法解决迷宫问题
*by TY 20181101
*
*
*/
#include<stdio.h>
#define n1 30//最多行
#define n2 30//最多列
struct migong
{
	int x;                                      	//记录坐标
	int y;                                         	//记录坐标
	int c;  										//方向，1为右，2为上，3为左，4为下，
} top[n1*n2];
int roww,linee;                             	//输出路径时使用
int mapp[100][n1][n2];                          //记录解
int a[100]= {0};                             	//路径步数
int row,line,r,l,ar,al,br,bl,i,j,k;
int n=0;										//解的个数
int xx[100][n1];
int yy[100][n2];								//解的路径

void printbest()
{
	if(n==0)
	{
		printf("该迷宫无解\n");
		return;
	}
	else
		printf("该迷宫有%d个解\n",n);

	int min,t,p,m;
	min=a[0];
	t=0;
	for(p=0; p<n; p++)                         //找出最优解
	{
		if(a[p]<=min)
		{
			t=p;
			min=a[p];
		}
	}
	printf("\n最优解为:\n");
	for(p=0; p<n; p++)
	{
		if(a[p]==min)
		{
			printf("第%d种解:\n",p+1);
			printf("(%d,%d)",xx[p][0],yy[p][0]);
			for(m=1; m<=a[p]; m++)
			{
				printf("->(%d,%d)",xx[p][m],yy[p][m]);
			}
			printf("\n路径为(2代表走过的路):\n");
			for(roww=0; roww<row; roww++)
			{
				for(linee=0; linee<row; linee++)
					printf("%d ",mapp[p][roww][linee]);
				printf("\n");
			}
			printf("\n");
		}
	}
}

int main()
{
	//初始化迷宫
	printf("输入行数和列数:");
	scanf("%d%d", &row, &line);
	int map[n1][n2];
	for(r=0; r<=row; r++)
	{
		for(l=0; l<=line; l++)
			map[r][l]=1;
	}
	printf("请输入地图，以0为路，以1为墙(输完一行后按回车输下一行):\n");
	for (r = 0; r < row; r++)
	{
		for (l = 0; l < line; l++)
		{
			scanf("%d", &map[r][l]);
		}
	}
	printf("输入迷宫入口坐标:");
	scanf("%d%d",&ar,&al);
	printf("输入迷宫出口坐标:");
	scanf("%d%d",&br,&bl);
	printf("\n");
	i=0;
	top[i].x=ar;
	top[i].y=al;
	top[i].c=1;
	do
	{
		if(top[i].c<5)
		{
			if(top[i].x==br&&top[i].y==bl)
			{
				n++;
				map[br][bl]=2;
				printf("第%d种解:\n",n);
				printf("(%d,%d)",top[0].x,top[0].y);
				for(j=1; j<=i; j++)
					printf("->(%d,%d)",top[j].x,top[j].y);
				printf("\n路径为(2代表走过的路):\n");
				for(roww=0; roww<row; roww++)
				{
					for(linee=0; linee<line; linee++)
					{
						printf("%d ",map[roww][linee]);
					}
					printf("\n");
				}
				a[n-1]=i;
				for(k=0; k<=i; k++)
					xx[n-1][k]=top[k].x;
				for(k=0; k<=i; k++)
					yy[n-1][k]=top[k].y;
				for(roww=0; roww<row; roww++)
				{
					for(linee=0; linee<line; linee++)
					{
						mapp[n-1][roww][linee]=map[roww][linee];
					}
					printf("\n");
				}
				map[br][bl]=0;
				printf("\n");
				map[top[i-1].x][top[i-1].y]=0;//回溯
				i--;
				top[i].c++;

			}
			switch(top[i].c)
			{
				case 1:                            //左方向
				{

					if(map[top[i].x][top[i].y+1]==0)
					{
						map[top[i].x][top[i].y]=2;
						i++;
						top[i].x=top[i-1].x;
						top[i].y=top[i-1].y+1;
						top[i].c=1;
					}
					else top[i].c++;
					break;
				}
				case 2:                                       //左方向
				{
					if(map[top[i].x-1][top[i].y]==0)
					{
						map[top[i].x][top[i].y]=2;
						i++;
						top[i].x=top[i-1].x-1;
						top[i].y=top[i-1].y;
						top[i].c=1;
					}
					else top[i].c++;
					break;
				}
				case 3:                                         //上方向
				{
					if(map[top[i].x][top[i].y-1]==0)
					{
						map[top[i].x][top[i].y]=2;
						i++;
						top[i].x=top[i-1].x;
						top[i].y=top[i-1].y-1;
						top[i].c=1;
					}
					else top[i].c++;
					break;
				}
				case 4:                                //下方向

				{
					if(map[top[i].x+1][top[i].y]==0)
					{
						map[top[i].x][top[i].y]=2;
						i++;
						top[i].x=top[i-1].x+1;
						top[i].y=top[i-1].y;
						top[i].c=1;
					}
					else top[i].c++;
					break;
				}
			}
		}
		else//回溯
		{
			if(i==0)
			{
				printbest();
				return  0;
			}
			else
			{
				map[top[i-1].x][top[i-1].y]=0;
				i--;
				top[i].c++;
			}
		}
	}
	while(1);
	return 0;
}


