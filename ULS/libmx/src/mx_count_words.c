#include "libmx.h"

int mx_count_words(const char *str, char c){
    if (str == NULL){
        return -1;
    }

    int res = 0;
    int flag = 1;

    for (int i = 0; str[i]; i++) {
        if (str[i] == c) {
            flag = 1;
        } else if (flag == 1){
            flag = 0;
            res++;
        }
    }
    return res;
}
