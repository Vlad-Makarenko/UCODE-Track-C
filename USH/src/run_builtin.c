#include "ush.h"

//      "exit env export unset pwd fg cd which echo"

void run_builtin(char **argv, char *all_command){

    char **builtin_arr = create_in_built_array();
    if(!strcmp(builtin_arr[0], argv[0])){ 
        int exit_status = EXIT_SUCCESS;
        if(argv[1]){
            exit_status = mx_atoi(argv[1]);
        }
        mx_del_strarr(&builtin_arr);
        exit(exit_status);
    } else if (!strcmp (builtin_arr[1], argv[0])){
        init_env(argv);
    } else if (!strcmp (builtin_arr[2], argv[0])){
        init_export(argv);
    } else if (!strcmp (builtin_arr[3], argv[0])){
        init_unset(argv);
    } else if (!strcmp (builtin_arr[4], argv[0])){
        init_pwd(argv);
    } else if (!strcmp (builtin_arr[5], argv[0])){
       init_fg(argv);
    } else if (!strcmp (builtin_arr[6], argv[0])){
        init_cd(argv);
    } else if (!strcmp (builtin_arr[7], argv[0])){
        init_which(argv);
    } else if (!strcmp (builtin_arr[8], argv[0])){
        init_echo(argv, &all_command);
    }

    mx_del_strarr(&builtin_arr);
}
