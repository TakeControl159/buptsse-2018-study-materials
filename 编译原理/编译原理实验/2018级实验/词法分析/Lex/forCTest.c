#ifndef FORCTEST_H_
#define FORCTEST_H_

#define NOCAN 38

#include <malloc.h>
#include <stdio.h>
/*************************************************
 * // 文档说明 \\***
 * 本次测试用例尽量将C语言的稀奇古怪的特性进行覆盖
 * "By ZhangKang"
 *************************************************/

typedef struct newClass {
    int 123abc = 1 + 3; // 第一个错误
    double asdc = -1.3f;
    int x; // = 1;
} newClass;

void testNumbers(int x) {
    // 整形
    // 有符号
    short _ = 12;

    int __a_;
    int b_i1_ = 0xE * NOCAN;
    int c1 = -100, d = +1234;
    int e = 0234 % 17, f;

    long g = -403L;
    long long ___ = 234ll;
    // 无符号
    unsigned int _1_ = 3u + 4U;
    unsigned long h = 1100l;

    // 浮点型
    float i = 1.0 / 4;
    float l = .3f, m = 3.F - 0.4;
    double n = 0.3e-2;
    double o = -5.e0, p = 2.E02f;
    // 下面构造几个错误
    double q = 7.2fl;
    double r = 4.5e-3lf;
    double s = 12.23.43;
    double u = .45.65;
    return;
}

int _testString(int c[], char *e) {
    // 字符
    char ___ = '\n';
    char a[] = "'123'";

    // 字符串
    char *b = "s/* //\n */ //";

    char *c = "asdads\
    换行字符串\
              ";

    return (int)5.f;
}

float testStateMents() {
    int i = 0;
    while (i < 15 ? 1 : 0) {
        for (int j = 01; j <= i + 5; j++)
            if (j == 4)
                break;
        for (int j = 10; j >= 0; j--) {
            if (i == 2) {
                j -= 1;
            } else if (i != 4) {
                j--;
            } else {
                j = (j << 2) >> 2;
                continue;
            }
        }

        do {
            i += 1;
        } while (i < 0);
    }

label1:
    switch (i) {
    case 15:
        i %= 10;
        goto label1;
    case 5:
    case 6:
        i += 1;
        goto label1;
    default:

        break;
    }

    return 6.e-3l;
}

char *test_others() {
    // "函数指针"
    int(*p(void));

    // 操作符
    char *pt = (char *)malloc(sizeof(char) * 10);
    free(pt);
    return "\n\n";
}

// 这里是程序入口点
int main(int agrs, char *agrv) {
    int a[] = {1, 2, 3, 4};
    char *b = "10";
    int *c = &b;
    //testNumbers(0b10); // 二进制表示不是标准，有的编译器支持有的不支持

    _testString(a, *c);
    testStateMents();
    test_others();

    printf("Hello World");
    return 0;
}

#endif // FORCTEST_H_