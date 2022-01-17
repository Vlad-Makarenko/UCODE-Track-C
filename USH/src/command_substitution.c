#include "ush.h"

char *escape_cm_foo(char *str){
    char *escape_cm = mx_strnew(PATH_MAX);
    int escape_cm_idx = 0;
    for (; *str != '`' && *str != '\0'; escape_cm_idx++) {
        escape_cm[escape_cm_idx] = *str;//readress
        str++;
    }
    escape_cm[escape_cm_idx] = '\0';
    *str = '\0';
    return escape_cm;
}

void swap_char(char *str) {
    char *tmp = str;
    for (; *(tmp + 1) != '\0'; tmp++) {
        mx_swap_char(tmp, (tmp + 1));
    }
}

char char_to_upper(char character) {
    if(mx_isalpha(character)) {
        if(character < 97) {
            character += 32;
        }
    }
    return character;
}

char *get_executable_cmd(char *line) {
    char **splited_arr = mx_strsplit(line, ' '); 

    char *result = mx_strnew(PATH_MAX);
    char **splited_path = mx_strsplit(getenv("PATH"), ':');

    struct stat s_stat;
    for (int i = 0; splited_path[i] != NULL; i++) {
        char *cmd = NULL;
        if (splited_arr[0][0] != '/') {
            cmd = mx_strdup(splited_path[i]);
            cmd = save_strjoin(cmd, SLESH);
            cmd = save_strjoin(cmd, splited_arr[0]);
        }
        else 
            cmd = mx_strdup(splited_arr[0]);
        if (lstat(cmd, &s_stat) != -1) {
            result = save_strjoin(result, cmd);
            mx_strdel(&cmd);
            result = save_strjoin(result, line + mx_strlen(splited_arr[0]));
            mx_del_strarr(&splited_path);
            return result;
        }

        if (cmd != NULL) {
            mx_strdel(&cmd);
        }
    }
    
    return result;
}

 int ch_pp(char **string, char *escape_cm) {
     char *escape_cm_dup = mx_strdup(escape_cm);

     char **splited_arr = mx_strsplit(escape_cm, ';');


    for (int i = 0; splited_arr[i] != NULL; i++) {
        char *cmd = get_executable_cmd(escape_cm);
        FILE *fp;
        char *string_replace = mx_strnew(PATH_MAX);
        fp = popen(cmd, "r");
        if (fp == NULL) {
            mx_printerr("Failed to run command\n");
            return 1;
        }
        char *rep_str_ptr = string_replace;
        while (fgets(rep_str_ptr, PATH_MAX, fp) != NULL) {
            rep_str_ptr = string_replace + mx_strlen(string_replace);
            string_replace[mx_strlen(string_replace) - 1] = ' ';
        }
        string_replace[mx_strlen(string_replace) - 1] = '\0';
        pclose(fp);
        
        *string = str_replace(*string, escape_cm_dup, string_replace);
        mx_strdel(&string_replace);
        mx_strdel(&cmd);
    }
    mx_strdel(&escape_cm_dup);
    mx_del_strarr(&splited_arr);
    return 0;
 }

int back_quotes(char **string){
    char *info = *string;
    char *buff = mx_strchr(info, '`');
    if (buff) {
        int count = mx_count_substr(buff, "`");
        int flag = count % 2;
        if (flag != 0) {
            return 0;
        }
        for (;!buff;) {
            char *buff_ptr = buff;

            *buff = '\0';
            swap_char(buff);

            char *escape_cm = escape_cm_foo(buff_ptr); /// !!!!!!!!

            *buff_ptr = '\0';
            swap_char(buff_ptr);



            for (char *tmp = escape_cm; *tmp != '\0' && *tmp != ' '; tmp++) {
                *tmp = char_to_upper(*tmp);
            }

            ch_pp(string, escape_cm);
            

            info = *string;
            mx_strdel(&escape_cm);
            buff = mx_strchr(info, '`');
        }
    }
    return 0;
}


void bucks_loop(char **string) {
    char *info = *string;
    char *buff = strchr(info, '$');
    for (;buff != NULL;) {
        if (*(buff + 1) == '{' || *(buff + 1) == '(') {
            buff = strchr(++buff, '$');
            continue;
        }
        char *buff_ptr = buff;

        if (*(buff + 1) != '(' && *(buff + 1) != '{') {
            int buf_len = mx_strlen(buff) + 2;
            char *string_to_replace = mx_strnew(buf_len);
            char *string_variable = mx_strnew(buf_len);

            string_to_replace[0] = *buff_ptr;
            buff_ptr++;
            for (int idx = 1, jdx = 0; *buff_ptr != '\0' && *buff_ptr != ' ' && *buff_ptr != '$'; idx++, jdx++) {
                if (*buff_ptr != '?') {
                    if (!mx_isalpha(*buff_ptr))
                        break;
                }
                string_to_replace[idx + 1] = '\0';
                string_variable[jdx + 1] = '\0';

                string_to_replace[idx] = *buff_ptr;
                string_variable[jdx] = *buff_ptr;
                if (string_variable[0] == '?')
                    break;
                buff_ptr++;
            }

            if (string_variable[0] == '?') {
                char *status = mx_itoa(Exit_Status);
                *string = str_replace_one_more(*string, string_to_replace, status);
                mx_strdel(&status);
                mx_strdel(&string_to_replace);
                mx_strdel(&string_variable);
                buff = strchr(*string, '$');
                continue;
            }
            
            char *environment_value = getenv(string_variable);
            char *environment = NULL;
            if (environment_value == NULL){
                environment = mx_strdup("\0");
            }else{ 
                environment = mx_strdup(environment_value);
            }
            if (mx_isalpha(environment[0])){
                *string = str_replace_one_more(*string, string_to_replace, environment);
            }
            mx_strdel(&environment);
            mx_strdel(&string_to_replace);
            mx_strdel(&string_variable);
        }

        buff = strchr(++buff, '$');
    }
}

int simple_bucks_loop(char **string){
    char *info = *string;
    char *buff = strchr(info, '$');
    if(!buff){
        return 0;
    }
    for (;buff != NULL;) {
        if (*(buff + 1) == '(') {
            buff = strchr(++buff, '$');
            continue;
        }
    
        char *buff_ptr = buff;
        if (*(buff + 1) == '{') {
            int buf_len = mx_strlen(buff) + 2;
            char *string_to_replace = mx_strnew(buf_len);
            char *string_variable = mx_strnew(buf_len);

            string_to_replace[0] = *buff_ptr;
            string_to_replace[1] = *(buff_ptr + 1);
            buff_ptr += 2;
            for (int i = 2, j = 0; *buff_ptr != '}'; i++, j++) {
                string_to_replace[i + 1] = '\0';
                string_variable[j + 1] = '\0';

                string_to_replace[i] = *buff_ptr;
                if (*buff_ptr != '}')
                    string_variable[j] = *buff_ptr;
                if (*buff_ptr == ' ' || *buff_ptr == '\0') {
                    mx_printerr("ush: bad substitution\n");
                    mx_strdel(&string_to_replace);
                    mx_strdel(&string_variable);
                    Exit_Status = 1;
                    return -1;
                }
                buff_ptr++;
                if (*buff_ptr == '}')
                    string_to_replace[i + 1] = *buff_ptr;
            }

            char *environment_value = getenv(string_variable);
            char *environment = NULL;
            if (environment_value == NULL)
                environment = mx_strdup("\0");
            else 
                environment = mx_strdup(environment_value);

            *string = str_replace_one_more(*string, string_to_replace, environment);

            mx_strdel(&environment);
            mx_strdel(&string_to_replace);
            mx_strdel(&string_variable);
        }
        buff = strchr(*string, '$');
        if (buff == buff_ptr){
            buff = strchr(++buff, '$');
        }
    }
    return 0;
}

int other_simple_bucks_loop(char **string){
    char *info = *string;
    char *buff = strchr(info, '$');
    if(!buff){
        return 0;
    }
    for (;buff != NULL;) {
        if (*(buff + 1) != '(') {
            buff = strchr(++buff, '$');
            continue;
        }
        
        char *buff_ptr = buff;
        int buf_len = mx_strlen(buff) + 2;
        char *string_to_replace = mx_strnew(buf_len);
        char *string_variable = mx_strnew(buf_len);

        string_to_replace[0] = *buff_ptr;
        string_to_replace[1] = *(buff_ptr + 1);
        buff_ptr += 2;
        for (int i = 2, j = 0; *buff_ptr != ')'; i++, j++) {
            string_to_replace[i + 1] = '\0';
            string_variable[j + 1] = '\0';

            string_to_replace[i] = *buff_ptr;
            if (*buff_ptr != ')')
                string_variable[j] = *buff_ptr;
            buff_ptr++;
            if (*buff_ptr == ')')
                string_to_replace[i + 1] = *buff_ptr;
        }

       
        char *cmd = mx_strnew(mx_strlen(string_variable));
        for (int j = 0; string_variable[j] != ' ' && string_variable[j] != '\0' && string_variable[j] != ')'; j++) {
            char sym = string_variable[j];
            char sym_cpy = sym;
            if (mx_isalpha(sym) && sym < 97)
                sym += 32;
            cmd[j] = sym_cpy;
            string_variable[j] = sym;
        }
        char *command = get_executable_cmd(string_variable);
        if (mx_strlen(command) == 0) {
            mx_printerr("ush: command not found: ");
            remove_bslashes(cmd);
            show_bslashes(&cmd);
            mx_printerr(cmd);
            mx_printerr("\n");
        }
        FILE *fp;
        char *rep_str = mx_strnew(PATH_MAX);
        fp = popen(command, "r");
        if (fp == NULL) {
            mx_printerr("Failed to run command\n");
            return 1;
        }
        char *rep_str_ptr = rep_str;
        while (fgets(rep_str_ptr, PATH_MAX, fp) != NULL) {
            rep_str_ptr = rep_str + mx_strlen(rep_str);
            rep_str[mx_strlen(rep_str) - 1] = ' ';
        }
        rep_str[mx_strlen(rep_str) - 1] = '\0';
        pclose(fp);
        
        *string = str_replace_one_more(*string, string_to_replace, rep_str);
        mx_strdel(&rep_str);
        mx_strdel(&command);
        mx_strdel(&cmd);

        mx_strdel(&string_to_replace);
        mx_strdel(&string_variable);
        buff = strrchr(*string, '$');
    }
    return 0;
}

void command_substitution(char **string, int *return_value) {

    int to_return = back_quotes(string);

    if(to_return){
        *return_value = to_return;
        return;
    }
    
    // Loop for replacing simple $COMMAND
    bucks_loop(string);


    // Loop for other simple substitutions like ${COMMAND}
    to_return = simple_bucks_loop(string);

    if(to_return){
        *return_value = to_return;
        return;
    }

    
    // Loop for other simple substitutions like $(COMMANDS)

    to_return = other_simple_bucks_loop(string);

    if(to_return){
        *return_value = to_return;
        return;
    }

}


