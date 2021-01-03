#include<iostream>
#include<queue>
#include<stack>
using namespace std;
int start[3][3];
int finish[3][3];
struct Node {
	int id;//记录当前节点的序号
	int pre;//记录上一个节点的序号
	int lastMoved;//记录上一次移动的点
	int state[3][3];//记录状态
	int fx;
	int level;//记录层次
};

class Branch {
private:
	int index;
	Node tmpNode;
	queue<Node> option;
	queue<Node> choice;
	stack<Node> best;
public:
	Branch() {
		index = 0;
	}
	void addNode(int level_, int lastMoved_, int id_, int pre_) {
		Node n;
		n.pre = pre_;
		n.id = id_;
		n.level = level_;
		n.lastMoved = lastMoved_;
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				n.state[i][j] = tmpNode.state[i][j];
		n.fx = 0;
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				if ((n.state[i][j] != finish[i][j]) && (finish[i][j] != 0)) {
					n.fx++;
				}
		n.fx = n.fx + level_;
		option.push(n);
	}

	int findFree(int state[3][3]) {
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3;j++)
				if (state[i][j] == 0) { 
					return i*10+j;
				}

	}

	void bestResult() {
		int cLevel = 0;
		int position[2];
		int p;
		queue<Node> tmp;
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++) {
				tmpNode.state[i][j] = start[i][j];

			}
		tmpNode.id = index;
		tmpNode.pre = -1;
		tmpNode.lastMoved = -1;
		tmpNode.fx = INT_MAX;
		tmpNode.level = 0;

		while (true) {

			p = findFree(tmpNode.state);
			position[0] = p / 10;
			position[1] = p % 10;
			for (int i = position[0] - 1; i <= position[0] + 1; i++) {
				if ((i >= 0) && (i <= 2) && (i!=position[0]) && (tmpNode.lastMoved != (i*10+position[1]))) {
					index++;
					tmpNode.state[position[0]][position[1]] = tmpNode.state[i][position[1]];
					tmpNode.state[i][position[1]] = 0;
					addNode( cLevel + 1, p, index, tmpNode.id);
					tmpNode.state[i][position[1]] = tmpNode.state[position[0]][position[1]];
					tmpNode.state[position[0]][position[1]] = 0;
				}
			}
			for (int i = position[1] - 1; i <= position[1] + 1; i++) {
				if ((i >= 0) && (i <= 2) && (i != position[1]) && (tmpNode.lastMoved != (i + position[0]*10))) {
					index++;
					tmpNode.state[position[0]][position[1]] = tmpNode.state[position[0]][i];
					tmpNode.state[position[0]][i] = 0;
					addNode( cLevel + 1,p, index, tmpNode.id);
					tmpNode.state[position[0]][i] = tmpNode.state[position[0]][position[1]];
					tmpNode.state[position[0]][position[1]] = 0;
				}
			}
			int min = INT_MAX;
			if (choice.empty()) {
				while (!option.empty()) {
					tmpNode = option.front();
					option.pop();
					tmp.push(tmpNode);
					if (min > tmpNode.fx) min = tmpNode.fx;
					if (tmpNode.fx == tmpNode.level) {
						cout << "需要进行交换的次数为："<<tmpNode.level << endl;
						//输出最佳路线
						cout << "交换路线为：" << endl;
						stack<Node> store;
						Node temp;
						store.push(tmpNode);
						while (!best.empty()) {
							temp = best.top();
							if (tmpNode.pre == temp.id) {
								tmpNode = temp;
								store.push(temp);
							}
							best.pop();
						}
						int number = store.size();
						cout << "开始状态:" << endl;
						for (int j = 0; j < 3; j++) {
							for (int k = 0; k < 3; k++)
								cout << start[j][k] << " ";
							cout << endl;
						}
						for (int i = 0; i < number; i++) {
							temp = store.top();
							store.pop();
							cout << "Round " << i + 1 << ":" << endl;
							for (int j = 0; j < 3; j++) {
								for (int k = 0; k < 3; k++)
									cout << temp.state[j][k] << " ";
								cout << endl;
							}
						}

						return;
					}
				}
				while (!tmp.empty()) {
					tmpNode = tmp.front();
					tmp.pop();
					if (min == tmpNode.fx) {
						choice.push(tmpNode);
						best.push(tmpNode);
					}
				}
			}
			tmpNode = choice.front();
			choice.pop();
			cLevel = tmpNode.level;
				
		}

	}
};

int main() {
	cout << "请输入开始状态（0代表空格）：" << endl;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			cin >> start[i][j];
	cout << "请输入目标状态（0代表空格）：" << endl;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			cin >> finish[i][j];
	Branch b = Branch();
	b.bestResult();
}