#include "pathfinder.h"

int mx_get_dist( char *name1, char *name2,  t_vertex_pair *head){
    if (mx_strcmp( name1, name2) == 0) {
        return 0;
    }else {
        t_vertex_pair *temp = head;
        while (temp){
            if ( (mx_strcmp(name1, temp->first_name) == 0 || mx_strcmp(name1, temp->second_name) == 0)
                && (mx_strcmp(name2, temp->first_name) == 0 || mx_strcmp(name2, temp->second_name) == 0) ) {
                return temp->dist;
            }
            temp = temp->next;
        }
    }


    return 0;
}

int **mx_create_adjacency_matrix(char **vertices_arr, t_vertex_pair *head, int size){
    int **adjacency_matrix = (int **)malloc(sizeof(int *) * size);
    for (int i = 0; i < size; ++i) {
        adjacency_matrix[i] = (int *)malloc(sizeof(int) * size);
    }

    for (int i = 0; i < size; i++) {
        adjacency_matrix[i][i] = 0;
        for (int j = 0; j < size; j++) {
            int temp = mx_get_dist(vertices_arr[i], vertices_arr[j], head);
            adjacency_matrix[i][j] = temp;
            adjacency_matrix[j][i] = temp;
        }
    }

    return adjacency_matrix;
}

