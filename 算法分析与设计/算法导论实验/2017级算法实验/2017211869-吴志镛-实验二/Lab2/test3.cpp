#include <iostream>
#define MaxSize 100
using namespace std;

//首先使用二位数据建立迷宫矩阵:0表示通路，1表示墙 
int maze[10][10] =        //迷宫在计算机中的物理存储方式
{
   {1,1,1,1,1,1,1,1,1,1},
   {1,0,0,1,1,0,1,1,0,1},
   {1,0,0,1,0,0,0,1,0,1},
   {1,0,0,0,0,1,1,0,0,1},
   {1,0,1,1,1,0,0,1,1,1},
   {1,0,0,0,1,0,0,0,0,1},
   {1,0,1,0,0,0,1,0,0,1},
   {1,0,1,1,1,0,1,1,0,1},
   {1,0,0,1,1,0,0,1,0,1},
   {1,1,1,1,1,1,1,1,1,1}
};

//建立顺序栈,用于存储当前的位置信息和下一步的方向 
struct Try
{
	int i;
	int j;
	int d;
}path[MaxSize];
int top = -1;    //初始化栈指针 

void FindPath(int xb, int yb, int xe, int ye)
{
	//起点入栈
	top++;
	path[top].i = xb;
	path[top].j = yb;
	path[top].d = -1;
	maze[xb][yb] = -1;    //标记起点     
	int i, j, k, d, find;    //映射变量与旗帜变量 
	while (top > -1)
	{
		i = path[top].i;
		j = path[top].j;
		d = path[top].d;
		if (i == xe && j == ye)
		{
			cout << "迷宫路径如下：" << endl;
			for (k = 0; k <= top; k++)
			{
				cout << "(" << path[k].i << "," << path[k].j << ") ";    //遍历整个栈，从栈底开始输出 
				if ((k + 1) % 5 == 0) cout << endl;    //每行输出五个数据 
			}
			cout << endl;
			return;
		}
		find = 0;
		while (d < 4 && find == 0)    //循环判断上下左右每一个方向的情况，不是1直接入栈，是1再次循环，循环四次都是1则弹栈 
		{
			d++;
			switch (d)
			{
			case 0:
				i = path[top].i - 1;
				j = path[top].j;
				break;
			case 1:
				i = path[top].i;
				j = path[top].j + 1;
				break;
			case 2:
				i = path[top].i + 1;
				j = path[top].j;
				break;
			case 3:
				i = path[top].i;
				j = path[top].j - 1;
				break;
			}
			if (maze[i][j] == 0) find = 1;
		}
		if (find == 1)
		{
			path[top].d = d;
			top++;
			path[top].i = i;
			path[top].j = j;
			path[top].d = -1;
			maze[i][j] = -1;    //标记每一个通路为-1，防止原路返回，如果弹栈则将相应的-1换为0 
		}
		else
		{
			maze[path[top].i][path[top].j] = 0;
			top--;
		}
	}
	cout << "无路可走！" << endl;
}

void PrintMaze()
{
	cout << "包含有路径的迷宫：" << endl;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			printf("%3d", maze[i][j]);
		}
		cout << endl;
	}
}

int main()
{
	FindPath(1, 1, 8, 8);
	PrintMaze();
	system("pause");
}