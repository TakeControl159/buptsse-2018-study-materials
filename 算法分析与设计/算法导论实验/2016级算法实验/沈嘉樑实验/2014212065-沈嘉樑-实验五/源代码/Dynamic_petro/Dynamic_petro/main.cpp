#include<iostream>
using namespace std;

class drive {
private:
	int n;
	int k;
	int a;
	int b;
	int c;
	int p[101][101];
	int f[101][101][2];
public:
	drive() {
		cout << "请分别输入N,K,A,B,C的值:" << endl;
		cin >> n >> k >> a >> b >> c;
		cout << "请输入加油站分布情况:" << endl;
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				cin >> p[i][j];
		execute();
	}
	void execute() {
		//当前点的前一个点
		int s[4][3] = {
			-1, 0, 0,
			0, -1, 0,
			1, 0, b,
			0, 1, b
		};
		
		for (int i = 1; i <= n; i++) 
			for (int j = 1; j <= n; j++) {
				f[i][j][0] = 1000;
			}
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++) {
				f[i][j][1] = k;
			}
			
		f[1][1][0] = 0;
		f[1][1][1] = k;
		int count = 1;
		int tempx;
		int tempy;
		while (count) {
			count = 0;
			for (int x = 1; x <= n; x++) {
				for (int y = 1; y <= n; y++) {
					if (x == 1 && y == 1)
						continue;
					int min_cost = 1000;
					int temp_cost;
					int tx, ty;
					int temp_petro;
					int min_petro;
					for (int z = 0; z < 4; z++) {
						tx = x + s[z][0];
						ty = y + s[z][1];
						if (ty < 1 || ty > n || tx < 1 || tx > n)
							continue;
						temp_cost = f[tx][ty][0] + s[z][2];
						temp_petro = f[tx][ty][1] - 1;
						if (p[x][y] == 1 && (x != n || y != n)) {
							temp_cost += a;
							temp_petro = k;
						}
						if ((temp_petro == 0) && (p[x][y] == 0) && (x != n || y != n)) {
							temp_cost += (a + c);
							temp_petro = k;
						}
						if (temp_cost < min_cost) {
							min_cost = temp_cost;
							min_petro = temp_petro;
							tempx = tx;
							tempy = ty;
						}
					}
					if (f[x][y][0] > min_cost) {
						count++;
						f[x][y][0] = min_cost;
						f[x][y][1] = min_petro;
					}
				}
			}
		}
		cout << "最少花销:" << f[n][n][0] << endl;
	}
};

int main() {
	drive d = drive();
	return 0;
}