#include "ush.h"

bool is_screen_chars(char c, char *null) {
    char chars[] = {'a', 'b', 'f', 'n', 'r', 't', 'v', '"', '\'', '`', '\\'};
    int len = 11;

    for (int idx = 0; idx < len; idx++) {
        if (c == chars[idx]) {
            return true;
        }
    }
    if (null != NULL){
        return true;
    }else {
        return false;
    }
}

char **command_parser(char *command){

    int begin = 0;
    int len = mx_strlen(command);
    int finish = len;

    t_env_list *list = NULL;


    bool is_back_quotes = false;
    bool is_double_back_quotes = false;

    for(int idx = 0; idx < len + 1; idx++){
        char *param = mx_strnew(len);      ///!!!!!!!!!!
        if(!is_back_quotes && command[idx] == '"') {
            if(idx != 0){
                if(command[idx - 1] == '\\'){
                    continue;
                }
            }
            if (is_double_back_quotes == true){
                finish = idx;
                mx_strncpy(param, command + begin + 1, finish - begin - 1);
                push_back_env_list(&list, param, param);//!!!!!!!
                begin = finish + 1;
            }
            is_double_back_quotes = !is_double_back_quotes;
        }

        if(!is_double_back_quotes && command[idx] == '\''){
            if (idx != 0) {
                    if (command[idx - 1] == '\\') {
                        continue;
                    }
                }
                if (is_back_quotes) {
                    finish = idx;
                    mx_strncpy(param, command + begin + 1, finish - begin - 1);
                    push_back_env_list(&list, param, param);
                    begin = finish + 1;
                }
                is_back_quotes = !is_back_quotes;
        }

        if (command[idx] == ' ') {
            if (is_double_back_quotes || is_back_quotes || (idx != 0 && command[idx - 1] == '\\')) {}
            else {
                finish = idx;
                mx_strncpy(param, command + begin, finish - begin);
                push_back_env_list(&list, param, param);
                begin = finish + 1;
            }
        }

        if (command[idx] == '\0') {
            if (begin != len) {
                finish = idx;
                mx_strncpy(param, command + begin, finish - begin);
                push_back_env_list(&list, param, param);
                begin = finish + 1;
            }
        }
        mx_strdel(&param);
    }

    int size = size_env_list(list);

    char **arr_str = (char**)malloc(sizeof(char *) * size);
    t_env_list *temp = list;
    for (int i = 0; temp; i++) {
        arr_str[i] = mx_strdup(temp->name);
        temp = temp->next;
    }

    del_env_list(&list);



    /////////fdgfhdfhdfhdfhdfhdfhdfhdfh

    char** to_return_str_arr = (char**)malloc(sizeof(char*) * (size + 1));
    int idx = 0;
    for (int array_index = 0; array_index < size; array_index++) {

        char* clear_str = mx_strtrim(arr_str[array_index]);

        if (clear_str == NULL || clear_str[0] == '\0') {
            idx++;
        } else
             to_return_str_arr[array_index - idx] = mx_strdup(clear_str);
        if (arr_str[array_index] != NULL) {
            free(arr_str[array_index]);
        }
        free(clear_str);
    }

    to_return_str_arr[size - idx] = NULL;

    free(arr_str);


    for (int idx = 0; to_return_str_arr[idx] != NULL; idx++) {
        char *temp = strchr(to_return_str_arr[idx], '\\');
        for (; temp;){
            if(!is_screen_chars(*(temp + 1), NULL) && *(temp + 1) != '\0' ){
                *temp = '\0';
                char *temp_for_temp = temp;
                for(; *(temp_for_temp + 1) != '\0';){
                    mx_swap_char(temp_for_temp, temp_for_temp + 1);
                    temp_for_temp++;
                }
            } else {
                temp++;
            }
            temp = strchr (temp, '\\');
        }
    }



    return to_return_str_arr;

}
