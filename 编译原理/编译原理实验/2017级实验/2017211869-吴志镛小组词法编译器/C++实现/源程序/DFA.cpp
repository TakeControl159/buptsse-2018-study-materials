#include"DFA.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>



DFA::DFA()
{
	if ((infile = fopen("source.txt", "r")) == NULL)
	{
		printf("Open source file error!\n");
		exit(0);
	}
	if ((outfile = fopen("out.txt", "w")) == NULL)
	{
		printf("Open dest file error!\n");
		exit(0);
	}
	GetChar();
	GetBC();
	while (ch != EOF)
	{
		//识别数字
		if (IsDigit(ch))
		{
			pos = 0;
			while (IsDigit(ch))
			{
				Concat(ch);
				GetChar();
			}
			//while循环在读到 数字开头+字母时报错 
			if (IsLetter(ch))
			{
				strToken[0] = '\0';
				printf("第%d行有非法字符！继续分析......\n", numberOflines);
				while (IsLetter(ch))
					GetChar();
			}
			strToken[pos++] = '\0';
			if (strToken[0] != '\0')
				fprintf(outfile, "%s      数字\n", strToken);
			numberOfwords++;
			GetBC();
		}

		//识别关键字、标识符           
		else if (IsLetter(ch))
		{
			pos = 0;
			while (IsLetter(ch) || IsDigit(ch) || ch == '_')
			{
				Concat(ch);
				GetChar();
			}
			strToken[pos++] = '\0';
			if (KeyList(strToken) == 1)
				fprintf(outfile, "%s      关键字\n", strToken);
			else fprintf(outfile, "%s      标识符\n", strToken);

			numberOfwords++;
			GetBC();
		}


		//识别运算符(算术运算符 关系运算符 逻辑运算符 赋值运算符 不包括位运算符) 
		else if (ch == '+') //+,++,+=
		{
			pos = 0;
			Concat(ch);
			GetChar();
			if (ch == '+' || ch == '=')
			{
				Concat(ch);
				strToken[pos++] = '\0';
				fprintf(outfile, "%s      运算符\n", strToken);
				GetChar();
				GetBC();
			}
			else
			{
				strToken[pos++] = '\0';
				fprintf(outfile, "%s      运算符\n", strToken);
				GetBC();//此情况下ch不应该用GetChar()
			}
		}

		else if (ch == '-') //-,--,-=
		{
			pos = 0;
			Concat(ch);
			GetChar();
			if (ch == '-' || ch == '=')
			{
				Concat(ch);
				strToken[pos++] = '\0';
				fprintf(outfile, "%s      运算符\n", strToken);
				GetChar();
				GetBC();
			}
			else
			{
				strToken[pos++] = '\0';
				fprintf(outfile, "%s      运算符\n", strToken);
				GetBC();
			}
		}

		else if (ch == '*' || ch == '%' || ch == '!' || ch == '>' || ch == '<' || ch == '=')
			//*,*=,%,%=!,!=,>,>=,<,<=,=,==
		{
			pos = 0;
			Concat(ch);
			GetChar();
			if (ch == '=')
			{
				Concat(ch);
				strToken[pos++] = '\0';
				fprintf(outfile, "%s      运算符\n", strToken);
				GetChar();
				GetBC();
			}
			else
			{
				strToken[pos++] = '\0';
				fprintf(outfile, "%s      运算符\n", strToken);
				GetBC();
			}
		}

		else if (ch == '&') // &&
		{
			pos = 0;
			Concat(ch);
			GetChar();
			if (ch == '&')
			{
				Concat(ch);
				strToken[pos++] = '\0';
				fprintf(outfile, "%s      运算符\n", strToken);
				GetChar();
				GetBC();
			}
			else
			{
				printf("第%d行有非法字符！继续分析......\n", numberOflines);
				GetChar();
				GetBC();
			}
		}

		else if (ch == '|') // ||
		{
			pos = 0;
			Concat(ch);
			GetChar();
			if (ch == '|')
			{
				Concat(ch);
				strToken[pos++] = '\0';
				fprintf(outfile, "%s      运算符\n", strToken);
				GetChar();
				GetBC();
			}
			else
			{
				printf("第%d行有非法字符！继续分析......\n", numberOflines);
				GetChar();
				GetBC();
			}
		}

		else if (ch == '/') // /,/=,//
		{
			pos = 0;
			Concat(ch);
			GetChar();
			if (ch == '=')
			{
				Concat(ch);
				strToken[pos++] = '\0';
				fprintf(outfile, "%s      运算符\n", strToken);
				GetChar();
				GetBC();
			}
			else if (ch == '/') //注释的处理(跳过)，只处理//型的注释，不处理/**/型的注释       
			// //型注释读到本行末尾
			{
				Retract();
				while (ch != '\n'&&ch != EOF) //可能是最后一行所以考虑EOF 
					GetChar();
				GetBC(); //新加的 
			}
			else
			{
				strToken[pos++] = '\0';
				fprintf(outfile, "%s      运算符\n", strToken);
				GetBC();
			}
		}

		//识别分界符         
		else if (IsBound(ch))
		{
			pos = 0;
			Concat(ch);
			strToken[pos++] = '\0';
			fprintf(outfile, "%s      分界符\n", strToken);
			GetChar();
			GetBC();
		}
		else
		{
			printf("第%d行有非法字符！继续分析......\n", numberOflines);
			GetChar();
			GetBC();
		}
	}

	//打印统计结果
	printf("\n共计%d行\n", numberOflines);
	printf("\n单词个数为%d个(即关键字、标识符和数字个数)\n", numberOfwords);
	printf("\n字符个数为%d个(即包括空格、换行、注释中的字符在内的所有字符)\n\n\n", numberOfchars);
	system("pause");

}

DFA::~DFA()
{
}

char DFA::getCH()
{
	return ch;
}

int DFA::getpos()
{
	return pos;
}

char DFA::GetChar()
{
	ch = fgetc(infile);
	if (ch == EOF)
		printf("\n source.txt 的词法分析已完成,分析结果记录在 out.txt\n\n");
	numberOfchars++;
	return ch;
}

void DFA::GetBC()//检查ch中字符是否空白 若是继续调用GetChar()直至非空
{
	while (ch == ' ' || ch == '\t' || ch == '\b' || ch == '\n')
	{
		if (ch == '\n')
			numberOflines++;
		GetChar();
	}
}

void DFA::Concat(char ch)//将ch中的字符连接到strToken后
{
	strToken[pos++] = ch;
}

int DFA::IsLetter(char ch)//判断当前字符是否为字母 
{
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
		return 1;
	else return 0;
}

int DFA::IsDigit(char ch)//判断当前字符是否为数字 
{
	if (ch >= '0' && ch <= '9')
		return 1;
	else return 0;
}

int DFA::IsBound(char ch)//判断当前字符是否为分界符 
{
	if (ch == '.' || ch == '{' || ch == '}' || ch == '[' || ch == ']' || ch == '(' || ch == ')' || ch == ',' || ch == ';' ||
		ch == '#' || ch == '\\' || ch == '\'' || ch == '\"' || ch == '\?' || ch == ':')
		return 1;
	else return 0;
}

void DFA::Retract() //strToken回退，将ch置空 
{
	pos--;
	ch = ' ';
}

int DFA::KeyList(char strToken[])//判断strToken中是否为关键字
{
	if (strcmp(strToken, "auto") == 0)
		return 1;
	else if (strcmp(strToken, "break") == 0)
		return 1;
	else if (strcmp(strToken, "case") == 0)
		return 1;
	else if (strcmp(strToken, "char") == 0)
		return 1;
	else if (strcmp(strToken, "const") == 0)
		return 1;
	else if (strcmp(strToken, "continue") == 0)
		return 1;
	else if (strcmp(strToken, "default") == 0)
		return 1;
	else if (strcmp(strToken, "double") == 0)
		return 1;
	else if (strcmp(strToken, "do") == 0)
		return 1;
	else if (strcmp(strToken, "else") == 0)
		return 1;
	else if (strcmp(strToken, "enum") == 0)
		return 1;
	else if (strcmp(strToken, "extern") == 0)
		return 1;
	else if (strcmp(strToken, "float") == 0)
		return 1;
	else if (strcmp(strToken, "for") == 0)
		return 1;
	else if (strcmp(strToken, "goto") == 0)
		return 1;
	else if (strcmp(strToken, "if") == 0)
		return 1;
	else if (strcmp(strToken, "int") == 0)
		return 1;
	else if (strcmp(strToken, "long") == 0)
		return 1;
	else if (strcmp(strToken, "register") == 0)
		return 1;
	else if (strcmp(strToken, "return") == 0)
		return 1;
	else if (strcmp(strToken, "short") == 0)
		return 1;
	else if (strcmp(strToken, "signed") == 0)
		return 1;
	else if (strcmp(strToken, "sizeof") == 0)
		return 1;
	else if (strcmp(strToken, "static") == 0)
		return 1;
	else if (strcmp(strToken, "struct") == 0)
		return 1;
	else if (strcmp(strToken, "switch") == 0)
		return 1;
	else if (strcmp(strToken, "typedef") == 0)
		return 1;
	else if (strcmp(strToken, "union") == 0)
		return 1;
	else if (strcmp(strToken, "unsigned") == 0)
		return 1;
	else if (strcmp(strToken, "void") == 0)
		return 1;
	else if (strcmp(strToken, "volatile") == 0)
		return 1;
	else if (strcmp(strToken, "while") == 0)
		return 1;
	else return 0;
}
