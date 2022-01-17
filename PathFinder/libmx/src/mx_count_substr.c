#include "libmx.h"

int mx_count_substr(const char *str, const char* sub){
    int res = 0;
    if (str == NULL || sub == NULL){
        return -1;
    }
    if (mx_strcmp(sub, "") == 0) {
        return 0;
    }
    
    if(mx_strlen(str) < mx_strlen(sub)){
        return res;
    }
    while (*str != '\0'){
        str = mx_strstr(str, sub);
        if (str != NULL) {
            str++;
            res++;
        } else {
            break;
        }
    }
    return res;
}

