#include "libmx.h"

void *mx_memmove(void *dst, const void *src, size_t len) {
    unsigned char *buffer = malloc(len);
    buffer = mx_memcpy(buffer, src, len);
    dst = mx_memcpy(dst, buffer, len);
    free(buffer);
    return dst;
}
