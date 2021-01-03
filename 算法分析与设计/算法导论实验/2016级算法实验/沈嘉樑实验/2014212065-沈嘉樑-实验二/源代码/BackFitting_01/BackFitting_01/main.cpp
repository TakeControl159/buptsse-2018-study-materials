#include<stdio.h>
#include<iostream>
int number, capacity;
int *weight;
int *value;
int sum = 0, result = 0;
int *choice;
int *resultchoice;
using namespace std;

void bubble(int number) {
	int temp;
	for (int i = 0; i < number - 1; i++)
		for (int j = i + 1; j < number;j++)
			if (weight[j]>weight[i]) {
				temp = weight[i];
				weight[i] = weight[j];
				weight[j] = temp;
				temp = value[i];
				value[i] = value[j];
				value[j] = temp;
			}
}

void put(int index, int space) {
	if (index == number - 1 || space < weight[number-1])
		if (sum > result) {
			for (int i = 0; i < number;i++)
				resultchoice[i] = choice[i];
			result = sum;
		}
		else return;
	for (int i = index+1; i < number; i++) {
		if (weight[i] <= space) {
			choice[i] = 1;
			sum += value[i];
			put(i, space - weight[i]);
			sum -= value[i];
			choice[i] = 0;
		}
		else {
			choice[i] = 0;
			put(i, space);
		}
	}
}


int main() {
	cout << "请依次输入背包的数量和背包的容量，用空格分隔：" << endl;
	cin >> number >> capacity;
	weight = new int [number + 1];
	value  = new int [number + 1];
	choice = new int[number + 1];
	resultchoice = new int[number + 1];

	for (int i = 0; i < number; i++)
		choice[i] = 0;
	cout << "请依次输入各个物品的重量和价值，用空格分隔：" << endl;
	for (int i = 0; i < number; i++)
		cin >> weight[i] >> value[i];

	bubble(number);

	put(-1, capacity);

	cout << "最大价值为： " << result << endl;
	cout << "选择的物品为(1表示选择，0表示不选)：" << endl;
	for (int i = 0; i < number; i++)
		cout << weight[i] << ':' << resultchoice[i] << endl;

	delete weight;
	delete value;
	delete choice;
	delete resultchoice;
	return 0;
}