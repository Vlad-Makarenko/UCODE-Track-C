#include "libmx.h"

void *mx_memccpy(void *restrict dst, const void *restrict src, int c, size_t n) {
    unsigned char *destination = (unsigned char *)dst;
    unsigned char *source = (unsigned char *)src;
    unsigned char stop = (unsigned char) c;
    for (size_t i = 0; i < n; i++) {
        destination[i] = source[i];
        if(source[i] == stop){
            return (void*)&(((unsigned char *)dst)[i + 1]);
        }
    }

    return NULL;
}
