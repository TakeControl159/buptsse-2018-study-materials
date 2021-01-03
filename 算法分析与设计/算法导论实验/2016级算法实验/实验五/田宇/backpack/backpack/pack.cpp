#include<iostream>  
using namespace std;   
void KANPSACK_DP(int c[50][50], int w[50], int v[50], int n, int C)  
{
	for (int i = 0; i <= C; i++)      
	{
		c[0][i] = 0;
	}
	for (int i = 1; i <= n; i++)     
	{
		c[i][0] = 0;
		for (int j = 1; j <= C; j++)          
		{
			if (w[i] <= j)              
			{
				if (v[i] + c[i - 1][j - w[i]] > c[i - 1][j])                      
					c[i][j] = v[i] + c[i - 1][j - w[i]];                  
				else c[i][j] = c[i - 1][j];
			}
			else c[i][j] = c[i - 1][j];
		}
	}
}
void OUTPUT_SACK(int c[50][50], int x[50], int w[50], int n, int C)  
{
	for (int k = n; k >= 2; k--)      
	{
		if (c[k][C] == c[k - 1][C])
			x[k] = 0;                      
		else {
			x[k] = 1;               
			C = C - w[k];
		}
	}
	x[1] = c[1][C] ? 1 : 0;
}  
int main()  
{
	int c[50][50];     
	int w[50], v[50];     
	int x[50];
	int C, n;
	cout << "输入物品的总个数:";      
	cin >> n;
	cout << "输入背包的总容量:";     
	cin >> C;
	cout << "依次输入物品的重量:" << endl;     
	for (int i = 1; i <= n; i++)
	{
		cin >> w[i];
	}
	cout << "依次输入物品的价值:" << endl;     
	for (int i = 1; i <= n; i++)
	{
		cin >> v[i];
	}
	KANPSACK_DP(c, w, v, n, C);                 
	OUTPUT_SACK(c, x, w, n, C);     
	cout << "最优解为:" << endl;     
	for (int i = 1; i <= n; i++)      
	{
		cout << x[i] << "   ";
	}
	cout << endl << "最大容量为:" << endl;     
	cout << c[n][C] << endl;     
	system("pause");      
	return 0;
}