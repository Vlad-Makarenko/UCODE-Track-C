#include <stdlib.h>
#include <stdio.h>

char *mx_strnew(const int size);

char *mx_strcpy(char *dst, const char *src);

int mx_strlen(const char *s);

char *mx_strdup(const char *s1) {

    int size = mx_strlen(s1);
    char *duplicate = mx_strnew(size);
    mx_strcpy(duplicate, s1);

    return duplicate;
}

