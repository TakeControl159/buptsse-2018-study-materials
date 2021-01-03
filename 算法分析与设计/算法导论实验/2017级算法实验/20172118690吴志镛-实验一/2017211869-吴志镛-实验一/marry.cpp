
#include<iostream>
#include <stack>

using namespace std;

#define NUM 4
#define NIL -1

int GetPositionFromLaday(int ladayArray[][NUM], int laday, int man)
{
	for (int i = 0; i < NUM; i++)
		if (ladayArray[laday][i] == man)
			return i;
	return NIL;
}

void ChoosePartener(stack<int>& manStack, int manPos, int manArray[][NUM], int ladayArray[][NUM], int manPerfer[], int manStartPos[], int ladayNow[])
{
	//选择自己名单上排在首位的女人
	int perferLaday = manArray[manPos][manStartPos[manPos]];
	//如果该女孩没有接受过表白，则接受该男孩的表白
	if (ladayNow[perferLaday] == NIL)
	{
		ladayNow[perferLaday] = manPos;
		manPerfer[manPos] = perferLaday;
	}
	//如果已经有人向她表白，则判断其现在拥有的有没有现在追求的好
	else
	{
		int oldPos = GetPositionFromLaday(ladayArray, perferLaday, ladayNow[perferLaday]);
		int newPos = GetPositionFromLaday(ladayArray, perferLaday, manPos);
		if (oldPos < newPos)
		{
			manStartPos[manPos]++;//说明该女生更喜欢现在拥有的，选心目中第二位
			//加入单身行列
			manStack.push(manPos);
		}
		else //换男友
		{
			//被甩的男友恢复自由身份
			manStartPos[ladayNow[perferLaday]]++;
			//加入单身行列
			manStack.push(ladayNow[perferLaday]);
			//将追求的男士改为现任男友
			ladayNow[perferLaday] = manPos;
			manPerfer[manPos] = perferLaday;
		}
	}
}

int main()
{
	int manArray[NUM][NUM] = { {2,3,1,0},{2,1,3,0},{0,2,3,1},{1,3,2,0} };
	int ladayArray[NUM][NUM] = { {0,3,2,1},{0,1,2,3},{0,2,3,1},{1,0,3,2} };

	int manPerfer[NUM] = { 0 };//每位男生选中的女生
	int manStartPos[NUM] = { 0 };//记录每位男生选取的是心目中第几位的女生
	int ladayNow[NUM] = { NIL,NIL,NIL,NIL };//女生对应的男生

	stack<int> manStack; // 还处于单身的男士

	//进行第一轮迭代，每个男生都选择自己名单上排在首位的女生。
	for (int pos = 0; pos < NUM; pos++)
	{
		ChoosePartener(manStack, pos, manArray, ladayArray, manPerfer, manStartPos, ladayNow);
	}

	while (manStack.size() != 0)
	{
		int manPos = manStack.top();
		manStack.pop();
		ChoosePartener(manStack, manPos, manArray, ladayArray, manPerfer, manStartPos, ladayNow);
	}

	for (int i = 0; i < NUM; ++i)
		cout << "Man NO.: " << i << " Laday NO.: " << manPerfer[i] << endl;

	system("pause");
}


