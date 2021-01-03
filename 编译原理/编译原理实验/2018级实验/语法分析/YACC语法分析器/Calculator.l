%{
	#include "Calculator.tab.h"
	#include <iostream>
	#include <string>
	using namespace std;
	
int lexerror(string err)
{
	cout << "错误的字符" << err << endl;
}

%}

%%

"+"               { return '+'; }
"-"               { return '-'; }
"*"               { return '*'; }
"/"               { return '/'; }
"("               { return '('; }
")"               { return ')'; }

[0-9]+\.[0-9]+    { yylval = atof(yytext); return num; }
[0-9]+            { yylval = atof(yytext); return num; }

\n                { return clend; }
[ \t]             {  }
.                 { lexerror(yytext); }

%%

int yywrap() {
	return 1;
}