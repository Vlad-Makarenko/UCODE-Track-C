#include "libmx.h"

char *mx_strndup(const char *s1, size_t n){
    char *new_str = NULL;
    size_t new_len = mx_strlen(s1);

    if (n < new_len){
        new_len = n;
    }

    new_str = mx_strnew(new_len);
    mx_strncpy(new_str, s1, new_len);

    return new_str;
}
