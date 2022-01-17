#include "libmx.h"

int mx_get_substr_index(const char *str, const char *sub){
    if (str == NULL || sub == NULL) {
        return -2;
    }
    
    int len1 = mx_strlen(str);
    int len2 = mx_strlen(sub);

    if(len1 < len2){
        return -1;
    }

    for (int i = 0; i < len1; i++) {
        if(mx_strncmp(str, sub, len2) == 0){
            return i;
        }
        str++;
    }
    return -1;
}
