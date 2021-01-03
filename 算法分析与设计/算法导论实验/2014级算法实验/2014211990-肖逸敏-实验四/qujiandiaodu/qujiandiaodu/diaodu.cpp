#include<iostream>
#include<algorithm>

using namespace std;

const int MAX = 100000;

int N, s[MAX], t[MAX];//输入，s开始时间，t结束时间

pair<int, int> itv[MAX];//用于对工作排序的pair数组

int main()
{
	cout << "输入工作量N：";
	cin >> N;
	cout << endl;

	cout << "输入开始时间和结束时间：" << endl;
	int i;
	for (i = 0; i<N; i++)
		cin >> itv[i].second >> itv[i].first;//便于以结束时间排序，所以改存顺序
	cout << endl;
	sort(itv, itv + N);

	int ans = 0, t = 0;
	for (i = 0; i < N; i++){
		if (t < itv[i].second){
			ans++;
			t = itv[i].first;
		}
	}
	cout << "最多的工作：";
	cout << ans << endl;

	system("pause");
	return 0;
}