#include "pathfinder.h"


bool is_unique(char **arr, char* name){
    bool isUnique = true;
    for (int i = 0; arr[i] != NULL; ++i) {
        if (mx_strcmp(arr[i], name) == 0){
            isUnique = false;
        }
    }
    return isUnique;
}


char **mx_unique_vertices(t_vertex_pair *head, int size){

    char **arr_of_vertices = (char **) malloc(sizeof(char *) * (size + 1));
    for (int i = 0; i < size + 1; ++i) {
        arr_of_vertices[i] = NULL;
    }

    t_vertex_pair *temp = head;
    int idx = 0;
    while (temp){
        if (is_unique(arr_of_vertices, temp->first_name)){
            if (idx < size) {
                arr_of_vertices[idx] = mx_strdup(temp->first_name);
                idx++;
            } else {
                mx_printerr("error: invalid number of islands\n");
                exit(0);
            }
        }
        if (is_unique(arr_of_vertices, temp->second_name)){
            if (idx < size) {
                arr_of_vertices[idx] = mx_strdup(temp->second_name);
                idx++;
            } else {
                mx_printerr("error: invalid number of islands\n");
                exit(0);
            }
        }
        temp = temp->next;
    }

    if (idx != size){
        mx_printerr("error: invalid number of islands\n");
        exit(0);
    }
    return arr_of_vertices;
}
