#include "libmx.h"

char *mx_replace_substr (const char *str, const char *sub, const char *replace){
    if (!str || !sub || !replace) {
        return NULL;
    }
    int len_str = mx_strlen (str);
    int len_sub = mx_strlen(sub);
    int len_replace = mx_strlen (replace);
    char *result = NULL;
    
    int count_substr = mx_count_substr(str, sub);

    int size_res = len_str + (count_substr * len_replace - count_substr * len_sub);

    result = mx_strnew(size_res);

    int str_idx = 0;
    int res_idx = 0;
    for (; res_idx < size_res; ) {
        if(mx_strncmp(str + str_idx, sub, len_sub) == 0){
            mx_strncpy(result + res_idx, replace, len_replace);
            str_idx += len_sub;
            res_idx += len_replace;
        } else {
            result[res_idx] = str[str_idx];
            str_idx++;
            res_idx++;
        }

    }
    
    return result;
}
