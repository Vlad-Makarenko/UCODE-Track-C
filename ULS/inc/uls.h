
#ifndef ULS_H
#define ULS_H

#include "libmx.h"
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <errno.h>
#include <time.h>
#include <grp.h>
#include <pwd.h>
#include <sys/xattr.h>
#include <sys/acl.h>
#include <sys/ioctl.h>
#include <string.h>

#define SLESH "/"

#define DEFAULT_CLR     "\033[0m"
#define RED_CLR         "\033[0;31m"
#define GREEN_CLR       "\033[0;32m"
#define YELLOW_CLR      "\033[0;33m"
#define BLUE_CLR        "\033[0;34m"
#define MAGENTA_CLR     "\033[0;35m"
#define CYAN_CLR        "\033[0;36m"
#define BLOCK_CLR       "\033[34;46m"
#define CHAR_CLR        "\033[34;43m"



typedef struct  s_base {
    char *name;
    char *path;
    struct stat *s_stat;
    struct s_base *next;
    
}               t_base;


typedef struct  s_flags {
    bool l;
    bool R;
    bool a;
    bool A;
    bool G;
    bool g;
    bool h;
    bool dog;
    bool e;
    bool T;
    bool one;
    bool C;
    bool r;
    bool t;
    bool u;
    bool c;
    bool S; 
    bool o; 
    bool s; 
}               t_flags;



//base
t_base *create_base (char *name, struct stat *s_stat, char *path);

void push_back_base ( t_base **head, char *name, struct stat *s_stat, char *path);

void parse_to_base (t_base ** head, char* directry_name);

void tree_function(char *directory_name, t_base **head);



//flags
t_flags *create_flags();

t_flags *get_flags (char *argv[]);

void correct_output(char *argv[], int argc, t_flags *flags);

void print_colorful(t_base *head);

void print_one(t_base * head, t_flags *flags);




//uls
void default_ls (t_base *head, t_flags* flags);

void del_uls_node (t_base **head);

void del_hidden_one(t_base **head);

void del_dote_one(t_base **head);

void print_correct_name(t_base *head, t_flags* flags);

int max_len_of_name(t_base *head);

void print_tab(int max_len, char * name);

void print_cols(t_base *head, int count_rows, int count, int len, t_flags *flags);

void names_ouput(t_base *head, int len, int col, t_flags *flags);

void correct_output_true(int i, char *argv[], int argc, t_base *head, t_flags *flags, char *d_name);

char **check_argv(char **argv, int *argc, t_flags *flags, bool *checker_argv, bool *chacker_files, bool *is_error);


//sort
int directory_count(t_base * head);

void sort_files(t_base **head, bool (*cmp)(t_base *a, t_base *b));

void sort_argv(char **arr, int size);

void sort_argv_without_flags(char **arr, int size);

void sort_flag_r(t_base **head);

bool sort_flag_default(t_base *a, t_base *b);

bool sort_flag_t(t_base *a, t_base *b);

bool sort_flag_u(t_base *a, t_base *b);

bool sort_flag_c(t_base *a, t_base *b);

bool sort_flag_S(t_base *a, t_base *b);




//basic
void ls_flag_l (t_base *head, t_flags* flags, bool is_dir);

char get_acl(t_base *head);

void print_roots (t_base *head);

void print_time(t_base *base, char *time, t_flags *flags);

int get_base_size (t_base *head);

int *correct_space_nlinks (t_base *head, int size);

int *correct_space_uid (t_base *head, int size);

int *correct_space_gid (t_base *head, int size);

int *correct_space_bsize (t_base *head, int size);

void print_total(t_base *head);

void print_uid(t_base *head);

void print_gid(t_base *head);

void print_symlnk(t_base *head);

void print_correct_name(t_base *head, t_flags* flags);




//utils
void del_base_nodes (t_base **node);

void del_base_node (t_base **node);

void del_flag_nodes (t_flags **node);

char *save_strjoin(char const *s1, char const *s2);

void mx_printerr(const char *s);

t_base *get_base_by_idx (t_base *head, int i);

void mx_printcharerr(char c);


#endif //ULS_H
