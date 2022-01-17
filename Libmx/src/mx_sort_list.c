#include "libmx.h"


t_list *mx_sort_list (t_list *list, bool (*cmp)(void *a, void *b)){
    if (list == NULL || cmp == NULL){
        return list;
    }
    int size = 0;
    t_list *current = list;
    while (current != NULL){
        size++;
        current = current->next;
    }
    for (int i = 0; i < size; ++i) {
        current = list;
        for (int j = 0; j < size - 1; ++j) {
            if (cmp(current->data, current->next->data)) {
                void *buf = current->data;
                current->data = current->next->data;
                current->next->data = buf;
            }
            current = current->next;
        }
    }
    return list;
}

