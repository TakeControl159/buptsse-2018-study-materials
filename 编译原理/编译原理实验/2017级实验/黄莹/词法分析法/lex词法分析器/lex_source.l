%option noyywrap
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <map>
using namespace std;
int row=1,col=1;
int ch_num;
int id_num;
int keyWord_num;
int num_times;
int bound_num;
int ope_num;
map<string, int> id_list;
map<string, int>::iterator ite;
int id_map(string token)
{

    ite = id_list.find(token);

    if (ite != id_list.end())
    {

        return ite->second;

    }

    else
    {

        id_list[token] = id_list.size()+1;

        return id_list.size();

    }

}
%}
DIGIT[0-9]
ID[a-zA-Z_][a-zA-Z0-9]*
whitespace [ \t]+

%%

auto { printf("识别单词 (%s, -)\n",yytext); col = col + yyleng; ch_num+=yyleng; keyWord_num++; }
bool { printf("识别单词 (%s, -)\n",yytext); col = col + yyleng; ch_num+=yyleng; keyWord_num++; }
break { printf("识别单词 (%s, -)\n",yytext); col = col + yyleng; ch_num+=yyleng; keyWord_num++; }
case { printf("识别单词 (%s, -)\n",yytext); col = col + yyleng; ch_num+=yyleng; keyWord_num++; }
catch { printf("识别单词 (%s, -)\n",yytext); col = col + yyleng; ch_num+=yyleng; keyWord_num++; }
char { printf("识别单词 (%s, -)\n",yytext); col = col + yyleng; ch_num+=yyleng; keyWord_num++; }
class { printf("识别单词 (%s, -)\n",yytext); col = col + yyleng; ch_num+=yyleng; keyWord_num++; }
const { printf("识别单词 (%s, -)\n",yytext); col = col + yyleng; ch_num+=yyleng; keyWord_num++; }
continue { printf("识别单词 (%s, -)\n",yytext); col = col + yyleng; ch_num+=yyleng; keyWord_num++; }
default { printf("识别单词 (%s, -)\n",yytext); col = col + yyleng; ch_num+=yyleng; keyWord_num++; }
delete { printf("识别单词 (%s, -)\n",yytext); col = col + yyleng; ch_num+=yyleng; keyWord_num++; }
do { printf("识别单词 (%s, -)\n",yytext); col = col + yyleng; ch_num+=yyleng; keyWord_num++; }
double { printf("识别单词 (%s, -)\n",yytext); col = col + yyleng; ch_num+=yyleng; keyWord_num++; }
enum { printf("识别单词 (%s, -)\n",yytext); col = col + yyleng; ch_num+=yyleng; keyWord_num++; }
else { printf("识别单词 (%s, -)\n",yytext); col = col + yyleng; ch_num+=yyleng; keyWord_num++; }
extern { printf("识别单词 (%s, -)\n",yytext); col = col + yyleng; ch_num+=yyleng; keyWord_num++; }
false { printf("识别单词 (%s, -)\n",yytext); col = col + yyleng; ch_num+=yyleng; keyWord_num++; }
float { printf("识别单词 (%s, -)\n",yytext); col = col + yyleng; ch_num+=yyleng; keyWord_num++; }
for { printf("识别单词 (%s, -)\n",yytext); col = col + yyleng; ch_num+=yyleng; keyWord_num++; }
friend { printf("识别单词 (%s, -)\n",yytext); col = col + yyleng; ch_num+=yyleng; keyWord_num++; }
goto { printf("识别单词 (%s, -)\n",yytext); col = col + yyleng; ch_num+=yyleng; keyWord_num++; }
if { printf("识别单词 (%s,-)\n",yytext); col = col + yyleng; ch_num+=yyleng; keyWord_num++; }
include { printf("识别单词 (%s, -)\n",yytext); col = col + yyleng; ch_num+=yyleng; keyWord_num++; }
inline { printf("识别单词 (%s, -)\n",yytext); col = col + yyleng; ch_num+=yyleng; keyWord_num++; }
int { printf("识别单词 (%s, -)\n",yytext); col = col + yyleng; ch_num+=yyleng; keyWord_num++; }
iostream { printf("识别单词 (%s, -)\n",yytext); col = col + yyleng; ch_num+=yyleng; keyWord_num++; }
long { printf("识别单词 (%s, -)\n",yytext); col = col + yyleng; ch_num+=yyleng; keyWord_num++; }
main { printf("识别单词 (%s, -)\n",yytext); col = col + yyleng; ch_num+=yyleng; keyWord_num++; }
namespace { printf("识别单词 (%s, -)\n",yytext); col = col + yyleng; ch_num+=yyleng; keyWord_num++; }
new { printf("识别单词 (%s, -)\n",yytext); col = col + yyleng; ch_num+=yyleng; keyWord_num++; }
private { printf("识别单词 (%s, -)\n",yytext); col = col + yyleng; ch_num+=yyleng; keyWord_num++; }
protected { printf("识别单词 (%s, -)\n",yytext); col = col + yyleng; ch_num+=yyleng; keyWord_num++; }
public { printf("识别单词 (%s, -)\n",yytext); col = col + yyleng; ch_num+=yyleng; keyWord_num++; }
read { printf("识别单词 (%s, -)\n",yytext); col = col + yyleng; ch_num+=yyleng; keyWord_num++; }
register { printf("识别单词 (%s, -)\n",yytext); col = col + yyleng; ch_num+=yyleng; keyWord_num++; }
return { printf("识别单词 (%s, -)\n",yytext); col = col + yyleng; ch_num+=yyleng; keyWord_num++; }
short { printf("识别单词 (%s, -)\n",yytext); col = col + yyleng; ch_num+=yyleng; keyWord_num++; }
signed { printf("识别单词 (%s, -)\n",yytext); col = col + yyleng; ch_num+=yyleng; keyWord_num++; }
sizeof { printf("识别单词 (%s, -)\n",yytext); col = col + yyleng; ch_num+=yyleng; keyWord_num++; }
static { printf("识别单词 (%s, -)\n",yytext); col = col + yyleng; ch_num+=yyleng; keyWord_num++; }
std { printf("识别单词 (%s, -)\n",yytext); col = col + yyleng; ch_num+=yyleng; keyWord_num++; }
structs { printf("识别单词 (%s, -)\n",yytext); col = col + yyleng; ch_num+=yyleng; keyWord_num++; }
switch { printf("识别单词 (%s, -)\n",yytext); col = col + yyleng; ch_num+=yyleng; keyWord_num++; }
this { printf("识别单词 (%s, -)\n",yytext); col = col + yyleng; ch_num+=yyleng; keyWord_num++; }
true { printf("识别单词 (%s, -)\n",yytext); col = col + yyleng; ch_num+=yyleng; keyWord_num++; }
try { printf("识别单词 (%s, -)\n",yytext); col = col + yyleng; ch_num+=yyleng; keyWord_num++; }
typedef { printf("识别单词 (%s, -)\n",yytext); col = col + yyleng; ch_num+=yyleng; keyWord_num++; }
union { printf("识别单词 (%s, -)\n",yytext); col = col + yyleng; ch_num+=yyleng; keyWord_num++; }
unsigned { printf("识别单词 (%s, -)\n",yytext); col = col + yyleng; ch_num+=yyleng; keyWord_num++; }
using { printf("识别单词 (%s, -)\n",yytext); col = col + yyleng; ch_num+=yyleng; keyWord_num++; }
virtual { printf("识别单词 (%s, -)\n",yytext); col = col + yyleng; ch_num+=yyleng; keyWord_num++; }
void { printf("识别单词 (%s, -)\n",yytext); col = col + yyleng; ch_num+=yyleng; keyWord_num++; }
volatile { printf("识别单词 (%s, -)\n",yytext); col = col + yyleng; ch_num+=yyleng; keyWord_num++; }
while { printf("识别单词 (%s, -)\n",yytext); col = col + yyleng; ch_num+=yyleng; keyWord_num++; }
write { printf("识别单词 (%s, -)\n",yytext); col = col + yyleng; ch_num+=yyleng; keyWord_num++; }
{DIGIT}+"."{DIGIT}+(E("+"|-)?{DIGIT}+)? { printf("识别单词 (num, %s)\n",yytext); col = col + yyleng; ch_num+=yyleng; num_times++;}
{DIGIT}+(E("+"|-)?{DIGIT}+)? { printf("识别单词 (num, %s)\n",yytext); col = col + yyleng; ch_num+=yyleng; num_times++;}
{DIGIT}+"."{DIGIT}+E("+"|-)? { printf("位于行%d，列%d\t%s-->出现错误\n",row,col,yytext); ch_num+=yyleng;}
{DIGIT}+"." { printf("位于行%d，列%d\t%s-->出现错误\n",row,col,yytext); ch_num+=yyleng;}
"<"+{ID}+".h>" { printf("识别单词 (%s, -)\n",yytext); col = col + yyleng; ch_num+=yyleng;}
["]+{ID}+".h"+["] { printf("识别单词 (%s, -)\n",yytext); col = col + yyleng; ch_num+=yyleng;}
{ID} { printf("识别单词 (id, %d)\n",id_map(yytext)); col = col + yyleng; ch_num+=yyleng; id_num++;}
{DIGIT}+{ID}+ { printf("位于行%d，列%d\t%s-->出现错误\n",row,col,yytext); ch_num+=yyleng;}
{whitespace} { }
"{" { printf("识别单词 (%s, -)\n",yytext); col = col + yyleng; ch_num+=yyleng; bound_num++;}
"}" { printf("识别单词 (%s, -)\n",yytext); col = col + yyleng; ch_num+=yyleng; bound_num++;}
"[" { printf("识别单词 (%s, -)\n",yytext); col = col + yyleng; ch_num+=yyleng; bound_num++;}
"]" { printf("识别单词 (%s, -)\n",yytext); col = col + yyleng; ch_num+=yyleng; bound_num++;}
; { printf("识别单词 (%s, -)\n",yytext); col = col + yyleng; ch_num+=yyleng; bound_num++;}
, { printf("识别单词 (%s, -)\n",yytext); col = col + yyleng; ch_num+=yyleng; bound_num++;}
"." { printf("识别单词 (%s, -)\n",yytext); col = col + yyleng; ch_num+=yyleng; bound_num++;}
"(" { printf("识别单词 (%s, -)\n",yytext); col = col + yyleng; ch_num+=yyleng; bound_num++;}
")" { printf("识别单词 (%s, -)\n",yytext); col = col + yyleng; ch_num+=yyleng; bound_num++;}
: { printf("识别单词 (%s, -)\n",yytext); col = col + yyleng; ch_num+=yyleng; bound_num++;}
# { printf("识别单词 (%s, -)\n",yytext); col = col + yyleng; ch_num+=yyleng; bound_num++;}
"'" { printf("识别单词 (%s, -)\n",yytext); col = col + yyleng; ch_num+=yyleng; bound_num++;}
"+" { printf("识别单词 (%s, -)\n",yytext); col = col + yyleng; ch_num+=yyleng; ope_num++;}
"-" { printf("识别单词 (%s, -)\n",yytext); col = col + yyleng; ch_num+=yyleng; ope_num++;}
"*" { printf("识别单词 (%s, -)\n",yytext); col = col + yyleng; ch_num+=yyleng; ope_num++;}
"/" { printf("识别单词 (%s, -)\n",yytext); col = col + yyleng; ch_num+=yyleng; ope_num++;}
"/*".*"*/" { printf("识别单词 (/*, -)\n"); printf("识别单词 (*/, -)\n"); col = col + yyleng; ch_num+=yyleng; bound_num+=2; }
"//"[^\n]* { printf("识别单词 (//, -)\n"); col = col + yyleng; ch_num+=yyleng; bound_num++; }
"%" { printf("识别单词 (%s, -)\n",yytext); col = col + yyleng; ch_num+=yyleng; ope_num++; }
">" { printf("识别单词 (%s, GT)\n",yytext); col = col + yyleng; ch_num+=yyleng; ope_num++;}
"<" { printf("识别单词 (%s, LT)\n",yytext); col = col + yyleng; ch_num+=yyleng; ope_num++;}
">=" { printf("识别单词 (%s, GE)\n",yytext); col = col + yyleng; ch_num+=yyleng; ope_num++;}
"<=" { printf("识别单词 (%s, LE)\n",yytext); col = col + yyleng; ch_num+=yyleng; ope_num++;}
"==" { printf("识别单词 (%s, EQ)\n",yytext); col = col + yyleng; ch_num+=yyleng; ope_num++;}
"-=" { printf("识别单词 (%s, -)\n",yytext); col = col + yyleng; ch_num+=yyleng; ope_num++;}
"+=" { printf("识别单词 (%s, -)\n",yytext); col = col + yyleng; ch_num+=yyleng; ope_num++;}
"*=" { printf("识别单词 (%s, -)\n",yytext); col = col + yyleng; ch_num+=yyleng; ope_num++;}
"/=" { printf("识别单词 (%s, -)\n",yytext); col = col + yyleng; ch_num+=yyleng; ope_num++;}
"!=" { printf("识别单词 (%s, NE)\n",yytext); col = col + yyleng; ch_num+=yyleng; ope_num++;}
= { printf("识别单词 (%s, assign-op)\n",yytext); col = col + yyleng; ch_num+=yyleng; ope_num++;}
"%=" { printf("识别单词 (%s, -)\n",yytext); col = col + yyleng; ch_num+=yyleng; ope_num++;}
& { printf("识别单词 (%s, -)\n",yytext); col = col + yyleng; ch_num+=yyleng; ope_num++;}
&& { printf("识别单词 (%s, -)\n",yytext); col = col + yyleng; ch_num+=yyleng; ope_num++;}
"|" { printf("识别单词 (%s, -)\n",yytext); col = col + yyleng; ch_num+=yyleng; ope_num++;}
"||" { printf("识别单词 (%s, -)\n",yytext); col = col + yyleng; ch_num+=yyleng; ope_num++;}
! { printf("识别单词 (%s, -)\n",yytext); col = col + yyleng; ch_num+=yyleng; ope_num++;}
"++" { printf("识别单词 (%s, -)\n",yytext); col = col + yyleng; ch_num+=yyleng; ope_num++;}
"--" { printf("识别单词 (%s, -)\n",yytext); col = col + yyleng; ch_num+=yyleng; ope_num++;}
~ { printf("识别单词 (%s, -)\n",yytext); col = col + yyleng; ch_num+=yyleng; ope_num++;}
"<<" { printf("识别单词 (%s, -)\n",yytext); col = col + yyleng; ch_num+=yyleng; ope_num++;}
">>" { printf("识别单词 (%s, -)\n",yytext); col = col + yyleng; ch_num+=yyleng; ope_num++;}
"?" { printf("识别单词 (%s, -)\n",yytext); col = col + yyleng; ch_num+=yyleng; ope_num++;}
\n { row++; col=0; }
. { printf("位于行%d，列%d\t%s-->出现错误\n",row,col,yytext); ch_num+=yyleng;}
%%
int main(void)
{
    errno_t err;
    err = fopen_s(&yyin, "testProgram.c", "r");
    yylex();
    printf("\n总行数：\t%d\t字符总数：\t%d" , row, ch_num);
    printf("\n各类单词个数：\n");
    printf("\nid个数：\t%d" , id_num);
    printf("\n数字个数：\t%d" , num_times);
    printf("\n关键字个数：\t%d" , keyWord_num);
    printf("\n分隔符个数：\t%d" , bound_num);
    printf("\n操作符个数：\t%d\n" , ope_num);
    system("pause");
}