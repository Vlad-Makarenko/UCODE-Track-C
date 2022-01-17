#include "libmx.h"

char *mx_strchr(const char *s, int c){
    for ( ; ; s++) {
        if (*s == c){
            return (char * ) s;
        } else if (*s == '\0') {
            if (*s == c){
                return (char * ) s;
            }else {
                return NULL;
            }
        }
    }
}



