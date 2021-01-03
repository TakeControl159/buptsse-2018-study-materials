1. lex.l
	Lex源程序
2. build.bat 
	windows平台下生成词法分析程序快捷脚本
3. lexAna.exe
	生成的词法分析程序。
4. forCTest.c
	测试用例

注意* 
	1. 由于编码问题，windows平台下测试用例文件必须使用GBK格式。
	2. 如果运行乱码或是异常，则是输出窗口的编码格式与程序不兼容。则在手动编译时需要指定参数 -fexec-charset=GBK
	3. 对于支持ASCII转义编码的命令行，可以使用 -h 高亮输出