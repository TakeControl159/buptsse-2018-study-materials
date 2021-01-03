 #include<cstdio>
#include<cstdlib>
#include<iostream>
using namespace std;
#define MAX = 1000;
int d[6][3] = { {0,0,0}, {0,0,0}, {0,0,-1}, {0,-1,0}, {0,0,1}, {0,1,0} };
int x[100][100];
int y[100][100];
int bestx[100][100];    //x用来设置当前警卫，y用来表示监控情况，bestx返回最终结果
int n, m, best, k = 0, t = 0;   //当前已设置的警卫数为k，受监视的陈列室数为t，当前最少警卫数为best
int t1, t2, more;               //判断下界剪枝的条件参数
bool p;


void change(int i, int j) {    //在(i, j)处设置一个警卫，并改变其周围受监控情况
	x[i][j] = 1;
	k++;
	for (int r = 1; r <= 5; r++) {    //在自己本身跟上下左右五个地方设置受控
		int p = i + d[r][1];
		int q = j + d[r][2];
		y[p][q]++;
		if (y[p][q] == 1)
			t++;
	}
}
void restore(int i, int j) {    //撤销在(i, j)处设置的警卫，并改变其周围受监控情况
	x[i][j] = 0;
	k--;
	for (int r = 1; r <= 5; r++) {
		int p = i + d[r][1];
		int q = j + d[r][2];
		y[p][q]--;
		if (y[p][q] == 0)
			t--;
	}
}
void search(int i, int j) {   //回溯搜索
	do {                             //从上到下，从左至右搜索没被监控的位置
		j++;
		if (j > m) {
			i++;
			j = 1;
		}
	} while (!((y[i][j] == 0) || (i > n)));
	if (i > n) {
		if (k < best) {            //刷新警卫值
			best = k;
			for (int p = 1; p <= n; p++)
				for (int q = 1; q <= m; q++)
					bestx[p][q] = x[p][q];
			return;
		}
	}
	if (k + (t1 - t) / 5 >= best)    return;            //警卫数下界 = 还需设置的最少警卫数 + 现有的警卫数
	if ((i < n - 1) && (k + (t2 - t) / 5 >= best))    return;   //如果比最优警卫数多的话，就剪去这一分枝
	if (i < n) {                //结点p
		change(i + 1, j);
		search(i, j);            //递归搜索下一个点
		restore(i + 1, j);        //恢复
	}
	if (y[i][j + 1] == 0) {        //结点q
		change(i, j);
		search(i, j);
		restore(i, j);
	}
	if ((j < m) && ((y[i][j + 1] == 0) || (y[i][j + 2] == 0))) {    //结点r
		change(i, j + 1);
		search(i, j);
		restore(i, j + 1);
	}
}

void compute() {
	more = m / 4 + 1;
	if (m % 4 == 3)
		more++;
	else if (m % 4 == 2)
		more += 2;
	t2 = m * n + more + 4;
	t1 = m * n + 4;
	best = 65536;
	if (m == 1 && n == 1) {
		cout << "1" << endl;
		cout << "1" << endl;

	}
	for (int i = 0; i <= m + 1; i++) {    //在整个外面加上一圈，便于处理边界情况
		y[0][i] = 1;
		y[n + 1][i] = 1;
	}
	for (int i = 0; i <= n + 1; i++) {
		y[i][0] = 1;
		y[i][m + 1] = 1;
	}
	search(1, 0);
}

/**
 * 世界名画陈列馆问题（回溯法）
 */
int main() {
	printf("请设置陈列馆区域: \n");
	printf("m: ");
	cin >> m;
	printf("n:");
	cin >> n;
	compute(); //计算
	cout << "最少需要" << best << "个警卫" << endl;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++)
			cout << bestx[i][j] << " ";
		printf("\n");
	}
	system("pause");
}