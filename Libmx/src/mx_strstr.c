#include "libmx.h"

char *mx_strstr(const char *haystack, const char *needle){
    int len1 = mx_strlen(haystack);
    int len2 = mx_strlen(needle);
    if(len1 < len2){
        return NULL;
    }
    while(*haystack != '\0'){
        if(mx_strncmp(haystack, needle, len2) == 0){
            return (char *) haystack;
        }
        haystack++;
    }
    return NULL;
    }
