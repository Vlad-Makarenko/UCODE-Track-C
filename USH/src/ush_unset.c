#include "ush.h"

int checker_for_any_parametrs_of_unset(char **command_lines) {
    for(int i = 1; command_lines[i] != NULL; i++) {
        for(int j = 0; j < mx_strlen(command_lines[i]); j++) {
            if (command_lines[i][j] == '=' || command_lines[i][j] == '-'
                || command_lines[i][j] == '.' || command_lines[i][j] == ','
                || command_lines[i][j] == '^' || command_lines[i][j] == '%'
                || command_lines[i][j] == '#' || command_lines[i][j] == '@'
                || command_lines[i][j] == ')' || command_lines[i][j] == '*'
                || command_lines[i][j] == '!' || command_lines[i][j] == '+'
                || mx_isspace(command_lines[i][j]) || command_lines[i][j] == '('
                || command_lines[i][j] == ']') {
                    fprintf(stderr, "ush: unset: '%s': invalid parameter name\n", command_lines[i]);
                return -1;  
                }
        }
    }
    return 0;
}

void unset_loop(char **command_lines) {
    for(int i = 1; command_lines[i] != NULL; i++) {
        if(unsetenv(command_lines[i]) < 0) {
            perror("ush: unset");
            Exit_Status = 1;
            continue;
        }
    }
}


void init_unset(char **command_lines) {
    if(checker_for_any_parametrs_of_unset(command_lines) == 0){
        unset_loop(command_lines);
    }
    Exit_Status = 0;
}

