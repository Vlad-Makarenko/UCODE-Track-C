#include "ush.h"

void prepare_for_echo(char **argv);

void produce_job(char **argv, char *command_line, char *cmd) {

    if (strstr(cmd, "echo")){
        prepare_for_echo(argv + 1);
    }

    pid_t p_id = fork();
    if(p_id == 0 ) {
        make_process(argv, cmd);
    } else {
        add_job(command_line, p_id); 
    }
}

void make_process(char **argv, char *cmd) {
    if(getenv("PATH") == NULL) {

        remove_bslashes(cmd);
        show_bslashes(&cmd);
        
        print_error(cmd);
        exit(1);
    }

    char **splited_path = mx_strsplit(getenv("PATH"), ':');
    char *command = NULL;
    for (int o = 0; splited_path[o]; o++) {
        if(cmd[0] != '/') {
            command = mx_strjoin(splited_path[o], SLESH);
            command = save_strjoin(command, cmd);
        }else {
            command = mx_strdup (cmd);
        }
        int flag = 0;
        flag = execve(command, argv, environ);
        mx_strdel(&command);

        if(flag != - 1){
            mx_del_strarr(&splited_path);
            exit(EXIT_SUCCESS);
        }
    }


    remove_bslashes (cmd);
    show_bslashes(&cmd);


    print_error(cmd);
    mx_del_strarr(&splited_path);
    exit(1);
}

void add_job(char *command_line, pid_t p_id){
    push_back_job(&Jobs_list, p_id, command_line);
    int flag = 0;
    waitpid(p_id, &flag, WUNTRACED);
    Exit_Status = WEXITSTATUS(flag);
    if(!WIFSTOPPED(flag)){
        remove_some_job(&Jobs_list, p_id);
    } else {
        Exit_Status = ES_BIG_ERR;
    }
    if (WIFSIGNALED(flag)){
        Exit_Status = ES_CTRL_C;
    }
}

void prepare_for_echo(char **argv) {

    for (int idx = 0; argv[idx] != NULL; idx++) {
        int dq_num = count_substr(argv[idx], "\"");
        int show_dq_num = count_substr(argv[idx], "\\\"");
        if ((dq_num - show_dq_num) == 0) {
            continue;
        }
        int dq_idx = -1;
        for (;(dq_idx = mx_get_char_index(argv[idx], '"')) != -1;){
            char *temp = argv[idx];
            argv[idx] = str_replace_one_more(temp, "\"", "");
        }
    }
}

