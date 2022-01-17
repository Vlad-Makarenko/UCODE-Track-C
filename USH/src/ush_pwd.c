#include "ush.h"

t_pwd * create_pwd(bool L, bool P){
    t_pwd *new_node = malloc(sizeof(struct s_pwd_flags));

    new_node->L = L;
    new_node->P = P;

    return new_node;
}

t_pwd* parse_to_pwd_flags(char **argv){
    t_pwd *pwd = create_pwd(false, false);

    if (argv[1] && argv[1][0] == '-') {
        char *error_line = mx_strdup("pwd: bad option: ");
        for (int n = 1; argv[1][n]; n++){
            switch (argv[1][n]) {
                case 'L':
                    pwd->L = true;
                    pwd->P = false;
                    break;
                case 'P':
                    pwd->P = true;
                    pwd->L = false;
                    break;
                default:
                    fprintf(stderr, "%s%c\n", error_line, argv[1][n]);
                    mx_strdel(&error_line);
                    Exit_Status = 1;
                    return NULL;
                    break;
            }
        }
        mx_strdel(&error_line);
        return pwd;
    }else {
        Exit_Status = 0;
        return pwd;
    }
}

int get_slesh(char *str) {
    if (str == NULL) return -2;

    for (int i = mx_strlen(str); ; i--) {
        if (str[i] == '/') return i;
        if (i == 0) break;
    }

    return -1;
}

char *get_pwd(char *environ_pwd){
    char *pwd = NULL;
    getcwd(pwd, INT_MAX);
    if(pwd == NULL){
        char *temp = NULL;
        temp = realpath(environ_pwd, NULL);

        pwd = (temp != NULL && temp[0] == '\0') ? mx_strndup ( environ_pwd, get_slesh(environ_pwd) + 1) : mx_strjoin(pwd, temp);
        
        mx_strdel(&temp);
    }
    return pwd;
}

void init_pwd(char **command_lines){
    t_pwd *flags = parse_to_pwd_flags (command_lines);
    if(flags == NULL){
        return;
    }

    char *pwd = NULL;

    char *environ_pwd = getenv("PWD");

    if(flags->P){
        pwd = get_pwd(environ_pwd);

    } else {
        pwd = mx_strdup(environ_pwd);

    }
    
    printf("%s\n", pwd);

    mx_strdel(&pwd);
    Exit_Status = 0;
}


