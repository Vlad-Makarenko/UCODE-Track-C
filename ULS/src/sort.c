#include "uls.h"

int directory_count(t_base * head) {
    int size = 0;
    if (head == NULL) {
        return 0;
    }

    t_base *current = head;

    while (current != NULL) {
        size++;
        current = current->next;
    }

    return size;
}

void sort_argv(char **arr, int size) {
    for (int i = 2; i < size; ++i) {
        for (int j = 2; j < size - 1; ++j) {
            if (mx_strcmp(arr[j], arr[j + 1]) > 0) {
                char *buf = *(arr + j);
                *(arr + j) = *(arr + j + 1);
                *(arr + j + 1) = buf;
            }
        }
    }
}

void sort_argv_without_flags(char **arr, int size) {
    for (int i = 1; i < size; ++i) {
        for (int j = 1; j < size - 1; ++j) {
            if (mx_strcmp(arr[j], arr[j + 1]) > 0) {
                char *buf = *(arr + j);
                *(arr + j) = *(arr + j + 1);
                *(arr + j + 1) = buf;
            }
        }
    }
}

void sort_flag_r(t_base **head){
    t_base * current = *head;
    t_base  *prev = NULL, *next = NULL;
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    *head = prev;
}

bool sort_flag_default(t_base *a, t_base *b){
    return mx_strcmp(a->name, b->name) > 0;
}

bool sort_flag_t(t_base *a, t_base *b){
    if (a->s_stat->st_mtime == b->s_stat->st_mtime) {
        return (a->s_stat->st_mtimespec.tv_nsec < b->s_stat->st_mtimespec.tv_nsec);
    }
    return (a->s_stat->st_mtime < b->s_stat->st_mtime);
}

bool sort_flag_u(t_base *a, t_base *b){
    if (a->s_stat->st_atime == b->s_stat->st_atime) {
        return (a->s_stat->st_atimespec.tv_nsec < b->s_stat->st_atimespec.tv_nsec);
    }
    return (a->s_stat->st_atime < b->s_stat->st_atime);
}

bool sort_flag_c(t_base *a, t_base *b){
    if (a->s_stat->st_ctime == b->s_stat->st_ctime) {
        return (a->s_stat->st_ctimespec.tv_nsec < b->s_stat->st_ctimespec.tv_nsec);
    }
    return (a->s_stat->st_ctime < b->s_stat->st_ctime);

}

bool sort_flag_S(t_base *a, t_base *b){
    return a->s_stat->st_size < b->s_stat->st_size;
}
 

void sort_files(t_base **head, bool (*cmp)(t_base *a, t_base *b)) {
    t_base *temp = *head;
    
    int size = directory_count(temp);

    for (int i = 0; i < size; i++) {
        temp = *head;
        for (int j = 0; j < size - 1; j++) {
            if (cmp(temp, temp->next)) {
                char *tmp_name = temp->name;
                char *tmp_path = temp->path;
                struct stat *tmp_s_stat = temp->s_stat;

                temp->name = temp->next->name;
                temp->path = temp->next->path;
                temp->s_stat = temp->next->s_stat;

                temp->next->name = tmp_name;
                temp->next->path = tmp_path;
                temp->next->s_stat = tmp_s_stat;      

            }
            temp = temp->next;
        }
        
    }
}





