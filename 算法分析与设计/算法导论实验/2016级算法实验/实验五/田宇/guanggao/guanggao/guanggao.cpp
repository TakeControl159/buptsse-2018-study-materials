#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;

#define N 100000

struct Po{
	int pre;
	int pos, val;
	bool operator  < (const Po &rhs)const{
		return pos<rhs.pos;
	}

}e[N];

int ans[N];

int find(Po *array, int size, int key)
{
	int first = 0, len = size - 1;
	int half, mid;
	while (len>1)
	{
		half = len / 2;
		mid = first + half;
		if (array[mid].pos >= key)
		{
			len = half;
		}
		else{
			first = mid;
			len = len - half;
		}
	}
	return first;
}

int main()
{
	int i, n;
	int y,m;
	printf("输入广告牌数量：");
	scanf("%d", &n);
	printf("输入两个广告牌最小距离：");
	scanf("%d", &y);
	printf("输入总的长度：");
	scanf("%d", &m);
	e[0].pos = 0;
	printf("输入可能地点：");
	for (i = 1; i <= n; i++)//第一个位置放一个空广告牌
		scanf("%d", &e[i].pos);
	printf("输入地点利益：");
	for (i = 1; i <= n; i++)
		scanf("%d", &e[i].val);
	sort(e, e + n + 1);//对位置由小到大排序
	for (i = 0; i <= n; i++)
		e[i].pre = find(e, n+1, e[i].pos - y);
	ans[1] = e[1].val;
	for (i = 2; i <= n; i++)
		ans[i] = max(e[i].val + ans[e[i].pre], ans[i - 1]);
	printf("总的最大利益：%d\n", ans[n]);
	system("pause");
	return 0;

}
