#include "ush.h"

int get_strarr_size(char **strarr){
    int size = 0;
    for(; strarr[size]; size++);
    return size;
}

void mx_printerr(const char *s){
    write(2, s, mx_strlen(s));
}

void mx_printcharerr(const char s){
    write(2, &s, 1);
}


char *save_strjoin(char const *s1, char const *s2) {
    if (!s1 && !s2)
        return NULL;
    if (!s1 && s2)
        return mx_strdup(s2);
    if (s1 && !s2)
        return mx_strdup(s1);
    char *new_str = mx_strnew(mx_strlen(s1) + mx_strlen(s2));
    new_str = mx_strcat(mx_strcpy(new_str, s1), s2);
    char *to_delete = (char*)s1;
    mx_strdel(&to_delete);
    return new_str;
}

int mx_atoi(const char *str){
    while (mx_isspace((char )*str)){
        str++;
    }
    int flag = 1;
    if (*str == '-'){
        flag = -1;
        str++;
    }
    int res = 0;
    for ( ; (mx_isdigit((char ) *str)); ) {
        res = (res * 10) + ((*str) - '0');
        str++;
    }

    return res * flag;
}

char **create_in_built_array_for_which(){

    char *in_built = mx_strdup("cd pwd env which echo exit unset fg");
    char **arr_in_bilt = mx_strsplit(in_built, ' ');
    mx_strdel(&in_built);
    return arr_in_bilt;
}

char **create_in_built_array(){
    char *in_built = mx_strdup("exit env export unset pwd fg cd which echo");
    char **arr_in_bilt = mx_strsplit(in_built, ' ');
    mx_strdel(&in_built);
    return arr_in_bilt;
}

bool is_builtin(char * command){
    char ** arr = create_in_built_array();
    for(int i = 0; arr[i]; i++){
        if(strcmp(arr[i], command) == 0){
            mx_del_strarr(&arr);
            return true;
        }
    }
    mx_del_strarr(&arr);
    return false;
}

void print_error (char * command_lines){
    mx_printerr("ush: command not found: ");
    mx_printerr(command_lines);
    mx_printcharerr('\n');
}

char *str_replace(char *str, char *substr, char *rep) {
    char *out = mx_strnew(PATH_MAX);
    int i = 0, j = 0, flag = 0, begin = 0;
 
    for (; str[i] != '\0'; i++) {
        if (str[i] == substr[j]) {
            if (!flag){
                begin = i;
            }
            j++;
            if (substr[j] == '\0'){
                break;
            }
            flag = 1;
        } 
        else {
            flag = begin = j = 0;
        }
    }

    if (substr[j] == '\0' && flag) {
        for (i = 0; i < begin; i++)
            out[i] = str[i];
        for (j = 0; j < mx_strlen(rep); j++)  {
            out[i] = rep[j];
            i++;
        }
        for (j = begin + mx_strlen(substr); j < mx_strlen(str); j++) {
            out[i] = str[j];
            i++;
        }
        out[i] = '\0';
        return out;
    } else {
        mx_strdel(&out);
        return NULL;
    }
}


char *str_replace_one_more(char *str, char *substr, char *rep) {
    int idx = mx_get_substr_index(str, substr);
    if (idx == -1){
        return NULL;
    }
    int len_rep = mx_strlen(rep);
    int length = mx_strlen(str) + mx_strlen(rep);
    char *result = mx_strnew(length);
    mx_memcpy(result, str, idx);
    if (len_rep > 0)
        mx_memcpy(result + idx, rep, len_rep);
    mx_memcpy(result + idx + len_rep, 
        str + idx + mx_strlen(substr), length - idx - mx_strlen(substr) - len_rep);
    free(str);

    return result;
}

char *strstr_temp(const char *str1, const char *str2) {

    if (*str2 == '\0') return (char *)str1;
    while (1)
    {
        str1 = mx_strchr(str1, str2[0]);
        if (str1 == NULL) break;
        if (mx_strncmp(str1, str2, mx_strlen(str2)) == 0) {
            return (char *)str1;
        }
        if (*str1 == '\0') break;
        str1++;
    }

    return NULL;
}


int count_substr(const char* str, char* sub) {

    if (str == NULL || sub == NULL) return -1;
    int result = 0;

    for(;;) {
        str = strstr_temp(str, sub);
        if (str) {
            result++;
            if (*str != '\0') {
                str++;
            }
            if (*str == '\0') {
                break;
            }
        } else
            break;
    }

    return result;
}

void remove_bslashes(char *str) {
    int idx = 0;
    int count = count_substr(str, "\\");
    while (count % 2 != 0 && (idx = mx_get_char_index(str, '\\')) != -1) {
        if(idx != -1) {
            mx_memmove(&str[idx], &str[idx + 1], mx_strlen(str) - idx);
        }
        count--;
    }
}

void show_bslashes(char **str) {
    int idx = 0;
    int move = 0;
    for (;(idx = mx_get_char_index(*str + move, '\\')) != -1;) {   
        if (move + idx < mx_strlen(*str) - 1) {
            if ((*str)[move + idx + 1] == '\\') {
                *str = str_replace_one_more(*str, "\\", "");
            }
        }
        move += idx + 1;
    }
}


void swap_slash_space(char ***str_arr) {
    char **info = *str_arr;
    int idx = 0;
    while ( info[idx] != NULL ) {
        int length = mx_strlen(info[idx]);
        if (info[idx][length - 1] == '\\') {
            info[idx][length - 1] = ' ';
            info[idx] = mx_strjoin(info[idx], info[idx + 1]);
            if (info[idx + 1] != NULL) {
                free(info[idx + 1]);
            }
            info[idx + 1] = NULL;
            for (int j = idx + 1; info[j] != NULL && info[j + 1] != NULL; j++) {
                char *tmp = info[j];
                info[j] = info[j + 1];
                info[j + 1] = tmp;
            }
            idx--;
        }
        idx++;
    }
}


void hold_loop(char **str){
    char *temp = mx_strchr(*str, '\\');
    int is_rewritten = 0;

    for (; temp != NULL ;) {
        if (*(temp + 1) == 'n') {
            *temp = '\n';
            is_rewritten = 1;
        } else if (*(temp + 1) == 't') {
            *temp = '\t';
            is_rewritten = 1;
        } else if (*(temp + 1) == '\\') {
            *temp = '\\';
            is_rewritten = 1;
        } else if (*(temp + 1) == '\'') {
            *temp = '\'';
            is_rewritten = 1;
        } else if (*(temp + 1) == '\"') {
            *temp = '\"';
            is_rewritten = 1;
        } else if (*(temp + 1) == '`') {
            *temp = '`';
            is_rewritten = 1;
        } else if (*(temp + 1) == 'a') {
            *temp = '\a';
            is_rewritten = 1;
        } else if (*(temp + 1) == '0') {
            *temp = '\0';
            is_rewritten = 1;
        }
        
        temp++;
        char *from_ptr = temp;
        if (is_rewritten) {
            *temp = '\0';
            for (;*(temp + 1) != '\0';) {
                mx_swap_char(temp, temp + 1);
                temp++;
            }
        }
        
        is_rewritten = 0;
        temp = mx_strchr(from_ptr, '\\');
    }
}

void hold_esc_symbs(char ***str_arr) {


    char **info = *str_arr;
    
    swap_slash_space(str_arr);

    for (int i = 0; info[i] != NULL; i++) {
        hold_loop(&(info)[i]); // tut pzdc mb
    }
}

