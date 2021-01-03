#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

class DFA
{
public:

	FILE *infile, *outfile;
	char GetChar();
	void GetBC();//检查ch中字符是否空白 若是继续调用GetChar()直至非空
	void Concat(char ch); //将ch中的字符连接到strToken后
	int IsLetter(char ch); //判断当前字符是否为字母 
	int IsDigit(char ch); //判断当前字符是否为数字 
	int IsBound(char ch); //判断当前字符是否为分界符 
	void Retract();  //strToken回退，将ch置空 
	int KeyList(char strToken[]); //判断strToken中是否为关键字
	DFA();
	~DFA();
	char getCH();
	int getpos();

private:
	char strToken[100];   //存放构成单词符号的字符串 
	char ch;    //存放最新读进的源程序字符 
	int pos = 0;  //当前字符串的位置指针 
	int numberOflines = 1; //统计行数 
	int numberOfwords = 0; //统计源程序中单词个数,标点和空格不计为单词 
	int numberOfchars = -1; //统计源程序中字符个数 要去掉EOF 


};
