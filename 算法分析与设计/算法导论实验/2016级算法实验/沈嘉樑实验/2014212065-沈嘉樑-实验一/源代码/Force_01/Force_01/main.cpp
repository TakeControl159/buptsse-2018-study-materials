#include<stdio.h>
#include<iostream>
using namespace std;
int number, capacity; 
int *weight;
int *value;
int currentsum = 0, resultsum = 0, space;
int *currentchoice;
int *resultchoice;
//该子函数用于搜索结果
void search() {
	int t;
	long times = 1;
	//计算搜索总次数times
	for (int i = 0; i < number; i++)
		times *= 2;
	for (int i = 0; i < times; i++) {
		currentsum = 0;
		space = capacity;
		t = i;
		for (int j = number - 1; j >= 0; j--) {
			currentchoice[j] = t % 2;
			t = t / 2;
			if (currentchoice[j] == 1) {
				currentsum += value[j];
				space -= weight[j];
				if (space < 0) {//当背包空间不足时
					currentsum -= value[j];
					space -= weight[j];
					break;
				}
			}
		}
		if (currentsum > resultsum) {//比较是否是总价值最大的结果
			for (int i = 0; i < number; i++)
				resultchoice[i] = currentchoice[i];
			resultsum = currentsum;
		}
	}
}

int main() {
	while (true) {
		cout << "请输入物品数量和背包容量，用空格分隔" << endl;
		cin >> number >> capacity;
		weight = new int[number + 1];
		value = new int[number + 1];
		currentchoice = new int[number + 1];
		resultchoice = new int[number + 1];
		cout << "请分别输入各个物品的重量和价值" << endl;
		for (int i = 0; i < number; i++)
			cin >> weight[i] >> value[i];

		search();
		cout << "背包里最多能装的价值为： " << resultsum << endl;
		cout << "背包里有的物品重量分别为：" << endl;
		for (int i = 0; i < number; i++)
			if (resultchoice[i])
				cout << weight[i] << endl;

		delete weight;
		delete value;
		delete currentchoice;
		delete resultchoice;

		cout << "请问是否要进行新的查询，输入0退出系统: ";
		int iscontinue;
		cin >> iscontinue;
		if (!iscontinue) break;
	}
	


	

	
	return 0;
}