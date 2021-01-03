#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<algorithm>
#define INF 0x3f3f3f3f
#define d(x) cout << (x) << endl
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;
const int N = 1e5 + 10;
const int M = 1e3 + 10;

int m, n;
int dp[N];
int lastdp[N];
int ans;
void g()
{
	for (int i = 0; i <= n; i++) {
		lastdp[i] = dp[i];
	}
	ans = dp[n];
	memset(dp, 0, sizeof(dp));
}

int common(char a[], char b[])
{

	memset(dp, 0, sizeof(dp));
	memset(lastdp, 0, sizeof(lastdp));
	for (int i = 1; i <= m; i++) {			//复杂度为 n * m
		for (int j = 1; j <= n; j++) {
			// if(a[i-1] == b[j-1]){
			//     dp[i][j] = dp[i - 1][j - 1] + 1;
			// }else{
			//     dp[i][j] = max(dp[i][j - 1], dp[i - 1][j]);
			// }
			if (a[i - 1] == b[j - 1]) {
				dp[j] = lastdp[j - 1] + 1;
			}
			else {
				dp[j] = max(dp[j - 1], lastdp[j]);
			}
		}
		g();		//更新数组滚动
	}
	return ans;
}
int main()
{
	char a[N];
	char b[N];
	printf("请输入父串");
	scanf("%s", a);
	m = strlen(a);
	int t;
	printf("输入字串:");
	scanf("%d", &t);
	while (t--) {
		scanf("%s", b);
		n = strlen(b);
		if (n > m) {
			printf("No\n");
			continue;
		}
		if (common(a, b) == n) {
			printf("Yes\n");
		}
		else {
			printf("No\n");
		}
	}

	return 0;
}
/*
YAHOO,GOOGLE,YAMAXUN.BAIDU,ALIBABA,TENGXUN
YAHOO
GOOGLE
YAHOO,BAIDU
BAIDU,ALIBABA,TENGXUN
*/
