%option noyywrap
%{
    #include <ctype.h>
    #include <stdio.h>
    #include <string>
    #include <cstdlib>
    #include <iomanip>
    #include <iostream>

	#define NONE "\033[0m"
	#define RED "\033[31m"
	#define GREEN "\033[32m"
	#define YELLOW "\033[33m"
	#define BLUE "\033[34m"
	#define PURPLE "\033[35m"
	#define CYAN  "\033[36m"
	#define WHITE "\033[37m"

	// 是否打印中间输出 
	#define IS_OUT_  1
	// 中间输出是否输出空白字符
	#define IS_OUT_SPACE 0
	// 中间输出是否输出换行符
	#define IS_OUT_LINKBREAK 0
    using namespace std;

	// 中间输出是否启用着色[对于支持ASCII颜色输出的才有效]
	// #define IS_OUT_COLOR 1
	int IS_OUT_COLOR = 0;
	
	

    int AllCharacterNum = 0;           //总字符数量     
    int Row = 1;                       //行数量
    int FloatNumerNum = 0;             //浮点数数量 
    int IntNumberNum = 0;              //整数数量
    int KeyWordNum = 0;                //关键字数量
    int SeparatorNum = 0;              //分隔符数量
    int OperatorNum = 0;               //操作符数量
    int LineCommentNum = 0;            //单行注释数量
    int LinesCommentNum = 0;	       //多行注释数量 
    int VariableNum = 0;               //变量or函数名数量
    int StringNum = 0;                 //字符串数量
    int CharNum = 0;                   //单个字符数量
    int ErrorNum = 0;                  //错误数量
    int ErrorRow[500] = {};            //错误行号

    //记录错误
    void recordError(int row)
    {
        ErrorRow[ErrorNum] = row;
    }

	// 打印函数
	void coutLineLog(int index, string sType,int textType,string text,int numOfChar){
		cout << std::setw(8) << std::left << "[" +to_string(index)+"]";
		cout << std::setw(8) << std::left << numOfChar;
		if(IS_OUT_COLOR){
			cout << std::setw(20) << std::left;
			if(textType==0) cout << (WHITE +sType+ NONE).c_str();
			else if(textType==1) cout << (RED  +sType+ NONE).c_str();
			else if(textType==2) cout << (YELLOW  +sType+ NONE).c_str();
			else if(textType==3) cout << (GREEN  +sType+ NONE).c_str();
			else if(textType==4) cout << (BLUE  +sType+ NONE).c_str();
			else if(textType==5) cout << (PURPLE  +sType+ NONE).c_str();
			else if(textType==6) cout << (CYAN +sType+ NONE).c_str();
		}
		else{
			cout << std::setw(12) << std::left;
			cout << sType.c_str();
		}
		cout << std::setw(16) << std::left <<text << "\n";
	}

	// 判断字符串是否相等
	int isEqual(const char *str1, const char *str2) {
		for (int p = 0; str1[p] == str2[p]; p++) {
			if (str1[p] == '\0') {
				return 1;
			}
		}
    return 0;
}
 
%}

digit [0-9]                                            
letter [a-zA-Z]

operator "+"|"-"|"*"|"/"|"%"|=|!|"<"|">"|"?"|&|"^"|~|"+="|"-="|"*="|"/="|"%="|"=="|"<<="|">>="|"&="|"^="|"|="|"!="|">="|"<="|"++"|"--"|"<<"|">>"|&&|"||"
separator "["|"]"|"("|")"|"{"|"}"|,|"."|;|:

delim [ \t\r]

space {delim}+

intNumer (([1-9]{digit}*)|(0[xX][0-9a-fA-F]+)|(0[01234567]*)|0b[01]+)([uU]|[lL]|[uU][lL]|[lL][uU]|([lL][lL]))?

floatNumer ({digit}+\.((({digit}*((E|e)(\+|-)?({digit}+([lLfF])?)|(([lL])?([fF])?))?)?)|([lLfF])?))|(\.({digit}+)(((E|e)(\+|-)?{digit}+[lLfF]?|([lL]?[fF]?))?))|({digit}+(((E|e)(\+|-)?{digit}+[lLfF]?)|([fF])))



keyword auto|char|float|double|int|short|long|signed|unsigned|static|const|enum|union|struct|if|else|for|switch|case|break|continue|while|do|goto|void|return|default|extern|register|sizeof|typedef|volatile
 
variable ({letter}|_)({letter}|{digit}|_)*                              

lineComment "//"[^\n]*
linesComment "/*"[^*]*\*(([^*/][^*]*)?\*)*\/


string_ \"([^\n"\\]|(\\(.|\n)))*\"   ????



char_ \'[^\']*\'


error {floatNumer}?([^ \n\t\[\](){},;:+\-*/%=!<>?&^~|=]+)


%%



{floatNumer} { 
	FloatNumerNum++; 
	AllCharacterNum += yyleng; 
	if(IS_OUT_)
		coutLineLog(Row,"[小数值]",0,yytext,yyleng);
}

{intNumer} { 
	IntNumberNum++; 
	AllCharacterNum += yyleng;
	if(IS_OUT_) 
		coutLineLog(Row,"[整数值]",0,yytext,yyleng);
}

{keyword} { 
	KeyWordNum++; 
	AllCharacterNum += yyleng; 
	if(IS_OUT_)
		coutLineLog(Row,"[关键字]",3,yytext,yyleng);
}

{variable} { 
	VariableNum++; 
	AllCharacterNum += yyleng; 
	if(IS_OUT_)
		coutLineLog(Row,"[标识符]",0,yytext,yyleng); 
}

{operator} { 
	OperatorNum++; 
	AllCharacterNum += yyleng;
	if(IS_OUT_) 
		coutLineLog(Row,"[运算符]",0,yytext,yyleng);
}

{separator} { 
	SeparatorNum++; 
	AllCharacterNum += yyleng;
	if(IS_OUT_) 
		coutLineLog(Row,"[分隔符]",6,yytext,yyleng);
}

{string_}  { 
	StringNum++;
	AllCharacterNum += yyleng;
	if(IS_OUT_) 
		coutLineLog(Row,"[字符串]",0,yytext,yyleng);
	for(int i =0;;i++){
		char c = *(yytext+i);
		if(c=='\n') Row++;
		else if(c=='\0') break;
	}
 }

{char_} { 
	CharNum++;
	AllCharacterNum += yyleng;
	if(IS_OUT_) 
		coutLineLog(Row,"[单字符]",0,yytext,yyleng);
}

\n { 
	AllCharacterNum += yyleng;
	if(IS_OUT_ && IS_OUT_LINKBREAK) 
		coutLineLog(Row,"[换行符]",0,"\\n",yyleng);
	Row++;
}

{lineComment} {
	LineCommentNum++;
	AllCharacterNum += yyleng;
	if(IS_OUT_) 
		coutLineLog(Row,"[行注释]",4,yytext,yyleng);
}

{linesComment} {
	LinesCommentNum++; 
	AllCharacterNum += yyleng;
	if(IS_OUT_)
		coutLineLog(Row,"[块注释]",4,yytext,yyleng);
	for(int i=0;;i++){
		char c = *(yytext+i);
		if(c=='\n') Row++;
		else if(c=='\0') break;
	}
}

{space} {  
	AllCharacterNum += yyleng;
	if(IS_OUT_ && IS_OUT_SPACE){
		coutLineLog(Row,"[空白块]",0,yytext,yyleng);
	}
}

{error} {
	AllCharacterNum += yyleng;
	recordError(Row);
	ErrorNum++;
	if(IS_OUT_){
		coutLineLog(Row,"[错误串]",1,yytext,yyleng);
	}
}

%%


int main(int args, char*argv[]){
	
	if(args==1){
		cout<<"需要文件名做参数"<<endl;
		return 0;
	}
	else if(args==2){
		yyin = fopen(argv[1], "r");
		if (yyin == NULL){
			cout<<"读取文件失败"<<endl;
			return 0;
		}
	}
	else if(args==3){
		int srcIndex = 0;
		if(isEqual(argv[1],"-h")){
			srcIndex = 2;
		}
		else if(isEqual(argv[2],"-h")){
			srcIndex = 1 ;
		}else{
			cout<<"参数错误"<<endl;
			return 0;
		}
		IS_OUT_COLOR = 1;
		yyin = fopen(argv[srcIndex], "r");
		// fopen_s(&yyin, argv[srcIndex], "r");
		if (yyin == NULL){
			cout<<"读取文件失败"<<endl;
			return 0;
		}
	}
	if(IS_OUT_){
		cout << std::setw(8) << std::left<<"[行号]";
		cout << std::setw(8) << std::left<<"[数量]";
		cout << std::setw(12) << std::left<<"[类别]";
		cout << std::setw(20) << std::left<<"[代码]"<< endl;
	}
		//printf("[行号]\t[类别 ]\t\t代码\t\t数量 \t \n");
	cout << "------------------------------------------------------"<< endl;
	yylex();
	if(IS_OUT_)
		cout << "------------------------------------------------------"<< endl;
	fclose(yyin);

	// cout << "词法分析结果统计:" << endl;
	cout << std::setw(40) << std::left << "<源文件词法分析数据统计>:" << endl;
	cout << std::setw(40) << std::left << "文件总字符数:" << AllCharacterNum << endl;
	cout << std::setw(40) << std::left << "代码总行数:" << Row << endl;
	cout << std::setw(40) << std::left << "浮点数总数:" << FloatNumerNum << endl;
	cout << std::setw(40) << std::left << "整形数总数:" << IntNumberNum << endl;
	cout << std::setw(40) << std::left << "关键字总数:" << KeyWordNum << endl;
	cout << std::setw(40) << std::left << "分隔符总数:" << SeparatorNum << endl;
	cout << std::setw(40) << std::left << "操作符总数:" << OperatorNum << endl;
	cout << std::setw(40) << std::left << "行注释总数:" << LineCommentNum << endl;
	cout << std::setw(40) << std::left << "块注释总数:" << LinesCommentNum << endl;
	cout << std::setw(40) << std::left << "标识符总数:" << VariableNum << endl;
	cout << std::setw(40) << std::left << "字符串总数:" << StringNum << endl;
	cout << std::setw(40) << std::left << "单个字符总数:" << CharNum << endl;
	cout << std::setw(40) << std::left << "错误总数:" << ErrorNum << endl;
	cout << std::setw(40) << std::left << "发生错误的行号:";
	for (int row = 0; row < ErrorNum; row++)
		cout << ErrorRow[row] << ", ";

	cout << endl;
	// system("pause");
	
	return 0;
}