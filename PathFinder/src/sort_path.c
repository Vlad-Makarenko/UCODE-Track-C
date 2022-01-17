#include "pathfinder.h"

int mx_path_size(t_path_holder *list){
    int size = 0;

    if (list == NULL){
        return 0;
    }

    t_path_holder *current = list;

    while (current != NULL){
        size++;
        current = current->next;
    }


    return size;
}

void swap_node (t_path_holder **node1, t_path_holder **node2){
    t_path_holder *tmp_node1 = *node1;
    t_path_holder *tmp_node2 = *node2;
    
    int tmp_b_i = tmp_node1->begin_index;
    int tmp_e_i = tmp_node1->end_index;
    int tmp_l_i = tmp_node1->last_index;
    int *tmp_ch_v = tmp_node1->checked_vertices;
    int *tmp_r = tmp_node1->route;

    tmp_node1->begin_index = tmp_node2->begin_index;
    tmp_node1->end_index = tmp_node2->end_index;
    tmp_node1->last_index =  tmp_node2->last_index;
    tmp_node1->checked_vertices = tmp_node2->checked_vertices;
    tmp_node1->route = tmp_node2->route;

    tmp_node2->begin_index = tmp_b_i;
    tmp_node2->end_index = tmp_e_i;
    tmp_node2->last_index = tmp_l_i;
    tmp_node2->checked_vertices = tmp_ch_v;
    tmp_node2->route = tmp_r;
}

void mx_sort_path(t_path_holder **head){
    t_path_holder *current = *head;

    int size = mx_path_size(current);

    for (int i = 0; i < size; i++) {
        current = *head;
        for (int j = 0; j < size - 1; j++) {
            if (current->begin_index == current->next->begin_index 
                && current->end_index == current->next->end_index
                && current->last_index == current->next->last_index) {
                    for (int k = current->last_index - 1; k >= 0 ; k--) {
                        if ((current->checked_vertices[k] - 1) > (current->next->checked_vertices[k] - 1) ) {
                            swap_node(&current, &current->next);
                        }
                        
                    }
                    
            }
            current = current->next;
        }
    }
}
