#include "pathfinder.h"

int *get_copy_arr (int *arr, int size){
   int * copy = malloc(sizeof(int) * size);
   for (int i = 0; i < size; ++i) {
       copy[i] = arr[i];
   }
   return copy;
}

t_path_holder *create_path_node(int begin_index, int end_index, int last_idx, int *checked_vertices, int *route, int final_dist, int size){
    t_path_holder *new_node = malloc(sizeof (t_path_holder));

    new_node->begin_index = begin_index;
    new_node->end_index = end_index;
    new_node->last_index = last_idx;
    new_node->checked_vertices = get_copy_arr(checked_vertices, size);
    new_node->route = get_copy_arr(route, size);
    new_node->final_distance = final_dist;
    new_node->next = NULL;

    return new_node;
}

void push_back_path (t_path_holder **head, int begin_index, int end_index, int last_idx, int *checked_vertices, int *route, int final_dist, int size){

    t_path_holder *new_node = create_path_node(begin_index, end_index, last_idx, checked_vertices, route, final_dist, size);

    if (*head == NULL || head == NULL){
        *head = new_node;
        return;
    }
    t_path_holder *temp = *head;
    while (temp->next){
        temp = temp->next;
    }
    temp->next = new_node;

}


