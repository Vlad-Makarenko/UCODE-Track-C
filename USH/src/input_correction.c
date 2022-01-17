#include "ush.h"


void tilda_correction(char **command){

    tilda_positive(command);
    tilda_negative(command);
    tilda_slesh(command);
    tilda_foo(command);
    tilda(command);
    
}

void tilda_positive(char **command) {
    int pos;
    int len = mx_strlen(getenv("PWD"));
    if((pos = mx_get_substr_index(*command, "~+/")) == -1){
        return;
    }

    char * buffer = mx_strnew(PATH_MAX);
    mx_strncpy(buffer, *command, pos);
    mx_strncpy(buffer + pos, getenv("PWD"), len);

    if (buffer[len - 1 + pos] == '/' && (*command)[2 + pos] == '/') {
        buffer[len - 1 + pos] = '\0';
        len--;
    }
    
    mx_strncpy(buffer + len + pos, *command + 2 + pos, PATH_MAX - 2 - len - pos);
    mx_strdel(command);
    *command = mx_strdup(buffer);
    mx_strdel(&buffer);

    tilda_positive(command);
}


void tilda_negative(char **command){
    int pos;
    int len = mx_strlen(getenv("OLDPWD"));
    if((pos = mx_get_substr_index(*command, "~-/")) == -1){
        return;
    }

    char * buffer = mx_strnew(PATH_MAX);
    mx_strncpy(buffer, *command, pos);
    mx_strncpy(buffer + pos, getenv("OLDPWD"), len);
    mx_strncpy(buffer + len + pos, *command + 2 + pos, PATH_MAX - 2 - len - pos);
    
    mx_strdel(command);
    *command = mx_strdup(buffer);
    mx_strdel(&buffer);

    tilda_negative(command);
}

void tilda_slesh(char **command){
    int pos;
    int len = mx_strlen(getenv("HOME"));
    if((pos = mx_get_substr_index(*command, "~/")) == -1){
        return;
    }

    char * buffer = mx_strnew(PATH_MAX);
    mx_strncpy(buffer, *command, pos);
    mx_strncpy(buffer + pos, getenv("HOME"), len);
    mx_strncpy(buffer + len + pos, *command + 1 + pos, PATH_MAX - 1 - len - pos);
    
    mx_strdel(command);
    *command = mx_strdup(buffer);
    mx_strdel(&buffer);

    tilda_slesh(command);
}

void tilda_foo(char **command){
    int pos;
    int len = mx_strlen(getenv("HOME"));
    if((pos = mx_get_substr_index(*command, "~")) == -1 || (*command)[pos + 1] == ' ' || (*command)[pos + 1] == '\0' || !mx_isalpha(*(mx_strchr(*command, '~') + 1))){
        return;
    }

    char * buffer = mx_strnew(PATH_MAX);
    mx_strncpy(buffer, *command, pos);
    mx_strncpy(buffer + pos, getenv("HOME"), len);

    char *tmp = strrchr(*command, '/');
    if (tmp){
        mx_memset(tmp + 1, '\0', mx_strlen(tmp));
    } else {
        (*command)[0] = '/';
    }

    mx_strncpy(buffer + strlen(buffer), *command + 1 + pos, PATH_MAX - 1 - len - pos);
    
    mx_strdel(command);
    *command = mx_strdup(buffer);
    mx_strdel(&buffer);

    tilda_foo(command);
}

void tilda(char **command){
    int pos;
    int len = mx_strlen(getenv("HOME"));
    if((pos = mx_get_substr_index(*command, "~")) == -1){
        return;
    }

    char * buffer = mx_strnew(PATH_MAX);
    mx_strncpy(buffer, *command, pos);
    mx_strncpy(buffer + pos, getenv("HOME"), len);
    mx_strncpy(buffer + len + pos, *command + 1 + pos, PATH_MAX - 1 - len - pos);
    
    mx_strdel(command);
    *command = mx_strdup(buffer);
    mx_strdel(&buffer);

    tilda(command);
}
