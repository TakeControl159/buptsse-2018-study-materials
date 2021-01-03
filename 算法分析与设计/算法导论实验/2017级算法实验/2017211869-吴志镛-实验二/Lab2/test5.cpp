#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;

int N, M;
int a[100][100];
struct Node {
	int x;
	int y;
};
Node Q[10005];
//定义马走的8个方向 
int dir_x[8] = { -1,-2,-2,-1,1,2,2,1 };
int dir_y[8] = { 2,1,-1,-2,-2,-1,1,2 };

void print() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++)
			printf("(%d,%d) ", Q[i*N + j + 1].x, Q[i*N + j + 1].y);
		printf("\n");
	}
	cout << endl << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++)
			printf("%-3d ", a[i][j]);
		printf("\n");
	}
}

bool judge(int x, int y) {
	for (int i = 0; i < 8; i++) {
		if (x + dir_x[i] == 0 && y + dir_y[i] == 0)
			return true;
	}
	return false;
}

void DFS(int cur_x, int cur_y, int step) {

	if (step == N * M + 1 && judge(cur_x, cur_y)) {
		print();
		system("pause");
		//exit(1);//exit是退出整个进程,exit里面的参数是作为进程的返回值提供给操作系统
	}

	int tmp_x, tmp_y;
	for (int i = 0; i < 8; i++) {
		tmp_x = cur_x + dir_x[i];
		tmp_y = cur_y + dir_y[i];
		if (tmp_x < 0 || tmp_x >= N || tmp_y < 0 || tmp_y >= M || a[tmp_x][tmp_y] != 0)
			continue;
		Q[step].x = tmp_x;
		Q[step].y = tmp_y;
		a[tmp_x][tmp_y] = step;
		DFS(tmp_x, tmp_y, step + 1);
		a[tmp_x][tmp_y] = 0;
	}
}


int main() {

	scanf("%d %d", &N, &M);
	a[0][0] = 1;
	Q[1].x = 0;
	Q[1].y = 0;
	DFS(0, 0, 2);
	system("pause");
	system("pause");
}

