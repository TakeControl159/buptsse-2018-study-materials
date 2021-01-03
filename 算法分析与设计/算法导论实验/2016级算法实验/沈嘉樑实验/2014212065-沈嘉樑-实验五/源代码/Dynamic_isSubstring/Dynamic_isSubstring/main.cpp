#include<iostream>
using namespace std;
class sub {
private:
	int m;
	int n;
	int subS[100];
	int S[100];

public:
	sub() {
		cout << "请分别输入S'串的长度m和S串的长度n:" << endl;
		cin >> m >> n;
		cout << "请输入串S':" << endl;
		for (int i = 0; i < m; i++)
			cin >> subS[i];
		cout << "请输入串S:" << endl;
		for (int j = 0; j < n; j++)
			cin >> S[j];
		int index1 = 0;
		int index2 = 0;
		while (index1 <= m || index2 <= n) {
			if (subS[index1] != S[index2]) {
				index2++;
				continue;
			}
			if (subS[index1] == S[index2]) {
				index1++;
				index2++;
				continue;
			}
		}
		if (index1 == m + 1) {
			cout << "Yes" << endl;
			return;
		}
		if (index2 == n + 1) {
			cout << "No" << endl;
			return;
		}
	}
};
int main() {
	sub s = sub();
	return 0;
}