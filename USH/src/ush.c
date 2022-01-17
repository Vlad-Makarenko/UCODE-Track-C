#include "ush.h"



void prompt(void){
    int flag = isatty(fileno(stdin));
    if (flag){
        printf("u$h> ");
    } else {
        return;
    }
}


void ush(){

    for(;;) {

        signal(SIGINT, CTRL_C);
        signal(SIGTSTP, CTRL_Z);

        prompt();
    
        char *command = read_line_from_terminal();
        if(command){
            
            command = mx_strtrim(command);

            
            if(mx_get_char_index(command, '~') >= 0){
                tilda_correction(&command);
            }


            char **command_lines = mx_strsplit(command, ';');
            

            
            for(int i = 0; command_lines[i]; i++){
                
                int flag = 0;
                command_substitution(&command_lines[i], &flag);
                if(flag == -1){ 
                    continue;
                }

                char **argv = command_parser(command_lines[i]);


                if(is_builtin(argv[0])){
                    run_builtin(argv, command_lines[i]);
                }else{
                    char *cmd = mx_strdup(argv[0]);
                    hold_esc_symbs(&argv);
                    produce_job(argv, command_lines[i], cmd);
                }

            }

            

            mx_strdel(&command);
            mx_del_strarr(&command_lines);
        }

        if (!isatty(fileno(stdin))){
            exit(0);
        }

    }
    

}
