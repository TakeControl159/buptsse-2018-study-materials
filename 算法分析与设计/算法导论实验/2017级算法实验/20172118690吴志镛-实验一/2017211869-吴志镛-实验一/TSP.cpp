#include<iostream>
#include<cstring>
#include<algorithm>
#include<vector>
#include<cstdio>
#include<cmath>
#include<string>
#define LL long long 
#define n 4 
using namespace std;
int main() {
	int i, k, j, l;
	int s[n];  //用于存储已访问过的城市 
	int D[n][n]; //用于记录两个城市之间的距离 
	int sum = 0; //用于计算已访问过的城市的最小路径长度 
	int Dtemp;//保证Dtemp比任意任意两个城市之间的距离都大 
	int flag;//最为访问的标志，若被访问过则为1，从未被访问过则为0 
	i = 1;//i是至今已经访问过的城市 
	s[0] = 0;
	D[0][1] = 3; D[0][2] = 6; D[0][3] = 7; D[1][0] = 12;
	D[1][2] = 2; D[1][3] = 8; D[2][0] = 8; D[2][1] = 6;
	D[2][3] = 2; D[3][0] = 3; D[3][1] = 7; D[3][2] = 6;

	do {
		k = 1;      //第几个位置 
		Dtemp = 10000;
		do {
			l = 0; flag = 0;
			do {
				if (s[l] == k) { //判断该城市是否被访问过， 
					flag = 1;
					break;
				}
				else {
					l++;
				}
			} while (l < i);
			if (flag == 0 && D[k][s[i - 1]] < Dtemp) {
				j = k; //j用来 存储已经访问过的城市 
				Dtemp = D[k][s[i - 1]];
			}
			k++;
		} while (k < n);
		s[i] = j;  //将已访问过的城市存储起来 
		i++;
		sum += Dtemp; //求出各城市之间的最短距离 
	} while (i < n);
	sum += D[0][j];//D[0][j]为旅行商所在的最后一个城市 
	cout << "依次经过的 城市号为";
	for (j = 0; j < n; j++) {
		cout << s[j]+1 << " ";
	}
	cout << "\n"<<"总的最短路程为" << sum<<endl;
	system("pause");
}
