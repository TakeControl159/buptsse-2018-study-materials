#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
struct package {
	double v, w;       
	bool operator  < (const package &rhs)const {      
		return v / w > rhs.v / rhs.w;
	}
}bag[500];
int main() {
	int p = 0, n;
	double C, cur = 0, ans = 0;
	cout << "\n请输入背包的最大容量：";
	cin >> C;
	cout << "请输入物品的个数：";
	cin >> n;
	cout << "请分别输入物品的重量和体积：" << endl;
	for (int i = 0; i < n; i++) {
		cin >> bag[i].w;
		cin >> bag[i].v;
	}
	sort(bag, bag + n);
	while (p < n) {
		if (cur + bag[p].w <= C) {
			cur += bag[p].w;
			ans += bag[p].v;
			cout << "选取价值为" << bag[p].v << "的物品,所取重量为：" << bag[p].w << endl;
			p++;
		}
		else {
			ans += bag[p].v / bag[p].w * (C - cur);
			cout << "选取价值为" << bag[p].v << "的物品,所取重量为：" << (C - cur) << endl;
			break;
		}
	}
	cout << "\n最大价值为：" << ans << endl;
	return 0;
}