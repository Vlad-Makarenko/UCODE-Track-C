#include "ush.h"

t_which * create_which(bool s, bool a){

    t_which *new_node = malloc(sizeof(struct s_which_flags));

    new_node->s = s;
    new_node->a = a;

    return new_node;
}

t_which* parse_to_which_flags(char **argv){
    t_which *which = create_which(false, false);

    if (argv[1] && argv[1][0] == '-') {
        char *error_line = mx_strdup("which: bad option -- ");
        for (int n = 1; argv[1][n]; n++){
            switch (argv[1][n]) {
                case 'a':
                    which->a = true;
                    break;
                case 's':
                    which->s = true;
                    break;
                default:
                    fprintf(stderr, "%s%c\n", error_line, argv[1][n]);
                    mx_strdel(&error_line);
                    Exit_Status = 1;
                    return which;
                    break;
            }
        }
        mx_strdel(&error_line);
        return which;
    }else {
        Exit_Status = 0;
        return which;
    }
}

void init_which(char **command_lines){
    hold_esc_symbs(&command_lines);

    char **builtin_arr = create_in_built_array_for_which();
    char *error_line1 = mx_strdup(": shell built-in command\n");
    char *error_line2 = mx_strdup("export: ush reserved word\n");

    struct stat s_stat;
    bool is_now = false;
    struct dirent *directory;
    bool is_there = true;
    DIR *dir;

    t_which *which_flags = parse_to_which_flags(command_lines);


    if (which_flags->a) {
        int cmd_idx = 2;
        if (command_lines[cmd_idx] == NULL) {
            Exit_Status = 1;
            return ;
        }
        char *path_name = NULL;
        char **splited_path = mx_strsplit(getenv("PATH"), ':');

        for (; command_lines[cmd_idx] != NULL; ) {
            for (int idx = 0; idx < 8; idx++) {
                if (!strcmp(builtin_arr[idx], command_lines[cmd_idx])) {
                    fprintf(stderr, "%s%s", command_lines[cmd_idx], error_line1);
                    is_now = true;
                    break;
                }
            }
            if (!strcmp(command_lines[cmd_idx], "export")) {
                fprintf(stderr, "%s", error_line2);
                is_now = true;
            }

            if (command_lines[cmd_idx][0] == '/') {
                lstat(command_lines[cmd_idx], &s_stat);
                if (s_stat.st_mode & S_IXUSR) {
                    printf("%s\n", command_lines[cmd_idx]);
                    is_now = true;
                } else {
                    fprintf(stderr, "%s not found\n", command_lines[cmd_idx]);

                    cmd_idx++;
                    is_now = true;
                    is_there = false;
                    continue;
                }
            }

            for (int idx = 0; splited_path[idx] != NULL; idx++) {
                dir = opendir(splited_path[idx]);
                if (dir != NULL) {
                    while ((directory = readdir(dir)) != NULL) {
                        if (!strcmp(directory->d_name, command_lines[cmd_idx])) {
                            path_name = mx_strnew(256);
                            strcpy(path_name, splited_path[idx]);
                            path_name = strcat(path_name, "/");
                            path_name = strcat(path_name, command_lines[cmd_idx]);
                            printf("%s\n", path_name);
                            mx_strdel(&path_name);
                            is_now = true;
                            break;
                        }       
                    }
                    closedir(dir);
                }
            }
            if (is_now == false) {
                is_there = false;
                fprintf(stderr, "%s not found\n", command_lines[cmd_idx]);

            }
            cmd_idx++;
        }

        mx_del_strarr(&splited_path);
        if (!is_there) {
            Exit_Status = 1;
            return ;
        }
        Exit_Status = 0;
        return ;
    } else if (command_lines[1] != NULL) {
        int cmd_idx = 1;
        if (which_flags->s) {
            cmd_idx = 2;
        }
        if (command_lines[cmd_idx] == NULL) {
            Exit_Status = 1;
            return ;
        }
        char *path_name = NULL;
        char **splited_path = mx_strsplit(getenv("PATH"), ':');

        for (; command_lines[cmd_idx] != NULL;) {
            int flag = 0;
            for (int idx = 0; idx < 8; idx++) {
                if (!strcmp(builtin_arr[idx], command_lines[cmd_idx])) {
                    fprintf(stderr, "%s: shell built-in command\n", command_lines[cmd_idx]);
                    is_now = true;
                    flag = 1;
                    cmd_idx++;
                    break;
                }
            }
            
            if (flag) {
                flag = 0;
                is_now = false;
                continue;
            }
            if (!strcmp(command_lines[cmd_idx], "export")) {
                if(!which_flags->s) {
                    fprintf(stderr, "%s", error_line2);
                }
                is_now = true;
                cmd_idx++;
                continue;
            }

            if (command_lines[cmd_idx][0] == '/') {
                lstat(command_lines[cmd_idx], &s_stat);
                if (s_stat.st_mode & S_IXUSR) {
                    if(!which_flags->s) {
                        printf("%s\n",command_lines[cmd_idx] );
                    }
                    cmd_idx++;
                    is_now = true;
                    continue;
                } else {
                    fprintf(stderr, "%s not found\n", command_lines[cmd_idx]);
                    cmd_idx++;
                    is_now = true;
                    is_there = false;
                    continue;
                }
            }
            for (int idx = 0; splited_path[idx] != NULL; idx++) {
                dir = opendir(splited_path[idx]);
                if (dir != NULL) {
                    for (;(directory = readdir(dir)) != NULL;) {
                        if (!strcmp(directory->d_name, command_lines[cmd_idx])) {
                            path_name = mx_strnew(256);
                            strcpy(path_name, splited_path[idx]);
                            path_name = strcat(path_name, SLESH);
                            path_name = strcat(path_name, command_lines[cmd_idx]);
                            if(!which_flags->s){
                                printf("%s\n", path_name);
                            }
                            mx_strdel(&path_name);
                            is_now = true;
                            break;
                        }       
                    }
                    closedir(dir);
                }
            }
            
            if (is_now == false) {
                is_there = false;
                fprintf (stderr, "%s not found\n", command_lines[cmd_idx] );
            }
            is_now = false;
            cmd_idx++;
        }
        mx_del_strarr(&splited_path);
        if (is_there) {
            Exit_Status = 0;
            return ;
        }
        Exit_Status = 1;
        return ;
    } else {
        mx_strdel(&error_line1);
        mx_strdel(&error_line2);
        mx_del_strarr(&builtin_arr);
        Exit_Status = 1;
        return ;

    }

}


