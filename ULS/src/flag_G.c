#include "uls.h"

void print_colorful(t_base *head){
    if (S_ISDIR(head->s_stat->st_mode)) {
        mx_printstr(BLUE_CLR);
        mx_printstr(head->name);
        mx_printstr(DEFAULT_CLR);
    } else if (S_ISLNK(head->s_stat->st_mode)) {
        mx_printstr(MAGENTA_CLR);
        mx_printstr(head->name);
        mx_printstr(DEFAULT_CLR);
    } else if (head->s_stat->st_mode & S_IXOTH) {
        mx_printstr(RED_CLR);
        mx_printstr(head->name);
        mx_printstr(DEFAULT_CLR);
    } else if (S_ISBLK(head->s_stat->st_mode)) {
        mx_printstr(BLOCK_CLR);
        mx_printstr(head->name);
        mx_printstr(DEFAULT_CLR);
    } else if (S_ISCHR(head->s_stat->st_mode)) {
        mx_printstr(CHAR_CLR);
        mx_printstr(head->name);
        mx_printstr(DEFAULT_CLR);
    } else if (S_ISSOCK(head->s_stat->st_mode)) {
        mx_printstr(GREEN_CLR);
        mx_printstr(head->name);
        mx_printstr(DEFAULT_CLR);
    } else if (S_ISFIFO(head->s_stat->st_mode)) {
        mx_printstr(YELLOW_CLR);
        mx_printstr(head->name);
        mx_printstr(DEFAULT_CLR);
    } else if (S_ISWHT(head->s_stat->st_mode)) {
        mx_printstr(CYAN_CLR);
        mx_printstr(head->name);
        mx_printstr(DEFAULT_CLR);
    } else if (head->s_stat->st_mode & S_IXUSR) {
        mx_printstr(RED_CLR);
        mx_printstr(head->name);
        mx_printstr(DEFAULT_CLR);
    } else {
        mx_printstr(head->name);
    }
}

