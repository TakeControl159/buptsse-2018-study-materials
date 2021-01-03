
#include<stdio.h>
#include<iostream>
#include<queue>
#include<tchar.h>

using namespace std;


const int N = 5;
int s[N] = { 1,2,4,6,8 };
int t[N] = { 3,5,7,9,10 };
int solve() {
	pair<int, int>itv[N];
	for (int i = 0; i < N; i++) {
		itv[i].first = s[i];
		itv[i].second = t[i];
	}
	sort(itv, itv + N);
	int count = 0;
	int t = 0;
	for (int i = 0; i < N; i++) {
		if (t < itv[i].first) {
			count++;
			t = itv[i].second;
			cout << "调度区间的开始值为："<<itv[i].first<< endl;
		}
	}
	return count;

}


int main() {
	cout << "总共调度的区间数量："<<solve() << endl;
	system("pause");
}

