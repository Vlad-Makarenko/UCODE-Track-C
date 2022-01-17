#include "libmx.h"


void *mx_realloc(void *ptr, size_t size){
    if(ptr == 0){
        return malloc(size);
    }
    size_t size_ptr = malloc_size (ptr);
    if(size <=  size_ptr){
        return ptr;
    }

    void *new_mem = malloc(size);

    if (!new_mem) {
        return NULL;
    }

    mx_memcpy(new_mem, ptr, size_ptr);
    free(ptr);

    return new_mem;


}
