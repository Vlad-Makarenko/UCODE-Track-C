#include "ush.h"

t_echo * create_echo(bool n, bool e, bool E){
    t_echo *new_node = malloc(sizeof(struct s_echo_flags));

    new_node->n = n;
    new_node->e = e;
    new_node->E = E;
    new_node->is_default = false;

    return new_node;
}

t_echo* parse_to_echo_flags(char **argv){
    t_echo *echo = create_echo(false, false, false);

    if (argv[1] && argv[1][0] == '-') {
        char *error_line = mx_strdup("echo: illegal option -- ");
        for (int n = 1; argv[1][n]; n++){
            switch (argv[1][n]) {
                case 'n':
                    echo->n = true;
                    break;
                case 'e':
                    echo->e = true;
                    echo->E = false;
                    break;
                case 'E':
                    echo->E = true;
                    echo->e = false;
                    break;
                default:
                    echo->is_default = true;
                    return echo;
                    break;
            }
        }
        mx_strdel(&error_line);
        return echo;
    }else {
        echo->is_default = true;
        return echo;
    }
}

char *move_bslash(t_echo *flags, int size, char *string){
    char *result = mx_strnew(size + 1);
    int idx = 0;

    for (int i = 0; i <= size; i++) {
        if (string[i] == '\\' && string[i + 1] == '\\'){
            i++;
        }
        
        if (string[i] == '\\' && string[i + 1] == 'e') {
            i = string[i + 2] != '\\' ? +3 : +2;
            
        }
        
        if (string[i] == '\\' && string[i + 1] == 'c') {
            flags->n = true;
            break;
        }
        result[idx] = string[i];
        idx++;
    }
    result[idx] = '\0';
    return result;
}

void argv_correction(t_echo *flags, char **command_lines){
    char *buff = move_bslash(flags, strlen(command_lines[0]),  command_lines[0]);
    
        char *arr1[] = {"\\a","\\b","\\f","\\n","\\r","\\t","\\v", NULL};
        char *arr2[] =    {"\a", "\b", "\f", "\n", "\r", "\t", "\v", NULL};

        free(command_lines[0]);
        command_lines[0] = mx_strdup(buff);
        free(buff);

        for (int j = 0; arr1[j] != NULL; j++) {
            if (strstr(command_lines[0],arr1[j])) {
                
                buff = str_replace_one_more(command_lines[0],arr1[j], arr2[j]);
                
                command_lines[0] = mx_strdup(buff);
                free(buff);
            }
        }
}

void init_echo(char **argv, char **command_lines){
    if (strchr(*command_lines, '"') || strchr(*command_lines, '\'')){
        (void)0;
    } else {
        char *to_del = *command_lines;
        *command_lines = mx_del_extra_spaces(*command_lines);
        mx_strdel(&to_del);
    }
    *command_lines = mx_strtrim(*command_lines);

    t_echo *echo_flags = parse_to_echo_flags(argv);

    if (!echo_flags->E && strstr(command_lines[0], "\\") && mx_get_char_index(command_lines[0], '\"') != -1)  {
        
        argv_correction(echo_flags, command_lines);
        int amount = 0;
        if(!echo_flags->E){
            amount++;
        }
    } else if (!echo_flags->E && strstr(command_lines[0], "\\\\")) {

        remove_bslashes(command_lines[0]);
        argv_correction(echo_flags, command_lines);
        int amount = 0;
        if(!echo_flags->E){
            amount++;
        }
    }

    if (echo_flags->E)
        command_lines[0] = move_bslash(echo_flags, strlen(command_lines[0]), command_lines[0]);
    else {
        int screenable_double_quotes_number = count_substr(command_lines[0], "\\\"");
        int double_quotes_number = count_substr(command_lines[0], "\"");
        if ( (double_quotes_number - screenable_double_quotes_number) != 0 ) {
            show_bslashes(&(command_lines[0]));
        }
    }
    char **info = mx_strsplit(*command_lines, '>');
    char *buf = info[0];
    char *temp_buff = buf;
    for (int i = 3;*temp_buff != '\0' && *temp_buff != ' '; i++) {
        *temp_buff = '\0';
        for (;*(temp_buff + 1) != '\0';) {
            mx_swap_char(temp_buff, temp_buff + 1);
            temp_buff++;
        }
        temp_buff = buf;
        if(i > 0){
            i -= 4;
        }else {
            i += 3;
        }
}
    *temp_buff = '\0';
    for ( ;*(temp_buff + 1) != '\0'; ) {
        mx_swap_char(temp_buff, temp_buff + 1);
        temp_buff++;

    }
    temp_buff = buf;
    if (*temp_buff == '-' && !echo_flags->is_default) {
        for (; *temp_buff != '\0' && *temp_buff != ' '; ) {
            *temp_buff = '\0';
            for (;*(temp_buff + 1) != '\0';) {
                mx_swap_char(temp_buff, temp_buff + 1);
                temp_buff++;
            }
            temp_buff = buf;

        }
    }
    if (*temp_buff == ' ') {
        *temp_buff = '\0';
        for (; *(temp_buff + 1) != '\0';) {
            mx_swap_char(temp_buff, temp_buff + 1);
            temp_buff++;
        }
    }

    if(echo_flags->n) {
        bool this_is_typable = true;
        char *string = NULL;
        string = mx_strnew(PATH_MAX);
        if(info[1] != NULL) {
            FILE *file;
            char *pwd_from_env = mx_strdup(getenv("PWD"));
            char *pwd_from_env_new = strcat(pwd_from_env, SLESH);
            pwd_from_env_new = strcat(pwd_from_env_new, info[1]);
            file = fopen(pwd_from_env_new, "w");
            fprintf(file, "%s", buf);
            fclose(file);
            mx_strdel(&pwd_from_env);
            this_is_typable = false;
        } else {
            strcat(string, info[0]);
        }
        int amount = 0;
        bool is_not_odd = false;
        for (int idx_for_string = 0; string[idx_for_string]; idx_for_string++) {
            if (string[idx_for_string] == '"' || string[idx_for_string] == '\'') {
                for (int temp_idx_for_string = idx_for_string; string[temp_idx_for_string]; temp_idx_for_string++) {
                    string[temp_idx_for_string] = string[temp_idx_for_string + 1];
                }
                amount++;
                is_not_odd = true;
            } else if (string[idx_for_string] == '\\') {
                if (!is_not_odd) {
                    for (int temp_idx_for_string = idx_for_string; string[temp_idx_for_string]; temp_idx_for_string++) {
                        string[temp_idx_for_string] = string[temp_idx_for_string + 1];
                    }
                }
            }
        }
        
        if(amount % 2 == 0 || amount == 0 || amount == 2) {
            if(this_is_typable) {
                mx_printstr(string);
                if(echo_flags->is_default) 
                    mx_printchar('\n');
            }
        } else {
            fprintf(stderr, "Odd number of quotes.\n");
            mx_del_strarr(&info);
            Exit_Status = 1;
        }
    } else if (echo_flags->e || echo_flags->E) {
        bool this_is_typable = true;
        char *string = NULL;
        string = mx_strnew(PATH_MAX);
        if(info[1] != NULL) {
            FILE *file;
            char *pwd_from_env = mx_strdup(getenv("PWD"));
            char *pwd_from_env_new = strcat(pwd_from_env, SLESH);
            pwd_from_env_new = strcat(pwd_from_env_new, info[1]);
            file = fopen(pwd_from_env_new, "w");
            fprintf(file, "%s", buf);
            fclose(file);
            mx_strdel(&pwd_from_env);
            this_is_typable = false;
        } else {
            strcat(string, buf);
        }
        int amount = 0;
        bool is_not_odd = false;
        for (int idx_for_string = 0; string[idx_for_string]; idx_for_string++) {
            if (string[idx_for_string] == '"' || string[idx_for_string] == '\'') {
                for (int temp_idx_for_string = idx_for_string; string[temp_idx_for_string]; temp_idx_for_string++) {
                    string[temp_idx_for_string] = string[temp_idx_for_string + 1];
                }
                amount++;
                is_not_odd = true;
            } else if (string[idx_for_string] == '\\') {
                if (!is_not_odd) {
                    for (int temp_idx_for_string = idx_for_string; string[temp_idx_for_string]; temp_idx_for_string++) {
                        string[temp_idx_for_string] = string[temp_idx_for_string + 1];
                    }
                }
            }
        }
        if(amount % 2 == 0 || amount == 0 || amount == 2) {
            if(this_is_typable) {
                mx_printstr(string);
                mx_printstr("\n");
            }
        } else {
            fprintf(stderr, "Odd number of quotes.\n");
            mx_del_strarr(&info);
            Exit_Status = 1;
        }
    } else {
        bool this_is_typable = true;
        char *string = NULL;
        string = mx_strnew(PATH_MAX);
        if(info[1] != NULL) {
            FILE *file;
            char *pwd_from_env = mx_strdup(getenv("PWD"));
            char *pwd_from_env_new = strcat(pwd_from_env, SLESH);
            pwd_from_env_new = strcat(pwd_from_env_new, info[1]);
            file = fopen(pwd_from_env_new, "w");
            fprintf(file, "%s", buf);
            fclose(file);
            mx_strdel(&pwd_from_env);
            this_is_typable = false;
        } else {
            strcat(string, buf);
        }
        int amount = 0;
        bool is_not_odd = false;
        for (int idx_for_string = 0; string[idx_for_string]; idx_for_string++) {
            if (string[idx_for_string] == '"' || string[idx_for_string] == '\'') {
                for (int j = idx_for_string; string[j]; j++) {
                    string[j] = string[j + 1];
                }
                amount++;
                is_not_odd = true;
            } else if (string[idx_for_string] == '\\') {
                if (!is_not_odd) {
                    for (int temp_idx_for_string = idx_for_string; string[temp_idx_for_string]; temp_idx_for_string++) {
                        string[temp_idx_for_string] = string[temp_idx_for_string + 1];
                    }
                }
            }
        }
        if(amount % 2 == 0 || amount == 0 || amount == 2) {
            if (this_is_typable) {
                mx_printstr(string);
                mx_printstr("\n");
            }
        } else {
            fprintf(stderr, "Odd number of quotes.\n");
            mx_del_strarr(&info);
            Exit_Status = 1;
        }
        mx_strdel(&string);
    }
    mx_del_strarr(&info);
    Exit_Status = 0;

}

