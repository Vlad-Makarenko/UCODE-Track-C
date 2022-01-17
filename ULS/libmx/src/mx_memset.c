#include "libmx.h"

void *mx_memset(void *b, int c, size_t len){
    unsigned char *destination = (unsigned char *)b;
    unsigned char filler = (unsigned char) c;
    for (size_t i = 0; i < len; i++) {
        destination[i] = filler;
    }
     return b;
}
