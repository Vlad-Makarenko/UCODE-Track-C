#include "ush.h"

void default_export(){
    t_env_list *head = NULL;
    parse_to_env_list(&head);
    while (head){
        printf("%s=%s\n", head->name, head->value);
        head = head->next;
    }
    del_env_list(&head);
    Exit_Status = 0;

}

void set_export(char **command_lines){
    for(int idx = 1; command_lines[idx]; idx++){
        char *buf = strchr(command_lines[idx], '=');
        if(buf == NULL){
            continue;
        }
        char **splited_argv = mx_strsplit(command_lines[idx], '=');
        setenv(splited_argv[0], splited_argv[1], 1);
        mx_del_strarr(&splited_argv);
    }
}


void init_export(char **command_lines) {
    if(command_lines[1] == NULL) {
        default_export();
        return;
    }
    set_export(command_lines);
    Exit_Status = 0;

}

