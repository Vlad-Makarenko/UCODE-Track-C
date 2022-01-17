#include "uls.h"

void mx_printerr(const char *s){
    write(2, s, mx_strlen(s));
}

t_base *get_base_by_idx (t_base *head, int i) {
    int idx = 0;
    while (head) {
        if (idx == i) {
            return head;
        }
        
        idx++;
        head = head->next;
    }
    return NULL;
    
}

void del_base_node (t_base **node){
    t_base *to_del = *node;

    mx_strdel(&(to_del->path));
    mx_strdel(&(to_del->name));
    free(to_del->s_stat);
    free(to_del);
    
    *node = NULL;
}

void del_base_nodes (t_base **node){
    t_base * head = * node;
    while(head!=NULL)
    {
        t_base *to_del = head;
        head = head->next;
        mx_strdel(&(to_del->path));
        mx_strdel(&(to_del->name));
        free(to_del->s_stat);
        free(to_del);
    }
    *node = NULL;
}

void del_flag_nodes (t_flags **node){
    t_flags *to_del = *node;
    free(to_del);
}

char **check_argv(char **argv, int *argc, t_flags *flags, bool *checker_argv, bool *checker_files, bool *is_error){
    int start_idx = argv[1][0] == '-' ? 2 : 1;
    char** arr = malloc(sizeof(char *) * (*argc + 1));
    for (int i = 0; i < *argc + 1; i++) arr[i] = NULL;
    t_base *head = NULL;
    int idx = start_idx;
    
    for (int i = start_idx; i < *argc; i++) {
        errno = 0;
        // char *name = save_strjoin( NULL, argv[i]);
        // char *name = save_strjoin(name, SLESH);
        struct stat *s_stat = malloc(sizeof(struct stat));
        stat(argv[i], s_stat);
        

        if (errno) {
            mx_printerr("uls: ");
            mx_printerr(argv[i]);
            mx_printerr(": ");
            mx_printerr(strerror(errno));
            mx_printerr ("\n");
            *is_error = true;
        }else {
            DIR *folder;
            folder = opendir(argv[i]);
            
            if (errno) {
                
                if(S_ISDIR(s_stat->st_mode)){
                    mx_printerr("uls: ");
                    mx_printerr(argv[i]);
                    mx_printerr(": ");
                    mx_printerr(strerror(errno));
                    mx_printerr ("\n");
                }else {
                    push_back_base(&head, mx_strdup( argv[i]), s_stat, mx_strdup(argv[i]));
                    *checker_files = true;
                }
            } else {
                arr[idx] = mx_strdup(argv[i]);
                idx++;
                closedir(folder);
                *checker_argv = true;
            }
            
            
            
        }
    }
    if(head){
        if(flags){
            if (flags->l) {
                ls_flag_l(head, flags, false);
            }else {
                default_ls (head, flags);
            }
            // mx_printchar('\n');
        } else {
            default_ls (head, flags);
            // mx_printchar('\n');
        }
        del_base_nodes(&head);
    }
    // mx_printstr("THRERRERW\n");
    //     mx_printint(errno);
    *argc = idx;
    return arr;
    
}

char *save_strjoin(char const *s1, char const *s2) {
    if (!s1 && !s2)
        return NULL;
    if (!s1 && s2)
        return mx_strdup(s2);
    if (s1 && !s2)
        return mx_strdup(s1);
    char *new_str = mx_strnew(mx_strlen(s1) + mx_strlen(s2));
    new_str = mx_strcat(mx_strcpy(new_str, s1), s2);
    char *to_delete = (char*)s1;
    mx_strdel(&to_delete);
    return new_str;
}
