#if !defined(AFX_WORK_H__FFC92D1D_03FB_4BE1_AE4E_6B64ADF7D9C0__INCLUDED_)
#define AFX_WORK_H__FFC92D1D_03FB_4BE1_AE4E_6B64ADF7D9C0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Work
{
	int n;
	int **c;
	int *work;  //存储当前工人的分配
	int *tmp;
	int cc, minc, highest;
	void swap(int &a, int &b);
	void init(); //初始化+从文件中读取数据
	void showArray();
	void show();
	int getHighest(); //计算上界
public:
	int count; //用于记录递归次数
	Work();
	virtual ~Work();
	void find(int i);   //分支界限法
	void output();    //输出最少时间
};

#endif // !defined(AFX_WORK_H__FFC92D1D_03FB_4BE1_AE4E_6B64ADF7D9C0__INCLUDED_)
