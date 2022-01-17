#include "ush.h"



t_jobs_list *jl_new_node(pid_t p_id, char *command) {
    t_jobs_list *obj = (t_jobs_list *)malloc(sizeof(t_jobs_list));
    obj->p_id = p_id;
    obj->j_id = 0;
    obj->command = mx_strdup(command);
    obj->next = NULL;

    return obj;
}

void jl_clear(t_jobs_list **head) {
    t_jobs_list *new_ptr = *head;

    for(;new_ptr != NULL;) {
        t_jobs_list *buff = new_ptr->next;
        if(new_ptr->p_id != getpid()) {
            kill(new_ptr->p_id, SIGINT);
        }
        mx_strdel(&new_ptr->command);
        free(new_ptr);
        new_ptr = buff;
    }
    *head = NULL;
}

void push_back_job(t_jobs_list **head, pid_t p_id, char *command) {
    t_jobs_list *new_node = jl_new_node(p_id, command);
    t_jobs_list *tmp = NULL;
    if (head == NULL || *head == NULL) {
        *head = new_node;
        (*head)->next = NULL;
    }
    else {
        tmp = *head;
        for (;tmp->next != NULL;) {
            tmp = tmp->next;
        }
        tmp->next = new_node;
        tmp->next->next = NULL;
    }
}

void remove_some_job(t_jobs_list **head, pid_t p_id){

    t_jobs_list *current = *head;
    t_jobs_list *buf = current;
    while (current != NULL){
        if (current->p_id == p_id){
            if (*head == current) {
                *head = current->next;
                mx_strdel(&current->command);
                mx_strdel(&current->prikole);
                free(current);
                break;
            }
            buf->next = current->next;
            mx_strdel(&current->command);
            free(current);
            break;
        }
        buf = current;
        current = current->next;
    }

}

