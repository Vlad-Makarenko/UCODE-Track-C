#include "ush.h"



t_env * create_env(bool i, bool P, bool u){
    t_env *new_node = malloc(sizeof(struct s_env_flags));

    new_node->i = i;
    new_node->P = P;
    new_node->u = u;

    return new_node;
}


t_env_list *create_env_list(char *name, char *value){
    t_env_list *new_node = malloc(sizeof(struct s_env_list));

    new_node->name = mx_strdup(name);
    new_node->value = mx_strdup(value);
    new_node->next = NULL;

    return new_node;
}

void push_back_env_list( t_env_list **head, char *name, char *value){
    t_env_list  *new_node = create_env_list(name, value);

    if (*head == NULL || head == NULL){
        *head = new_node;
        return;
    }

    t_env_list *temp = *head;
    while (temp->next){
        temp = temp->next;
    }
    temp->next = new_node;
}

int size_env_list(t_env_list* head) {
    int size = 0;
    while (head != NULL) {
        size++;
        head = head->next;
    }
    return size;
}


void del_env_list(t_env_list **head){
    t_env_list *to_del = *head;
    while (to_del){
        mx_strdel(&to_del->name);
        mx_strdel(&to_del->value);
        t_env_list *temp = to_del;
        to_del = to_del->next;
        free(temp);
    }
    
}

t_env* parse_to_env_flags(char **argv){

    char *error_line = mx_strdup("env: illegal option -- ");
    if (argv[1] && argv[1][0] == '-') {

        t_env *env = create_env(false, false, false);
        for (int i = 1; argv[1][i]; i++){

            switch (argv[1][i]) {
                case 'i':

                    env->i = true;
                    env->u = false;
                    env->P = false;
                    break;
                case 'P':
                    env->P = true;
                    env->i = false;
                    env->u = false;
                    if(argv[2] == NULL){
                        mx_printerr("env: option requires an argument -- ");
                        mx_printcharerr(argv[1][i]);
                        mx_printerr("\nusage: env [-i] [-P utilpath] [-u name]\n           [name=value ...] [utility [argument ...]]\n");
                        mx_strdel(&error_line);
                        env->P = false;   
                    }
                    break;
                case 'u':
                    env->u = true;
                    env->i = false;
                    env->P = false;
                    if(argv[2] == NULL){
                        mx_printerr("env: option requires an argument -- ");
                        mx_printcharerr(argv[1][i]);
                        mx_printerr("\nusage: env [-i] [-P utilpath] [-u name]\n           [name=value ...] [utility [argument ...]]\n");
                        mx_strdel(&error_line);
                        env->u = false;    
                    }
                    break;
                default:
                    mx_printerr(error_line);
                    mx_printcharerr(argv[1][i]);
                    mx_printerr("\nusage: env [-i] [-P utilpath] [-u name]\n           [name=value ...] [utility [argument ...]]\n");
                    mx_strdel(&error_line);
                    break;
            }
        }

        return env;
    }else {
        return NULL;
    }
}

void parse_to_env_list(t_env_list **head){
    for (int i = 0; environ[i]; i++) {
        int size_of_name = mx_get_char_index(environ[i], '=');
        char *name = mx_strndup(environ[i], size_of_name);
        char *value = environ[i] + size_of_name + 1;
        push_back_env_list(head, name, value);
        mx_strdel(&name);
    }  
    
    t_env_list *temp = *head;
    while (temp->next) {
        if(strcmp(temp->name, "_") == 0){
            mx_strdel(&temp->value);
            temp->value = mx_strdup("env");
        }
        temp = temp->next;
    }
}

void init_env(char **command_lines){

    hold_esc_symbs(&command_lines);

    t_env *env_flags = parse_to_env_flags(command_lines);
    

    if (env_flags)  {

        if (env_flags->i) {
            int p_id = fork();
            if(p_id == 0){
                // environ = NULL;
                make_process(command_lines, command_lines[0]); // slomal?
            } else {
                add_job(command_lines[0], p_id);
            }
        } else if (env_flags->u){
            char *temp = getenv(command_lines[2]);
            if(temp){
                unsetenv(command_lines[2]);
            }else {
                fprintf(stderr, "Set the environmental variable %s\n", command_lines[2]);
                return;
            }
            if(command_lines[3] == NULL){
                for(int i = 0; environ[i]; i++){
                    printf("%s\n", environ[i]);
                }
                Exit_Status = 0;
                return;
            }
            produce_job(command_lines + 3, command_lines[3], command_lines[3]);
            Exit_Status = 0;
        } else if (env_flags->P){
            if(command_lines[3] == NULL){
                for(int i = 0; environ[i]; i++){
                    printf("%s\n", environ[i]);
                }
                Exit_Status = 0;
                return;
            }
            int p_id = fork();
            if (p_id == 0) {
                int flag = 0;
                char *command = mx_strnew(PATH_MAX);
                command = mx_strcpy(command, command_lines[2]);
                command = mx_strcat(command, command_lines[3]);
                flag = execve(command, command_lines + 3, environ);
                free(command);
                if (flag != -1)
                    exit(0);

                mx_printerr("env: ");
                mx_printerr(command_lines[3]);
                mx_printerr(": No such file or directory\n");
                exit(1);
            } else {
                add_job(command_lines[3], p_id);
            }
            
        }
        
    }else {
        t_env_list *head = NULL;
        parse_to_env_list(&head);
        while (head){
            printf("%s=%s\n", head->name, head->value);
            head = head->next;
        }
        del_env_list(&head);
        Exit_Status = 0;
    }

}



