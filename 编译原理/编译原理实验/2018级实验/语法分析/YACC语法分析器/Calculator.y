%{
	#include <iostream>
	#include <string>
	#include <iomanip>
	using namespace std;
	
	int yyerror(char *s);
	int yylex();

	void showResult(string production, double num_, double num1, string op, double num2, bool isSingle){
		if(isSingle){
			cout << "运算表达式为: " << num_ << "=" << left << setw(5) << num1 << "  ";
			cout << "采用的产生式为: " << production << endl;
		}else{
			cout << "运算表达式为: " << num_ << "=" << num1 << op << left << setw(3) << num2 << "  ";
			cout << "采用的产生式为: " << production << endl;
		}
		return;
	}

%}

//设置属性类型 double
%define api.value.type {double}

/* token 声明 */
%token num 256
%token clend 263

%%
S : S E clend { cout << "计算结果为: " << $2 << endl; cout << "\n请输入一个算术表达式: "; }
  | S '\n'
  |
  ;

E : T       { $$ = $1; showResult("E->T", $$, $1, " ", 0, true);}
  | E '+' T { $$ = $1 + $3; showResult("E->E+T", $$, $1, "+", $3, false);}
  | E '-' T { $$ = $1 - $3; showResult("E->E-T", $$, $1, "-", $3, false);} 
  ;

T : F       { $$ = $1; showResult("T->F", $$, $1, " ", 0, true);}
  | T '*' F { $$ = $1 * $3; showResult("T->T*F", $$, $1, "*", $3, false);}
  | T '/' F { $$ = $1 / $3; showResult("T->T/F", $$, $1, "/", $3, false);} 
  ;

F : num { $$ = $1; showResult("F->num", $$, $1, " ", 0, true);}
  | '(' E ')' { $$ = $2; showResult("F->(E)", $$, $2, " ", 0, true);}
  ;

%%

int main()
{
	cout.setf(ios::right);
	cout << "请输入一个算术表达式: "; 
	yyparse();
}

int yyerror(char *s)
{
	fprintf(stderr, "语法错误: %s\n", s);
}