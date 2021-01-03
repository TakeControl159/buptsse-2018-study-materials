%option noyywrap
%{
#include<ctype.h>
#include<stdio.h>
#include<string>
#include<stdlib.h>
#include <iostream>
#include <map>
using namespace std;
int row=1;
int character_num=0;
int word_num=0;
int num_num=0;
int keyword_num=0;
int seperator_num=0;
int operator_num=0;
int error_num=0;

map<string, int> id_list;
map<string, int>::iterator iter;
string error_list[10];
int error_location[10];
int id_table(string token)
{
    iter = id_list.find(token);
    if (iter != id_list.end())
    { return iter->second; }
    else
    {
      id_list[token] = id_list.size();
      return id_list.size();
    }
}
void error_table(string token,int location)
{ 
      error_list[error_num]=token;
      error_location[error_num]=location;
      error_num++;
}
%}

digit[0-9]
id[a-zA-Z_][a-zA-Z0-9]*
whitespace [ \t]+
operator "+"|"-"|"*"|"/"|:=|">="|"<="|#|=|"=="|">"|"<"|"!="
delimiter "["|,|"."|;|"("|")"|"{"|"}"|"]"|:
reservedWord char|float|double|enum|int|short|long|void|signed|unsigned|struct|union|if|else|for|return|switch|case|break|continue|while|do|goto|default|auto|extern|register|static|const|sizeof|typedef|volatile
num {digit}+

%% 
{reservedWord} { keyword_num++; printf("%d\t%s\treservedWord\t-\n",row,yytext); }
{digit}+"."{digit}+(E("+"|-)?{digit}+)? { num_num++;printf("%d\tnum\tnum\t\t%s\n",row,yytext); }
{digit}+(E("+"|-)?{digit}+)? { num_num++;printf("%d\tnum\tnum\t\t%s\n",row,yytext);}

{digit}+"."({digit}+E("+"|-)?)? { error_table("digits error",row); }
{digit}+"." {error_table("digits error",row);}
{digit}+{id}  {error_table("id error",row); }

{id} {printf("%d\t%s\tid\t\t%d\n",row,yytext,id_table(yytext)); }

{operator} { operator_num++;printf("%d\t%s\toperator\t-\n",row,yytext); }
{delimiter} {seperator_num++; printf("%d\t%s\tseperator\t-\n",row,yytext);  }
\n { row++; }
{whitespace} { }
"/*".*"*/" { }
"//"[^\n]* { }
. { error_table("unknown error",row);  }
%%
void main(){
cout<<"The result is :"<<endl;
yyin=fopen("test.txt","r"); 
yylex(); 
fclose(yyin);
word_num=id_list.size()+num_num+keyword_num+seperator_num+operator_num;
cout<<endl;
cout << "rows:" << row << "\t\t" << "total words:" << word_num  << "\t\t"<<"error:"<<error_num<<endl;
cout<<"id:"<<id_list.size()<<endl;
cout<<"num:"<<num_num<<endl;
cout<<"keyword:"<<keyword_num<<endl;
cout<<"seperator:"<<seperator_num<<endl;
cout<<"operator num:"<<operator_num<<endl;
 cout<<endl<<"error list:"<<endl;
 for ( int i=0;i<error_num;i++)  
    {   
        cout<<error_list[i]<<"\t\t";
        cout<<error_location[i]<<endl;
    }  
 system("PAUSE");}