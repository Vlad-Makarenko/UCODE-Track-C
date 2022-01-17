#include "libmx.h"

char *mx_del_extra_spaces(const char *str){
    if (str == NULL){
        return NULL;
    }
    char *newStr = mx_strtrim(str);
    char *temp = mx_strnew(mx_strlen(newStr));
    int resIdx = 0;
    bool isOneSpace = false;
    for (int i = 0; i < mx_strlen(newStr); ++i) {
        if (!mx_isspace(newStr[i])){
            temp[resIdx] = newStr[i];
            resIdx++;
            isOneSpace = true;
        } else if (mx_isspace(newStr[i]) && isOneSpace){
            temp[resIdx] = ' ';
            resIdx++;
            isOneSpace = false;
        }
    }
    char *res = mx_strnew(resIdx);
    mx_strncpy(res, temp, resIdx);
    mx_strdel(&temp);
    mx_strdel(&newStr);
    return res;
}

