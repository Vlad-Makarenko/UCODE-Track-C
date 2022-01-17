
#ifndef USH_H
#define USH_H

#define _GNU_SOURCE
#define _POSIX_C_SOURCE 200809L 
#define _XOPEN_SOURCE 500 
#include <sys/stat.h>
#include <sys/types.h>
#include <termios.h>
#include <sys/xattr.h>
#include <signal.h>
#include <pwd.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>
#include <sys/acl.h>
#include <sys/dir.h>
#include <sys/ioctl.h>
#include <sys/param.h>
#include <termios.h>
#include <sys/wait.h>
#include <grp.h>
#include <dirent.h>
#include <limits.h>
#include <term.h>
#include <curses.h>


#include "libmx.h"
#include "builtin.h"
#include "utilities.h"

#define SLESH "/"


#define ES_CTRL_C       130     /* # exit status for ctrl + c signal */
#define ES_BIG_ERR       147




void ush();

void CTRL_C(int signal);

void CTRL_Z(int signal);

char * read_line_from_terminal(void);

void command_substitution(char **string, int *return_value);

char **command_parser(char *command);


//////////////////// PID \\\\\\\\\\\\\\\\\\\\\\\|

typedef struct s_jobs_list{
    pid_t p_id;
    int j_id;
    char *command;
    struct s_jobs_list *next;
}      t_jobs_list;


t_jobs_list *jl_new_node(pid_t p_id, char *command);

void jl_clear(t_jobs_list **head);

void push_back_job(t_jobs_list **head, pid_t p_id, char *command);

void remove_some_job(t_jobs_list **head, pid_t p_id);


//////////////// GLOBAL variables \\\\\\\\\\\\\\|

extern char **environ;

t_jobs_list *Jobs_list;

int Exit_Status;


//////////////////////////// processes \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\|

void produce_job(char **argv, char *command_line, char *cmd);

void make_process(char **argv, char *cmd);

void add_job(char *command_line, pid_t p_id); 
    


////////////////////// INPUT CORRECTION\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\|

void tilda_correction(char **command);

void tilda_positive(char **command);

void tilda_negative(char **command);

void tilda_slesh(char **command);

void tilda_foo(char **command);

void tilda(char **command);




#endif //USH_H
