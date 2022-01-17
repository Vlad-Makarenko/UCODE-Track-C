#include "ush.h"


int main(void ){
    Jobs_list = jl_new_node(getpid(), "ush");
    Exit_Status = 0;

    char *pwd = mx_strnew(PATH_MAX);
    setenv("PWD", getcwd(pwd, PATH_MAX), 1);
    

    int tmp_shlvl = mx_atoi(getenv("SHLVL"));
    setenv("SHLVL", mx_itoa(tmp_shlvl + 1), 1);
    char *tmp_shell = save_strjoin(pwd, "/");
    tmp_shell = save_strjoin(tmp_shell, "ush");
    setenv("SHELL", tmp_shell, 1);

    mx_strdel(&tmp_shell);


    ush();
}
