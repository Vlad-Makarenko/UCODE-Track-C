#include "ush.h"

char * read_line_from_terminal(void) {
    char * line = malloc(PATH_MAX), * linep = line;
    size_t lenmax = PATH_MAX, len = lenmax;
    int c;

    if(line == NULL)
        return NULL;

    for(int i = 0;; i++) {
        c = fgetc(stdin);
        if(c == EOF || c == '\n') {
            if(c == EOF){
                mx_printstr("exit\n");
                exit(0);
            } else if(i == 0){
               return NULL;
            }else {
                break;
            }
        }

        if(--len == 0) {
            len = lenmax;
            char * linen = realloc(linep, lenmax *= 2);

            if(linen == NULL) {
                free(linep);
                return NULL;
            }
            line = linen + (line - linep);
            linep = linen;
        }

        if((*line++ = c) == '\n')
            break;
    }
    *line = '\0';
    return linep;
}

