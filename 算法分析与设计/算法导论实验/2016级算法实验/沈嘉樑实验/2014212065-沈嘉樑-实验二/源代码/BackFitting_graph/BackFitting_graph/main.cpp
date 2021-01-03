/*
在输入中关系矩阵中，0表示两点之间无连线；1表示有连线
该程序能够输出所有的取色方案
*/
#include<stdio.h>
#include<iostream>
using namespace std;

int relation[100][100], color[100], m, number, numOfResult;

bool isOk(int k) {//判断是否有冲突
	for (int j = 1; j <= number; j++)
		if (relation[k][j] && (color[j] == color[k]))
			return false;
	return true;
}

void draw(int index) {
	if (index > number) {
		numOfResult++;
		for (int i = 1; i <= number; i++) {
			cout << color[i] << " ";
		}
		cout << endl;
		return;
	}
	for (int i = 1; i <= m; i++) {
		color[index] = i;
		if (isOk(index)) {
			draw(index + 1);
		}
		color[index] = 0;
	}
}

int main() {
	cout << "请输入点的个数:" << endl;
	cin >> number;
	cout << "请输入点之间的关系矩阵:" << endl;
	for (int i = 1; i <= number; i++)
		for (int j = 1; j <= number; j++) {
			cin >> relation[i][j];
		}
	cout << "解空间为:" << endl;

	for (int i = 1; i <= 10; i++) {
		m = i;
		numOfResult = 0;
		draw(1);
		if (numOfResult != 0) {
			cout << "最少需要的颜色数量为:" << m << endl;
			cout << "着色方案数量为:" << numOfResult << endl;
			break;
		}
	}

	return 0;
}
