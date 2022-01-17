#ifndef UTILS_H
#define UTILS_H



//////////////////////////// UTILS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\|



int get_strarr_size(char **strarr);

void mx_printerr(const char *s);

void mx_printcharerr(const char s);

char *save_strjoin(char const *s1, char const *s2);

int mx_atoi(const char *str);

char **create_in_built_array();

bool is_builtin(char * command);

void print_error (char * command_lines);

char *str_replace(char *str, char *substr, char *rep);

char *str_replace_one_more(char *str, char *substr, char *rep);

void remove_bslashes(char *str);

void show_bslashes(char **str);

int count_substr(const char* str, char* sub);

void hold_esc_symbs(char ***str_arr);


#endif 
