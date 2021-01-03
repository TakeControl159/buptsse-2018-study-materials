#include<iostream>
#include<queue>
using namespace std;
const int MAX = 20;
int cost[MAX][MAX];
struct Node {
	bool assigned[MAX];
	int ub;
	int level;
	queue<int> choice;
};
class Branch {
private:
	int number;
	int min;
	queue<Node> heap;
	queue<int> best;

public:
	Branch(int number_) {
		number = number_;
		min = 0;
		for (int i = 0; i < number; i++)
			min += cost[i][i];
	}

	void addNode(queue<int> currentChoice, int ub_, bool assigned_[MAX], int level) {
		Node n;
		n.choice = currentChoice;
		n.level = level;
		n.ub = ub_;
		for (int i = 0; i < number; i++)
			n.assigned[i] = assigned_[i];
		if (level <= number-1)
			heap.push(n);
	}

	void bestResult() {
		int cLevel = -1;
		bool tmpAssigned[MAX];
		int ub = 0;
		int temp;
		Node tmpNode;
		queue<int> tmpChoice;
		queue<int> tmp;
		for (int i = 0; i < number; i++)
			tmpAssigned[i] = false;
		while (true) {
			cLevel++;
			for (int i = 0; i < number; i++) {
				if ((!tmpAssigned[i]) && (ub + cost[cLevel][i] <= min)) {
					tmpAssigned[i] = true;
					tmpChoice.push(i);
					addNode(tmpChoice, ub + cost[cLevel][i], tmpAssigned, cLevel);
					if (cLevel == number - 1) {
						min = ub + cost[cLevel][i];
						best = tmpChoice;
					}

					tmpAssigned[i] = false;
					while (!tmpChoice.empty()) {
						temp = tmpChoice.front();
						tmp.push(temp);
						tmpChoice.pop();
					}
					int n = tmp.size();
					for (int i = 0; i < n - 1; i++) {
						tmpChoice.push(tmp.front());
						tmp.pop();
					}
				}
			}
			if (heap.empty())
				return;

			tmpNode = heap.front();
			cLevel = tmpNode.level;
			ub = tmpNode.ub;
			tmpChoice = tmpNode.choice;
			for (int i = 0; i < number; i++)
				tmpAssigned[i] = tmpNode.assigned[i];

			heap.pop();
		}
	}
	void printResult(){
		cout << "最小成本为：" << min << endl;
		int index = 0;
		while (!best.empty()) {
			index++;
			cout << "任务"<<index<<"分配给人员"<< (char)('a'+best.front()) << endl;
			best.pop();
		}

	}
};

int main() {
	int number;
	cout << "请输入有多少个任务：";
	cin >> number;
	for (int i = 0; i < number; i++)
		for (int j = 0; j < number; j++)
			cin >> cost[i][j];
	Branch b = Branch(number);
	b.bestResult();
	b.printResult();
	return 0;
}