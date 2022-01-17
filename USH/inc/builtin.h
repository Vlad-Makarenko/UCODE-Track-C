#ifndef BUILTIN_H
#define BUILTIN_H

/////////////////// BUILTIN \\\\\\\\\\\\\\\\\\\\|


void run_builtin(char **argv, char *all_command);

///////////////////// PWD \\\\\\\\\\\\\\\\\\\\\\|

typedef struct  s_pwd_flags{
    bool L;
    bool P;
}               t_pwd;

t_pwd * create_pwd(bool L, bool P);

t_pwd* parse_to_pwd_flags(char **argv);

void init_pwd(char **command_lines);


////////////////////// CD \\\\\\\\\\\\\\\\\\\\\\|

typedef struct  s_cd_flags{
    bool s;
    bool P;
    bool minus;
}               t_cd;

t_cd * create_cd(bool s, bool P, bool minus);

t_cd* parse_to_cd_flags(char **argv);

void init_cd(char **command_lines);

///////////////////// WHiCH \\\\\\\\\\\\\\\\\\\\|

typedef struct  s_which_flags{
    bool a;
    bool s;
}               t_which;

t_which * create_which(bool s, bool a);

t_which* parse_to_which_flags(char **argv);

void init_which(char **command_lines);

char **create_in_built_array_for_which();



///////////////////// ECHO \\\\\\\\\\\\\\\\\\\\\|

typedef struct  s_echo_flags{
    bool n;
    bool e;
    bool E;
    bool is_default;
}               t_echo;

t_echo * create_echo(bool n, bool e, bool E);

t_echo* parse_to_echo_flags(char **argv);

void init_echo(char **argv, char **command_lines);


///////////////////// ENV \\\\\\\\\\\\\\\\\\\\\\|

typedef struct  s_env_list{
    char *name;
    char *value;
    struct s_env_list *next;
}               t_env_list;

typedef struct  s_env_flags {
    bool i;
    bool P;
    bool u;
}               t_env;

t_env * create_env(bool i, bool P, bool u);

t_env_list *create_env_list(char *name, char *value);

void push_back_env_list( t_env_list **head, char *name, char *value);

void del_env_list(t_env_list **head);

void init_env(char **command_lines);

void parse_to_env_list(t_env_list **head);

int size_env_list(t_env_list* head);

t_env* parse_to_env_flags(char **argv);


/////////////////////////// EXPORT \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\|


void init_export(char **command_lines);


///////////////////////////// FG \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\|


void init_fg(char **command_lines);



/////////////////////////// UNSET \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\|


void init_unset(char **command_lines);

int checker_for_any_parametrs_of_unset(char **command_lines);

void unset_loop(char **command_lines);








#endif 
