#include "Conio.h"

//ÅÐ¶ÏÊäÈëµÄ×Ö·ûÊÇ·ñÎªÊý×Ö
int isDigit(char ch) {
    if (ch >= '0' && ch <= '9') {
        return 1;
    }
    else {
        return 0;
    }
}

//ÅÐ¶ÏÊäÈëµÄ×Ö·ûÊÇ·ñÎª×ÖÄ¸£¨´óÐ´+Ð¡Ð´£©
int isLetter(char ch) {
    if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
        return 1;
    }

    else {
        return 0;
    }
}

//ÅÐ¶ÏÊäÈëµÄ×Ö·ûÊÇ·ñÎª¿Õ°×·û
int isBlank(char ch) {
    if (ch == ' ' || ch == '\t' || ch == '\b' || ch == '\n'){
        return 1;
    }
    else {
        return 0;
    }
}