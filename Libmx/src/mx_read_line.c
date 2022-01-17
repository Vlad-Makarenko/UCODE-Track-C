#include "libmx.h"


int mx_read_line ( char **lineptr, size_t buf_size, char delim, const int fd){
    if (fd < 1) {
        return -2;
    }

    int result = 0;
    buf_size = 1;
    int byte;
    char *if_not_found = *lineptr;
    char *temp;
    *lineptr = NULL;
    char *buf = mx_strnew(buf_size);
    while ((byte = read(fd, buf, buf_size)) > 0) {
        if(mx_get_char_index(buf, delim) >= 0){

            buf[mx_get_char_index(buf, delim)] = '\0';

            temp = *lineptr;
            *lineptr = mx_strjoin(*lineptr, buf);
            mx_strdel(&temp);  

            result += mx_strlen(buf);

            mx_strdel(&if_not_found);
            mx_strdel(&buf);

            return result;
        }

        temp  = *lineptr; 
        *lineptr = mx_strjoin(*lineptr, buf);
        mx_strdel(&temp);  

        result += byte;
    }
    
    if (result == 0) {
        *lineptr = if_not_found;
        mx_strdel(&buf);

        if (byte == -1) {
            return -2;
        } else {
            return -1;
        }
    }

    mx_strdel(&buf);
    return result;

}

