#include "libmx.h"

char *mx_strtrim(const char *str){
    if (str  == NULL){
        return NULL;
    }
    int count = 0;
    while (mx_isspace(*str)) {
        str++;
    }
    for (int i = mx_strlen(str) - 1; mx_isspace(*(str + i)); --i) {
        count++;
    }
    char * res = mx_strnew(mx_strlen(str) - count);
    mx_strncpy(res, str, mx_strlen(str) - count);
    return res;
}


