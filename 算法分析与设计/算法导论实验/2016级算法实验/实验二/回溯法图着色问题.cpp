/*
*算法分析实验二 
* 
*回溯法解决图着色问题 
*by TY 20181101 
*
*题目设置：由用户输入顶点数量和颜色数目并且输入无向图的邻接矩阵最后给出所有着色可能 
*
*/ 

#include "cstdio"
#include "cstring"
int color[500];
bool ok(int k,int c[][100])
{
    for(int i=1;i<k;i++)
    {
        if(c[k][i]==1&&color[i]==color[k])///看已经着色的 与之相连的顶点和他同色与否？
            return false;
    }
    return true;
}
int graphColor(int n,int m,int c[][100])
{
    int cnt=0;
    memset(color,0,sizeof(color));
    int k=1;
    while(k>=1)
    {
        color[k]+=1;///染第一种颜色
        while(color[k]<=m)
        {
            if(ok(k,c))
                break;
            else
                color[k]++;///搜索下一个颜色
        }///挑选合适颜色
        if(color[k]<=m&&k==n)///找完  输出
        {
            for(int i=1;i<=n;i++)
                printf("%d ",color[i]);
            printf("\n");
            cnt++;
        }
        else if(color[k]<=m&&k<n)
        {
            k++;///染下一个顶点
        }
        else
        {
            color[k]=0;///回溯 找其他方法
            k--;
        }
    }
    return cnt;
}
int main()
{
    int n,m,i,j;
    int c[100][100];
    printf("输入顶点数n和着色数m:\n");
    scanf("%d %d",&n,&m);
    printf("输入无向图的邻接矩阵:\n");
    for(i=1;i<=n;i++)
        for(j=1;j<=n;j++)
            scanf("%d",&c[i][j]);
    printf("着色所有可能的解:\n");
    int cnt=graphColor(n,m,c);
    printf("方案数: %d\n",cnt);
}
