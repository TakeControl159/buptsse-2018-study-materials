#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Conio.h"

/******全局变量定义*******/
FILE* readp, * writep;             //文件指针
char token[30] = { 0 };          //存放每次扫描的结果
char keylist[32][20] = {         //C语言的32个关键字，按照字典序升序排列
    "auto", "break", "case", "char", "const", "continue",
    "default", "do", "double", "else", "enum", "extern",
    "float", "for", "goto", "if", "int", "long",
    "register", "return", "short", "signed", "sizeof", "static",
    "struct", "switch", "typedef", "union", "unsigned", "void",
    "volatile", "while"
};
char symbolList[100][5] = {      //运算符和分界符的表
    "+", "-", "*", "/", "<", "<=", ">", ">=", "=", "==", 
   "!=", "<<", ">>", "++", "--", "+=", "-=", "*=", "/=",
   "&=", "|=", ";", "(", ")", "^", ",", "\"", "\'", "&", 
   "&&", "|", "||", "%", "~", "<<", ">>", "[", "]", "{", 
   "}", "\\", ".", "\?", ":", "!"
};
char identifierTable[500][30] = { 0 };  //标识符表，默认为空
int identifierNum = 0;                  //标识符总数

int lineCount = 1;                //记录代码总行数
int charCount = -1;               //记录字符总数

int wordCount = 0;                //记录单词的个数
int stringCount = 0;
int numCount = 0;                 //记录常数的个数
int operatorCount = 0;            //记录运算符的个数
int delimiterCount = 0;           //记录界符的个数


char getChar();                //从文件中读入一个字符
void scan();                   //主函数，进行记号的识别
char scanFloat(char ch);       //子功能函数，识别整数和浮点数
char scanString(char ch);      //子功能函数，识别字符串结构
int isCKey();                  //子功能函数，判断一个字符串是否为C语言的关键字，如果是，返回该关键字在表中的位置，否则返回-1
void clearToken();             //清除程序中的缓冲区
int insertID();                //向标识符表中加入新的标识符，并返回标识符的地址（如果已经插入，则不进行插入操作）
int findSymbol(char str[]);    //在运算符和分界符表中查找符号，并返回在表中的地址
void printResult();            //在控制台中打印统计结果


int main() {
    char ch;
    char str[10] = "asfa\e\n\5";
    //从文件中读入源代码
    if ((readp = fopen("SourceCode.txt", "r")) == NULL) {
       printf("file cannot open \n");
       exit(0);
    }

    if ((writep = fopen("TokenStream.txt", "w")) == NULL) {
        printf("file cannot open \n");
        exit(0);
    }
    

    scan();
    printResult();
    if (fclose(readp) != 0) {
       printf("file cannot be closed \n");
    }
    if (fclose(writep) != 0) {
        printf("file cannot be closed \n");
    }
    system("pause");
    
    return 0;
}

//主函数，进行记号的识别
void scan() {
    char ch;
    ch = getChar();

    while (ch != EOF) {
        //ch是空白符：跳过所有的空白符
        if (isBlank(ch)) {
            while (isBlank(ch = getChar()));
        }
        //ch是字母：标识符 or 关键字
        else if (isLetter(ch)) {
            //扫描出完整的标识符
            int p = 0;
            do {
                token[p++] = ch;
                ch = getChar();
            } while (isDigit(ch) || isLetter(ch) || ch == '_');
            wordCount++;
            //判断标识符token是否为C语言关键字
            int addr;
            if ((addr = isCKey()) != -1) {
                
                fprintf(writep, "%s --- 关键字%d\n", token, addr);
            }
            else {
                //如果是标识符，将其插入符号表中
                addr = insertID();

                fprintf(writep, "%s --- 标识符%d\n", token, addr);
            }
            clearToken();
            
        }
        //ch是数字：整数 or 浮点数
        else if (isDigit(ch)) {
            ch = scanFloat(ch);
            clearToken();
        }
        else if (ch == '\"') {
            ch = scanString(ch);
        }
        //ch是其他字符：运算符 or 界符
        else if(ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == ';' || ch == '(' || ch == ')' || ch == '^'
            || ch == ',' || ch == '\'' || ch == '~' || ch == '#' || ch == '%' || ch == '['
            || ch == ']' || ch == '{' || ch == '}' || ch == '\\' || ch == '.' || ch == '\?' || ch == ':' 
            || ch == '=' || ch == '<' || ch == '>' || ch == '!' || ch == '&' || ch == '|'){
             
            //对ch进行分情况处理
            switch (ch) {
            case '#': {
                //预处理部分的内容，因此本行跳过
                while (1) {
                    ch = getChar();
                    if (ch == '\n' || ch == '\b') {
                        break;
                    }
                }
                ch = getChar();
                break;
            }
            case '/': {
                ch = getChar();
                switch (ch) {
                case '/': {
                    //单行注释结构，跳过该行内容
                    while (1) {
                        ch = getChar();
                        if (ch == '\n' || ch == '\b') {
                            break;
                        }
                    }
                    //ch = getChar();
                    break;
                }
                case '*': {
                    //多行注释结构，跳过后面的所有代码，直到出现'*/'
                    int flag = 0;        //flag用来标识上一个字符是否为*号
                    while (1) {
                        ch = getChar();
                        if (flag && ch == '/') {
                            //结束注释识别
                            break;
                        }
                        if (ch == '*') {
                            flag = 1;
                        }
                        else {
                            flag = 0;
                        }
                        
                    }
                    //ch = getChar();
                    break;
                }
                case '=': {
                    char str[] = "/=";
                    operatorCount++;
                    fprintf(writep, "/= --- 运算符%d\n", findSymbol(str));
                    //ch = getChar();
                    break;
                }
                default: {
                    char str[] = "/";
                    operatorCount++;
                    fprintf(writep, "/ --- 运算符%d\n", findSymbol(str));
                    break;
                }
                }
                ch = getChar();
                break;
            }
            case '=':
            case '*':
            case '%':
            case '!': {
                //识别= * % ! == *= %= !=
                token[0] = ch;
                ch = getChar();
                if (ch == '=') {
                    token[1] = ch;
                    ch = getChar();
                }
                operatorCount++;
                fprintf(writep, "%s --- 运算符%d\n", token, findSymbol(token));
                clearToken();

                break;
            }
            case '<':
            case '>':
            case '+':
            case '-': {
                //识别++ -- += -= + -
                token[0] = ch;
                ch = getChar();
                if (token[0] == ch || ch == '=') {
                    token[1] = ch;
                    ch = getChar();
                }
                operatorCount++;
                fprintf(writep, "%s --- 运算符%d\n", token, findSymbol(token));
                clearToken();
                break;
            }
            case '&':
            case '|': {
                //识别&& || &= |= & | << >> <= >= < >
                token[0] = ch;
                ch = getChar();
                if (token[0] == ch || ch == '=') {
                    token[1] = ch;
                    ch = getChar();
                }
                operatorCount++;
                fprintf(writep, "%s --- 运算符%d\n", token, findSymbol(token));
                clearToken();
                break;
            }
            case '~':
            case '^': {
                //其他只由一个字符组成的运算符
                char str[2] = { ch };
                operatorCount++;
                fprintf(writep, "%s --- 运算符%d\n", str, findSymbol(str));
                ch = getChar();
                break;
            }
            default: {
                //剩余的均为界符，且均只由一个字符组成
                char str[2] = { ch };
                delimiterCount++;
                fprintf(writep, "%s --- 界符%d\n", str, findSymbol(str));
                ch = getChar();
                break;
            }
            }
        }
        //出现C语言不允许的非法字符：报错
        else {
            printf("WARNING: 第 %d 行出现非法字符，忽略后继续分析...\n", lineCount);
            while (!isBlank(ch = getChar()));
        }
    }

    
}

//子功能函数，识别整数和浮点数
char scanFloat(char ch){
    //将整数部分扫描出来，放到缓冲区中
    int p = 0;
    do {
        token[p++] = ch;
        ch = getChar();
    } while (isDigit(ch));
    if (isLetter(ch) && ch !='e' &&  ch != 'E') {
        printf("WARNING: 第 %d 行出现非法字符，忽略后继续分析...\n", lineCount);
        while (!isBlank((ch = getChar())));
        return ch;
    }
    //num1存放整数部分，num2存放小数部分，num3存放指数部分
    int num1 = 0, num3 = 0;
    double num2 = 0;
    for (int i = 0; i < strlen(token); i++) {
        char temp = token[i];
        num1 = num1 * 10 + (temp - '0');
    }
    clearToken();
    if (ch == '.') {    //识别到小数点，说明该数有小数部分
        //将小数部分扫描出来，放到缓冲区中
        int p = 0;
        while (isDigit((ch = getChar()))) {
            token[p++] = ch;
        }
        if (p == 0) {
            //小数点后面没有数字，报错
            printf("WARNING: 第 %d 行出现非法字符，忽略后继续分析...\n", lineCount);
            while (!isBlank((ch = getChar())));
            return ch;
        }
        else {
            for (int i = strlen(token) - 1; i >= 0; i--) {
                char temp = token[i];
                num2 = (num2 + (temp - '0')) / 10.0;
            }
            clearToken();
        }
    }
    if (ch == 'e' || ch == 'E') {
        //指数部分
        int signal = 1;
        int p = 0;
        ch = getChar();
        if (ch == '+' || ch == '-') {
            if (ch == '-') {
                signal = -1;
            }
            ch = getChar();
            if (!isDigit(ch)) {
                printf("WARNING: 第 %d 行出现非法字符，忽略后继续分析...\n", lineCount);
                while (!isBlank((ch = getChar())));
                return ch;
            }
            else {
                token[p++] = ch;
            }
        }
        else if (isDigit(ch)) {
            token[p++] = ch;
        }
        else {
            printf("WARNING: 第 %d 行出现非法字符，忽略后继续分析...\n", lineCount);
            while (!isBlank((ch = getChar())));
            return ch;
        }

        while (isDigit((ch = getChar()))) {
            token[p++] = ch;
        }
        for (int i = 0; i < strlen(token); i++) {
            char temp = token[i];
            num3 = num3 * 10 + (temp - '0');
        }
        num3 = num3 * signal;
    }
    clearToken();
    numCount++;
    if (num2 == 0) {
        int num = num1 * (int)(pow(10, num3));
        fprintf(writep, "%d --- 整常数\n", num);
    }
    else {
        double num = (num1 + num2) * pow(10, num3);
        fprintf(writep, "%.2f --- 浮点数\n", num);
    }
    return ch;
}

char scanString(char ch){
    //将整数部分扫描出来，放到缓冲区中
    int p = 0;
    token[p++] = ch;
    while (1) {
        ch = getChar();
        token[p++] = ch;
        if (ch == '\"') {
            break;
        }
    }
    stringCount++;
    fprintf(writep, "%s --- 字符串\n", token);
    clearToken();
    ch = getChar();
    return ch;
}

int insertID() {
    int isExist = 0;
    for (int i = 0; i < identifierNum; i++) {
        if (strlen(token) == strlen(identifierTable[i])) {
            int flag = 1;
            for (int j = 0; j < strlen(token); j++) {
                if (token[j] != identifierTable[i][j]) {
                    flag = 0;
                    break;
                }
            }
            if (flag) {
                isExist = 1;
                return i;
            }
        }
    }
    //如果token未在表中，将其插入表中
    if (!isExist) {
        for (int i = 0; i < strlen(token); i++) {

            identifierTable[identifierNum][i] = token[i];
        }
        identifierNum++;
        return identifierNum - 1;
    }
    return -1;
}

int findSymbol(char str[]){
    for (int i = 0; i < 50; i++) {
        if (strlen(str) == strlen(symbolList[i])) {
            int flag = 1;
            for (int j = 0; j < strlen(str); j++) {
                if (str[j] != symbolList[i][j]) {
                    flag = 0;
                    break;
                }
            }
            if (flag) {
                return i;
            }
        }

    }
    return -1;
    return 0;
}

void printResult(){
    printf("\n\n\n/---------统计结果----------/\n");
    printf("代码总行数: %d\n", lineCount);
    printf("代码中字符总数: %d\n\n", charCount);
    printf("代码中每种记号的个数：\n");
    printf("\t单词: %d\n", wordCount);
    printf("\t字符串: %d\n", stringCount);
    printf("\t无符号数: %d\n", numCount);
    printf("\t运算符: %d\n", operatorCount);
    printf("\t界符: %d\n", delimiterCount);

    printf("/---------标识符表----------/\n");
    for (int i = 0; i < identifierNum; i++) {
        printf("%2d ------- %s\n", i, identifierTable[i]);
    }
    
}

int isCKey() {
    for (int i = 0; i < 32; i++) {
        if (strlen(token) == strlen(keylist[i])) {
            int flag = 1;
            for (int j = 0; j < strlen(token); j++) {
                if (token[j] != keylist[i][j]) {
                    flag = 0;
                    break;
                }
            }
            if (flag) {
                return i;
            }
        }
        
    }
    return -1;
}

char getChar() {
    char ch = fgetc(readp);
    if (!isBlank(ch) && ch != EOF) {
        charCount++;
    }
    
    if (ch == '\n' || ch == '\b') {
        lineCount++;
    }
    return ch;
}

void clearToken() {
    int l = strlen(token);
    for (int i = 0; i < l; i++) {
        token[i] = 0;
    }
}