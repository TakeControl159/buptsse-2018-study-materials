@echo off
lex lex.l
g++ -fexec-charset=GB2312 -finput-charset=utf-8 lex.yy.c -o lexAna