#include "pathfinder.h"

void mx_del_vertex_pair(t_vertex_pair **head){
    t_vertex_pair *temp = *head;
    while (temp){
        mx_strdel(&temp->first_name);
        mx_strdel(&temp->second_name);
        t_vertex_pair *to_del = temp;
        temp = temp->next;
        free(to_del);
    }
}

void mx_del_int_arr(int ***arr, int size){

    for (int i = 0; i < size; ++i) {
        free((*arr)[i]);
        (*arr)[i] = NULL;
    }

    free(*arr);
    *arr = NULL;
}

void mx_del_path_holder( t_path_holder **head){
    t_path_holder *temp = *head;
    while (temp){
        free(temp->checked_vertices);
        free(temp->route);
        t_path_holder *to_del = temp;
        temp = temp->next;
        free(to_del);
    }
}
