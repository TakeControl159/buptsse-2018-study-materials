/*
*
*
*语法分析器 
*
*
*By TianYu 
*2018 12 20
*
*
*
*/

#include<stdlib.h>
#include<stdio.h>
#include<string.h>

/*移入或规约时压入分析栈的符号、移入或规约操作后转而进入的状态*/
int symbol,status;
/*定义分析栈*/
int analysis_stack [50];
/*ip为栈顶元素下标*/
int ip = -1;

/*将输入符号串w保存于数组中*/
char buffer[30];
/*将读入的字符串转换为代号形式*/
int code[30];
/*position为code数组的下标*/
int position = 0;
/*X为当前获取的输入符号的代号*/
int X;

/*循环标志*/
int flag = 1;

typedef struct{/*定义文法产生式的结构*/
    int Vn;/*文法产生式的左部非终结符的代码*/
    int Str[4];/*文法产生式右部的代码串*/
    int size;/*文法产生式右部的长度*/
}G;

G production[11] = {/*该文法的所有产生式*/
    {0},
    {101,{0,102},1},/*S -> E*/
    {102,{0,102,3,103},3},/*E -> E+T*/
    {102,{0,102,4,103},3},/*E -> E-T*/
    {102,{0,103},1},/*E -> T*/
    {103,{0,103,5,104},3},/*T -> T*F*/
    {103,{0,103,6,104},3},/*T -> T/F*/
    {103,{0,104},1},/*T -> F*/
    {104,{0,7},1},/*F -> id*/
    {104,{0,1,101,2},3},/*F -> (E)*/
    {104,{0,8},1},/*F -> num*/
};
int GOTO[17][5] = {/*LR分析表goto*/
    {0,0,1,2,3},/*0*/
    {0,0,0,0,0},/*1*/
    {0,0,0,0,0},/*2*/
    {0,0,0,0,0},/*3*/
    {0,0,0,0,0},/*4*/
    {0,0,11,2,3},/*5*/
    {0,0,0,0,0},/*6*/
    {0,0,0,12,3},/*7*/
    {0,0,0,13,3},/*8*/
    {0,0,0,0,14},/*9*/
    {0,0,0,0,15},/*10*/
    {0,0,0,0,0},/*11*/
    {0,0,0,0,0},/*12*/
    {0,0,0,0,0},/*13*/
    {0,0,0,0,0},/*14*/
    {0,0,0,0,0},/*15*/
    {0,0,0,0,0}/*16*/
};
int ACTION[17][9] = {/*LR分析表action*/
    {51,5,52,51,51,51,51,4,6},//0
    {999,53,52,7,8,0,0,53,53},//1
    {-4,53,-4,-4,-4,9,10,53,53},//2
    {-7,0,-7,-7,-7,-7,-7,0,0},//3
    {-8,0,-8,-8,-8,-8,-8,0,0},//4
    {0,5,52,51,51,51,51,4,6},//5
    {-10,0,-10,-10,-10,-10,-10,0,0},//6
    {51,5,52,51,51,51,51,4,6},//7
    {51,5,52,51,51,51,51,4,6},//8
    {51,5,52,51,51,51,51,4,6},//9
    {51,5,52,51,51,51,51,4,6},//10
    {0,53,16,7,8,0,0,53,53},//11
    {-2,53,-2,-2,-2,9,10,53,53},//12
    {-3,53,-3,-3,-3,9,10,53,53},//13
    {-5,0,-5,-5,-5,-5,-5,0,0},//14
    {-6,0,-6,-6,-6,-6,-6,0,0},//15
    {-9,0,-9,-9,-9,-9,-9,0,0}//16
};

void TRANS();/*将读入的buffer数组内容按字符转换为相应代号存入code数组中*/
void GetFromCode();/*取得当前输入符号串的元素*/
void PUSH(int A,int S);/*入栈操作*/
void POP();/*出栈操作*/
void SHITF();/*移入操作*/
void REDUCE();/*规约操作*/
void ACC();/*接受操作*/ 
void E1();/*错误处理*/
void E2();
void E3();
main()
{
    int c=1; 
    printf("请输入表达式,并以$结尾。例如：'a+b$'\n");
    scanf("%s",buffer);/*读入算术表达式，保存至buffer中*/
    printf("\n");
    TRANS();/*将字符型的buffer数组内容以字符为单位，转换为相应代号，保存至整型数组w中*/
    
    PUSH(0,0);/*状态S0入栈*/
    GetFromCode();//从输入缓冲区读取一个字符 
       
    while(flag){
        if( ACTION[analysis_stack[ip]][X] > 0 && ACTION[analysis_stack[ip]][X] <50 ){/*进行移入操作*/
            SHITF();
            GetFromCode();
        }
        else if( ACTION[analysis_stack [ip]][X] < 0 ){/*进行规约操作*/
            REDUCE();
        } 
        else if( ACTION[analysis_stack[ip]][X] == 999 ){/*分析成功*/
            ACC();
        } 
        else
        {
            switch(ACTION[analysis_stack[ip]][X])
            {
                case 51: E1();break;
                case 52: E2();GetFromCode();break;
                case 53: E3();GetFromCode();break;
            }
            }
    }
    
    system("pause");
    return 0;
}
void TRANS(){/*将读入的buffer数组内容按字符转换为相应代号存入w数组中*/
    int x=0,y=0;/*x为指向buffer数组的下标 */
    while(buffer[x]!='$'){
        if( buffer[x]>=48 && buffer[x]<=57 ){/*当前字符为数字，即num*/
            while( buffer[x]>=48 && buffer[x]<=57 ) x++;
            code[y++] = 8;/*在buffer的替身数组w中写入代表num的8,并且y后移*/
        }
        else if( (buffer[x]>=97 && buffer[x]<=122) || (buffer[x]>=65 && buffer[x]<=90) ){/*当前字符为字母，即id*/
            while( (buffer[x]>=97 && buffer[x]<=122) || (buffer[x]>=65 && buffer[x]<=90) ) x++;
            code[y++] = 7;/*在buffer的替身数组w中写入代表id的7，并且y后移*/
        }
        else{
            switch(buffer[x++]){/*当buffer中的字符为一下任意一种时，自动转换为相应的代号存入w中*/ 
                case '&': code[y++] = 0;break;
                case '(': code[y++] = 1;break;
                case ')': code[y++] = 2;break;
                case '+': code[y++] = 3;break;
                case '-': code[y++] = 4;break;
                case '*': code[y++] = 5;break;
                case '/': code[y++] = 6;break;
            }
        }
    }
    code[y] = 0;
}
void GetFromCode(){/*取得当前输入符号串的元素*/
    X = code[position++];
}
void PUSH(int A,int S){/*入栈操作*/
    ip++;/*将栈指针ip指向最新元素 */
    analysis_stack[ip] = A;/*将符号A移入栈顶*/
    ip++;
    analysis_stack[ip] = S;/*将状态S移入栈顶*/
};
void POP(){/*出栈操作*/
    ip--;/*弹出一个栈顶元素，栈指针ip下移，指向新的栈顶*/
    ip--;
};
void SHITF(){/*移入操作*/
    int x;
    x = ACTION[analysis_stack[ip]][X];/*查找goto表以确定当前移入操作所需移入的状态*/
    PUSH(X,x);/*将当前读入的字符与状态压入栈*/
    printf("s%d\tShift in.\n",x);
}
void REDUCE(){/*规约操作*/
    int x,y,z;
    x = -ACTION[analysis_stack[ip]][X];/*查找action表以确定当前规约操作，即用哪个产生式规约*/
    printf("r%d\tReduce by\t",x);
    switch(production[x].Vn){
        case 101: printf("S -> ");break;
        case 102: printf("E -> ");break;
        case 103: printf("T -> ");break;
        case 104: printf("F -> ");break;
    }
    for(int i = 1; i <= production[x].size; i++){
        POP();/*将栈中元素，按规约产生式的右部长度进行弹出操作*/
        switch(production[x].Str[i]){
            case 0: printf("$");break;
            case 1: printf("(");break;
            case 2: printf(")");break;
            case 3: printf("+");break;
            case 4: printf("-");break;
            case 5: printf("*");break;
            case 6: printf("/");break;
            case 7: printf("id");break;
            case 8: printf("num");break;
            case 101: printf("S");break;
            case 102: printf("E");break;
            case 103: printf("T");break;
            case 104: printf("F");break;
        }
    }
    printf("\n");
    y = GOTO[analysis_stack[ip]][production[x].Vn-100];/*查找goto表以确定规约完成后需要转换的状态*/
    PUSH(production[x].Vn,y);/*将规约产生式的左部压入栈中，并将相应的转移状态压入栈中*/
}
void ACC(){
    flag = 0;
    printf("Acc!\n");
}
void E1()
{//期待(或运算对象首字符，但出现运算符或者$
    printf("e1\t\t\t缺少运算对象,id压入栈\n"); 
    PUSH(7,4);
}
void E2()
{//括号不匹配，删掉右括号 
    printf("e2\t\t\t括号不匹配,删除右括号\n");
    
}
void E3()
{//期待运算符号，但出现(或运算对象 
    int pointer = position;
    switch(analysis_stack[ip])
    {
        case 1: PUSH(3,7);printf("e3\t\t\t缺少运算符,添加运算符至栈");break;
        case 2: case 12: case 13: PUSH(5,9);printf("e3\t\t\t缺少运算符,添加运算符至栈");break;
        case 11:
            if( code[pointer] >=3 && code[pointer] <=6 )//期待运算符号
            {PUSH(2,16);printf("e3\t\t\t缺少右括号,添加右括号至栈");}
            else if( code[pointer] >= 7 && code[pointer]<=8 )
            {PUSH(3,7);printf("e3\t\t\t缺少运算符,添加运算符至栈");}
            break;
    }
}

