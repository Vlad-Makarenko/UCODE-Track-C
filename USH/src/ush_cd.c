#include "ush.h"


t_cd * create_cd(bool s, bool P, bool minus){
    t_cd *new_node = malloc(sizeof(struct s_cd_flags));

    new_node->s = s;
    new_node->P = P;
    new_node->minus = minus;

    return new_node;
}

t_cd* parse_to_cd_flags(char **argv){
    t_cd *cd = create_cd(false, false, false);

    if (argv[1] && argv[1][0] == '-') {
        cd->minus = true;
        char *error_line = mx_strdup(": invalid option\ncd: usage: cd [-sP]\n");
        for (int n = 1; argv[1][n]; n++){
            switch (argv[1][n]) {
                case 's':
                    cd->s = true;
                    break;
                case 'P':
                    cd->P = true;
                    break;
                default:
                    fprintf(stderr, "ush: cd: -%c%s",  argv[1][n],error_line);
                    mx_strdel(&error_line);
                    Exit_Status = 1;
                    return NULL;
                    break;
            }
        }
        mx_strdel(&error_line);
        return cd;
    }else {
        Exit_Status = 0;
        return cd;
    }
}

void vary_current_pwd(char *environ_pwd, char *environ_oldpwd, char *environ_home ){
    if (environ_home[0] != '\0') {
        chdir(environ_home);
        if (strcmp(environ_oldpwd, environ_pwd)) {
            setenv("OLDPWD", environ_pwd, 1);
        }
        setenv("PWD", environ_home, 1);
    }
}

int do_s_flag(char *environ_pwd, char *environ_oldpwd, char *path){
    char pwd_tmp[PATH_MAX];

    strncpy(pwd_tmp, environ_pwd, PATH_MAX);

    if(path[0] == '/') {
        memset(environ_pwd, 0, PATH_MAX);
        environ_pwd[0] = '/';
    }


    char **splited_path = mx_strsplit(path, '/');
    for(int idx = 0; splited_path[idx] != NULL; idx++) {
        char *temp = mx_strnew(PATH_MAX);
        if(strcmp(splited_path[idx], "..") == 0) {
            char *shlash_ptr = strrchr(environ_pwd, '/');
            if (shlash_ptr){
                memset(shlash_ptr, '\0', mx_strlen(shlash_ptr));
            } else{
                environ_pwd[0] = '/';
            }
            if (environ_pwd[0] == '\0'){
                environ_pwd[0] = '/';
            }
        } else if (mx_strcmp(splited_path[idx], ".") == 0) {
            int len = strlen(environ_pwd);
            if (environ_pwd[len - 1] != '/'){
                environ_pwd[strlen(environ_pwd)] = '/';
            }
            strncpy(environ_pwd + strlen(environ_pwd), splited_path[idx], strlen(splited_path[idx]));

            // add_dir(splited_path[idx]);
        }
        readlink(environ_pwd, temp, PATH_MAX);
        struct stat s_stat;
        lstat(path, &s_stat);
        // free(link);
        if ((s_stat.st_mode & S_IFMT) == S_IFLNK && strcmp(splited_path[idx], "..") && strcmp(splited_path[idx], ".")) {
            mx_del_strarr(&splited_path);
            // strncpy(environ_pwd, pwd_tmp, PATH_MAX);
            return 1;
        }
        mx_strdel(&temp);
    }

    mx_del_strarr(&splited_path);

    int flag = chdir(path);

    if (flag < 0) {
        char *err_tmp = mx_strdup(strerror(errno));
        if (err_tmp[0] < 97){
            err_tmp[0] += 32;
        }
        fprintf(stderr, "cd: %s: %s\n", err_tmp, path);
        strncpy(environ_pwd, pwd_tmp, PATH_MAX);
        mx_strdel(&err_tmp);

    } else {
        if (strcmp(environ_oldpwd, pwd_tmp)) {
            setenv("OLDPWD", pwd_tmp, 1);
            // strncpy(environ_oldpwd, pwd_tmp, PATH_MAX);
            // setenv("OLDPWD", environ_oldpwd, 1);
        }
        setenv("PWD", environ_pwd, 1);
    }

    return 0;
}

void init_cd(char **command_lines){
    hold_esc_symbs(&command_lines);

    int size_cmd_ln = 0;
    char *temp = mx_strnew(PATH_MAX);
    char *all_path = NULL;
    char *current_pwd = mx_strnew(PATH_MAX);

    char *environ_pwd = mx_strnew(PATH_MAX);
    char *environ_oldpwd = mx_strnew(PATH_MAX);
    char *environ_home = mx_strnew(PATH_MAX);
    strcpy(environ_pwd, getenv("PWD"));
    strcpy(environ_oldpwd, getenv("OLDPWD"));
    strcpy(environ_home, getenv("HOME"));
    size_cmd_ln = get_strarr_size(command_lines);
    strncpy(current_pwd, environ_pwd, PATH_MAX);

    if (size_cmd_ln > 1) {
        all_path = (command_lines[1][0] == '-' && mx_strlen(command_lines[1]) > 1) ? mx_strdup(command_lines[2]) : mx_strdup(command_lines[1]);
    }

    if(size_cmd_ln == 1) {

        vary_current_pwd(environ_pwd, environ_oldpwd, environ_home);

        mx_strdel(&all_path);
        Exit_Status = 0;
        return;
    } else if (size_cmd_ln == 2) {
        if (command_lines[1][0] == '-' && mx_strlen(command_lines[1]) > 1) {
            vary_current_pwd(environ_pwd, environ_oldpwd, environ_home);

            mx_strdel(&all_path);
            mx_strdel(&temp);
            mx_strdel(&current_pwd);
            Exit_Status = 0;
            return ;
        } else  if (command_lines[1][0] == '-') {

            if (environ_oldpwd[0] != '\0') {
                chdir(environ_oldpwd);
                setenv("OLDPWD", environ_pwd, 1);
                setenv("PWD", environ_oldpwd, 1);
            }
            mx_strdel(&all_path);
            mx_strdel(&temp);
            mx_strdel(&current_pwd);
            Exit_Status = 0;
            return ;
        }

    }
    else if(size_cmd_ln == 3){
        if (command_lines[1][0] == '-')
            NULL;
        else {
            char *tmp = str_replace(environ_pwd, command_lines[1], command_lines[2]);
            if (tmp != NULL) {
                mx_strdel(&all_path);
                all_path = tmp;
            }
            else {
                fprintf(stderr, "cd: string not in pwd: %s\n", command_lines[1]);
                Exit_Status = 1;
                mx_strdel(&temp);
                mx_strdel(&current_pwd);
                return ;
            }
        }

    }else if (size_cmd_ln == 4){
        if (command_lines[1][0] != '-') {
            fprintf(stderr, "ush: cd: too many arguments\n");
            mx_strdel(&all_path);
            mx_strdel(&temp);
            mx_strdel(&current_pwd);
            Exit_Status = 1;
            return ;
        } else {
            char *tmp = str_replace(environ_pwd, command_lines[2], command_lines[3]);
            if (tmp != NULL) {
                mx_strdel(&all_path);
                all_path = tmp;
            } else {
                fprintf(stderr, "cd: string not in pwd: %s\n", command_lines[1]);
                Exit_Status = 1;
                mx_strdel(&temp);
                mx_strdel(&current_pwd);
                return ;
            }
        }
    }


    t_cd *cd_flags = parse_to_cd_flags(command_lines);
    
    char *path_with_tilda = str_replace_one_more(all_path, "~", environ_home);
    if (path_with_tilda == NULL){
        path_with_tilda = mx_strdup(all_path);
    }
    if (cd_flags->s) {
        int tmp_flag = do_s_flag(environ_pwd, environ_oldpwd, path_with_tilda);
        if (tmp_flag) {
            fprintf(stderr, "cd: not a directory: %s\n", path_with_tilda);
            if (all_path != NULL){
                mx_strdel(&all_path);
            }
            mx_strdel(&temp);
            mx_strdel(&current_pwd);
            mx_strdel(&path_with_tilda);
            Exit_Status = 1;
            return ;
        }
        if (all_path != NULL){
            mx_strdel(&all_path);
        }
        mx_strdel(&temp);
        mx_strdel(&current_pwd);
        mx_strdel(&path_with_tilda);
        Exit_Status = 0;
        return ;
    }

    if (all_path != NULL && cd_flags->P) {
        char *result = NULL;
        result = realpath(path_with_tilda, temp);
        mx_strdel(&path_with_tilda);
        path_with_tilda = mx_strdup(temp);
        if (!result){
            mx_strdel(&result);
        }
    }

    int flag = 0;
    if (path_with_tilda[0] == '/') {
        memset(environ_pwd, '\0', mx_strlen(environ_pwd));
        environ_pwd[0] = '/';
    }

    char **splited_path_with_tilda = mx_strsplit(path_with_tilda, '/');
    for (int i = 0; splited_path_with_tilda[i] != NULL; i++) {
        if (!strcmp(splited_path_with_tilda[i], "..")){
            char *shlash_ptr = strrchr(environ_pwd, '/');
            if (shlash_ptr){
                memset(shlash_ptr, '\0', mx_strlen(shlash_ptr));
            } else{
                environ_pwd[0] = '/';
            }
            if (environ_pwd[0] == '\0'){
                environ_pwd[0] = '/';
            }

        }else if (strcmp(splited_path_with_tilda[i], ".")){
            int len = strlen(environ_pwd);
            if (environ_pwd[len - 1] != '/'){
                environ_pwd[len] = '/';
            }

            strncpy(environ_pwd + strlen(environ_pwd), splited_path_with_tilda[i], strlen(splited_path_with_tilda[i]));


        }
    }
    mx_del_strarr(&splited_path_with_tilda);

    
    flag = chdir(environ_pwd);
    if (flag < 0) {
        char *err_tmp = mx_strdup(strerror(errno));
        if (err_tmp[0] < 97){
            err_tmp[0] += 32;
        }
        fprintf(stderr, "cd: %s: %s\n", err_tmp, all_path);
        mx_strdel(&err_tmp);
        Exit_Status = 1;
        return;
    } else {
        if (strcmp(environ_oldpwd, current_pwd)) {
            setenv("OLDPWD", current_pwd, 1);
        }
        setenv("PWD", environ_pwd, 1);
    }
    if (all_path != NULL)
        mx_strdel(&all_path);
    mx_strdel(&path_with_tilda);
    Exit_Status = 0;
}
