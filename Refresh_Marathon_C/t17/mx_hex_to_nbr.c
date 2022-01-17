#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

bool mx_isdigit(int c){
    if (c > 47 && c < 58){
        return 1;
    } else {
        return 0;
    }
}


bool mx_isalpha(int c){
    if (((c > 64 && c < 91))
        || (c > 96 && c < 123)){
        return 1;
    }else{
        return 0;
    }
}

unsigned long mx_hex_to_nbr(const char *hex) {
    int len = 0;
    unsigned long res = 0;
    unsigned long base = 1;

    if (hex != NULL) {
        while (hex[len]) {
            len++;
        }
    }else {
        return 0;
    }

    for (int i = len - 1; i >= 0; i--) {
        if ( mx_isdigit(hex[i]) ) {
            res = res+ (hex[i] - '0') * base;
            base *= 16;
        } else if (mx_isalpha(hex[i])) {
            if (hex[i] >= 'A' && hex[i] <= 'F') {
                res = res+ (hex[i] - 'A' + 10) * base;
                base *= 16;
            } else if (hex[i] >= 'a' && hex[i] <= 'f') {
                res = res+ (hex[i] - 'a' + 10) * base;
                base *= 16;
            } else {
                return 0;
            }
        } else{
            return 0;
        }
    }
    return res;
}
