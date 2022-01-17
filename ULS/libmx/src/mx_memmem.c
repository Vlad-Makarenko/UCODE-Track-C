#include "libmx.h"

void *mx_memmem(const void *big, size_t big_len, const void *little, size_t little_len) {
    
    if ( big_len < little_len || big_len < 0 || little_len < 0) {
       return NULL;
    }

    unsigned char *haystack = (unsigned char *)big;
    unsigned char *needle = (unsigned char *)little;
    while (*haystack) {
        if (mx_memcmp(haystack, needle, little_len) == 0)  {
            return haystack;
        }
        haystack++;
    }
    
    return NULL;

}

