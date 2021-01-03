#include <stdio.h>
#include <tchar.h>
#include <queue>
#include "iostream"
using namespace std;
int N;
int s[100];
int t[100];
int solve()
{
	int temp;
	for (int i = 0; i < N; i++) {
		for (int j = i + 1; j < N; j++)
			if (t[i]>t[j]) {
				temp = s[i];
				s[i] = s[j];
				s[j] = temp;
				temp = t[i];
				t[i] = t[j];
				t[j] = temp;
			}
	}
	int count = 0;
	int time = 0;
	for (int i = 0; i < N; i++) {
		if (time <= s[i]) {
			count++;
			time = t[i];
			cout << "选择开始时间为" << s[i] << "；结束时间为" << t[i] << endl;
		}
	}
	return count;
}
int main() {
	cout << "请输入一共有多少个工作集：";
	cin >> N;
	cout << "请分别输入每个工作集的开始和结束时间：" << endl;
	for (int i = 0; i < N; i++)
		cin >> s[i] >> t[i];
	int num = solve();
	cout << "数量为：" << num << endl;
	return 0;
}