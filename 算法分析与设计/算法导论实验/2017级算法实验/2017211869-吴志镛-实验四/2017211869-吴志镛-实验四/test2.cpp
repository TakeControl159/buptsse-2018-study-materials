#include<iostream>
using namespace std;
class Object {
	friend void knapsack(int, float, float*, float*);
public:
	int operator<=(Object a) const {
		return (d >= a.d);
	}
private:
	int ID;
	float d;
};

void knapsack(int n, float c, float v[], float w[]) {
	//排序：
	Object * Q = new Object[n];

	for (int i = 1; i <= n; i++) {
		Q[i - 1].ID = i;
		Q[i - 1].d = 1.0 * v[i] / w[i];
	}
	//采用简单冒泡排序
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n + 1 - i; j++) {
			if (Q[j - 1].d < Q[j].d) {
				Object temp = Q[j - 1];
				Q[j - 1] = Q[j];
				Q[j] = temp;
			}
		}
	
	float *v1 = new float[n + 1];
	float *w1 = new float[n + 1];

	for (int i = 1; i <= n; i++) {
		v1[i] = v[Q[i - 1].ID];
		w1[i] = w[Q[i - 1].ID];
		cout << "预处理后的装包顺序：" << endl;
		cout << "v1[" << i << "]: " << v1[i] << "    w1[" << i << "]: " << w1[i] << endl;
	}
	//排序结束：

	int i;
	float bestp = 0;
	float x[6];
	for (i = 1; i < n; i++) {
		x[i] = 0;
	}
	//贪心算法：
	for (i = 1; i < n; i++) {
		if (w1[i] > c)
			break;
		x[i] = 1;
		c -= w1[i];
	}
	if (i <= n)
		x[i] = c / w1[i];
	for (i = 1; i <= n; i++) {
		if (x[i] != 0) {
			cout << "选择放入的物品是：" << Q[i - 1].ID << endl;
			cout << "物品的" << x[i] << "部分被放入了背包" << endl;
			bestp += x[i] * v[Q[i - 1].ID];
		}
	}
	cout << "该背包问题的最大价值是：" << bestp << endl;
}
int main() {
	float p[] = { 0, 4, 6, 3, 5, 6 };
	float w[] = { 0, 5, 4, 2, 6, 2 };
	float c = 10;
	int n = 5;

	knapsack(n, c, p, w);

	system("pause");
	return 0;
}




