#include<iostream>
#include <stack>
using namespace std;
struct Node {
	int level;
	double weight;
	double value;
	double ub;
	stack<int> choice;
};

class Branch {
private:
	int *value;
	int *weight;
	int capacity;
	int number;
	double currentWeight;
	double currentValue;
	stack<Node> heap;
	int best;
	stack<int> bestChoice;

public: 
	Branch(int *value_, int *weight_, int capacity_, int number_) {
		value = value_;
		weight = weight_;
		capacity = capacity_;
		number = number_;
		currentWeight = 0;
		currentValue = 0;
		best = 0;
		bubble();
	}
	~Branch() {
		//delete bestChoice;
	}


	void bubble() {
		int temp;
		for (int i = 0; i < number - 1; i++)
			for (int j = i + 1; j < number; j++)
				if ((value[j] / weight[j]) > (value[i] / weight[i])) {
					temp = weight[i];
					weight[i] = weight[j];
					weight[j] = temp;
					temp = value[i];
					value[i] = value[j];
					value[j] = temp;
				}
	}
	double maxBound(int currentLevel) {
		double spare = capacity - currentWeight;
		double bound = currentValue;
		while (currentLevel < (number -1) && weight[currentLevel] <= spare  ) {
			spare -= weight[currentLevel];
			bound += value[currentLevel];
			currentLevel++;
		}
		if (currentLevel < number - 1) {
			bound += spare * (value[currentLevel] / weight[currentLevel]);
		}
		return bound;
	}
	void addNode(stack<int> currentChoice,int currentWeight_, int currentValue_, int ub_, int level_) {
		Node newNode;
		newNode.weight = currentWeight_;
		newNode.value = currentValue_;
		newNode.level = level_;
		newNode.ub = ub_;
		newNode.choice = currentChoice;
		if (level_ <= number - 1)
			heap.push(newNode);
	}
	void bestResult() {
		int index = 0;
		double ub = maxBound(index);
		int tmpWeight;
		Node tmpNode;
		stack<int> tmpChoice;
		while (true) {
			tmpWeight = currentWeight + weight[index];
			if (tmpWeight < capacity) {
				tmpChoice.push(weight[index]);
				addNode(tmpChoice, tmpWeight, currentValue + value[index], ub, index+1);
				if (best < (currentValue + value[index])) {
					best = currentValue + value[index];
					bestChoice = tmpChoice;
				}
			}
			ub = maxBound(index + 1);
			if (ub > best) {
				addNode(tmpChoice, currentWeight, currentValue, ub, index + 1);
			}
			if (heap.empty())
				return;
			tmpNode = heap.top();
			currentValue = tmpNode.value;
			currentWeight = tmpNode.weight;
			index = tmpNode.level;
			ub = tmpNode.ub;
			tmpChoice = tmpNode.choice;
			heap.pop();
		}
	}
	void printResult() {
		cout << "最大价值量为:" << best << endl;
		cout << "背包内的物体的重量分别为:" << endl;
		while(!bestChoice.empty()){
			cout << bestChoice.top() << endl;
			bestChoice.pop();
		}
	}
};
int main() {
	int number, capacity;
	int* weight, *value;
	cout << "请按顺序输入物品的数量以及背包容积（用空格分隔）：" << endl;
	cin >> number >> capacity;
	weight = new int[number];
	value = new int[number];
	cout << "请分别输出各个物品的重量和价值（用空格分隔）：" << endl;
	for (int i = 0; i < number; i++)
		cin >> weight[i] >> value[i];
	Branch b = Branch(value, weight, capacity, number);
	b.bestResult();
	b.printResult();

	delete weight;
	delete value;
	return 0;
}
