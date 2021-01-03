#include<stdio.h>
int c[10][100];
int knapsack(int m,int n)
{
 int i,j,w[10],p[10];
 printf("请输入每个物品的重量,价值：\n");
 for(i=1;i<=n;i++)
        scanf("%d %d",&w[i],&p[i]);
 for(i=0;i<10;i++)
      for(j=0;j<100;j++)
           c[i][j]=0;
 for(i=1;i<=n;i++)
      for(j=1;j<=m;j++)
           {
            if(w[i]<=j) 
                     {
                      if(p[i]+c[i-1][j-w[i]]>c[i-1][j])
                            c[i][j]=p[i]+c[i-1][j-w[i]];
                            else
                            c[i][j]=c[i-1][j];
                     }
              else c[i][j]=c[i-1][j];
            }
 return(c[n][m]);
                     
}
int main()
{
    int m,n,v;int i,j;
	printf("请输入物品的个数：\n");
    scanf("%d",&n);
    printf("请输入背包承重量：\n");
    scanf("%d",&m);
    
	v=knapsack(m,n);
    printf("总价值最大为%d",v);
    printf("\n");
    return 0;
}
