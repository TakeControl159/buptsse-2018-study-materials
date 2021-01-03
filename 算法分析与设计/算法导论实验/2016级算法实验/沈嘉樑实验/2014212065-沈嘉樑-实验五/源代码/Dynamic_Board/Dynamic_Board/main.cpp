#include<iostream>
using namespace std;
class board {
private:
	int x[100];
	int p[100];
	int miles;
	int number;
public:
	int opt(int j) {
		if (j == 0) return 0;
		int e = j - 1;
		while (x[j] - x[e] <= 5)
			e--;
		int n1 = p[j] + opt(e);
		int n2 = opt(j - 1);
		if (n1 > n2)
			return n1;
		else 
			return n2;
	}
	board() {
		cout << "请分别输入公里数和广告牌数量(空格分隔):" << endl;
		cin >> miles >> number;
		cout << "请分别输入每个广告牌的位置和价值(空格分隔)" << endl;
		x[0] = 0;
		for (int i = 1; i <= number; i++)
			cin >> x[i] >> p[i];
		cout << opt(number) <<endl;
	}
};


int main() {
	board b = board();
	return 0;
}