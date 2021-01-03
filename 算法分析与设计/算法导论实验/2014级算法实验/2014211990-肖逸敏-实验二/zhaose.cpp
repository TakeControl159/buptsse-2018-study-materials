#define _CRT_SECURE_NO_WARNINGS
#include<iostream> 
using namespace std; 

int color[100];
bool Ok(int k, int c[][100])   //判断顶点k的着色是否发生冲突 
{ 
for (int i = 1; i<k; i++)
	if (c[k][i] == 1 && color[i] == color[k]) //相连且颜色相同时为false              
		return false;      
return true;   
}
	
void GraphColor(int n, int m, int c[][100])      //所有数组下标从1开始，n为顶点数，m为着色数
{   
		for (int i = 1; i <= n; i++)     //将数组color[n]初始化为0         
			color[i]=0;        
		int k=1;        
		while (k>=1)        
		{ 
			color[k] = color[k] + 1;          
			while (color[k] <= m)                
				if (Ok(k, c))     
					break;                
				else      
					color[k] = color[k] + 1;   //搜索下一个颜色          
			if (color[k]<=m && k==n) //求解完毕，输出解          
			{ 
				for (int i = 1; i <= n; i++)                   
					cout << color[i];        //输出结果       
				return;           
			}
		  else if (color[k] <= m && k<n)
		  {
			  k = k + 1;             //处理下一个顶点                       
			  color[k]=0;
		  }          
		  else  
			  k = k - 1;    //回溯           
		}   
} 

			  
int main(){
	//无向图的邻接矩阵
	int e[5][5]={
	{0,1,1,0,0},     
	{1,0,1,1,1},      
	{1,1,0,0,1},      
	{0,1,0,0,1},      
	{0,1,1,1,0}
	};  

	int i, j;
	int n=5, m=3;
	int c[100][100];//存储n个顶点的无向图的数组  
	printf("已知顶点数和着色数分别为5和3\n");
	printf("已知无向图的邻接矩阵:\n{0,1,1,0,0}\n{1,0,1,1,1}\n{1,1,0,0,1}\n{0,1,0,0,1}\n{0,1,1,1,0}\n"); 
	for (i = 1; i <= n; i++)
		for (j = 1; j <= n; j++) 
			c[i][j] = e[i - 1][j - 1];
	printf("着色所有可能的解:\n");
	GraphColor(n, m, c);
	printf("\n");
	system("pause");
	return 0;
}