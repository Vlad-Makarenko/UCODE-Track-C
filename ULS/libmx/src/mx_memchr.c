#include "libmx.h"

void *mx_memchr(const void *s, int c, size_t n){
    unsigned char *destination = (unsigned char *)s;
    unsigned char stop = (unsigned char) c;
    for (size_t i = 0; i < n; i++) {
        if(destination[i] == stop){
            return (void*)&(((unsigned char *)s)[i]);
        }
    }
    return NULL;
}

