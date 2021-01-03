@echo off
flex Calculator.l
bison -d Calculator.y
g++ -fexec-charset=GB2312 -finput-charset=utf-8 lex.yy.c Calculator.tab.c -o Calculator