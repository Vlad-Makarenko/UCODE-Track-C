#include "libmx.h"

void mx_push_back(t_list **list, void *data){
    t_list *new_node = mx_create_node(data);
    if (*list == NULL || list == NULL){
        *list = new_node;
        return;
    }
    t_list *temp = *list;
    while (temp->next) {
        temp = temp->next;
    }
    temp->next = new_node;
}


