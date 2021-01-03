#include<stdio.h>
#include<iostream>
using namespace std;

int positionOfLove(int number, int ftom[100][100],int indexOfFemale, int indexOfMale) {
	for (int i = 0; i < number; i++) {
		if (ftom[indexOfFemale][i] == indexOfMale) return i;
	}
	
}
int main() {
	int number;
	int mtof[100][100], ftom[100][100];
	int femaleIsMarry[100];
	int maleIsMarry[100];
	int numberOfMarried = 0;
	cout << "请输入人数：" << endl;
	cin >> number;
	for (int i = 0; i < number; i++) {
		maleIsMarry[i] = -1;
		femaleIsMarry[i] = -1;
	}

	cout << "请输入男生对女生的好感度矩阵" << endl;
	for (int i = 0; i < number; i++)
		for (int j = 0; j < number; j++)
			cin >> mtof[i][j];

	cout << "请输入女生对男生的好感度矩阵" << endl;
	for (int i = 0; i < number; i++)
		for (int j = 0; j < number; j++)
			cin >> ftom[i][j];
	//当所有人匹配好时循环才结束
	for (int i = 0; numberOfMarried!=number ; i++) {
		i = i % number;
		if (maleIsMarry[i]!=-1) // 该男生已经匹配了对象
			continue; 
		for (int j = 0; j < number; j++) {//按好感度从高到底匹配
			if (*(femaleIsMarry + mtof[i][j]) == -1) {//当女生还没有对象时
				maleIsMarry[i] = mtof[i][j];
				*(femaleIsMarry + mtof[i][j]) = i;
				numberOfMarried++;
				break;
			}
			else {//当女生已经有对象时
				if (positionOfLove(number, ftom, mtof[i][j], i) < positionOfLove(number, ftom, mtof[i][j], *(femaleIsMarry + mtof[i][j]))) {//比较两个男生的好感度
					*(maleIsMarry + *(femaleIsMarry + mtof[i][j])) = -1; 
					*(femaleIsMarry + mtof[i][j]) = i;
					maleIsMarry[i] = mtof[i][j];
					break;
				}
			}
		}
	}
	cout << "男生娶的女孩：" << endl;
	for (int i = 0; i < number; i++)
		cout << maleIsMarry[i] << endl;

	cout << "女生嫁的男孩：" << endl;
	for (int i = 0; i < number; i++)
		cout << femaleIsMarry[i] << endl;



	return 0;
}
