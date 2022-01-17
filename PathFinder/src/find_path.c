#include "pathfinder.h"

int size_of_route ( const int *arr, int size){
    int counter = 0;
    for (int i = 0; i < size; ++i) {
        if (arr[i] != 0) {
            counter++;
        }
    }

    return counter;
}



int **get_copy_matrix (int **arr, int size){
    int **matrix = malloc(sizeof (int *) * size);
    for (int i = 0; i < size; ++i) {
        matrix[i] = malloc(sizeof (int) * size);
    }

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            matrix[i][j] = arr[i][j];
        }
    }

    return matrix;

}


void mx_find_path (t_path_holder **head, int **adjacency_matrix, int *distance, int size, int begin_index, int end_index) {
    int *checked_vertices = malloc(sizeof(int) * size);
    checked_vertices[0] = end_index + 1;
    int last_idx = 1;
    int weight = distance[end_index];
    int copy_end_idx = end_index;
    int *route = malloc(sizeof(int) * size);
    for (int i = 0; i < size; ++i) route[i] = 0;

    int checker = 0;
    int counter = 0;
    int save_end_idx = 0;
    int save_i = 0;

    int last_save_i = 0;
    int last_save_end_idx = 0;

    while (end_index != begin_index && counter < size * size) {

        for (int i = 0; i < size; ++i) {
            if (adjacency_matrix[end_index][i] != 0) {
                int temp = weight - adjacency_matrix[end_index][i];
                if (temp == distance[i]) {
                    route[last_idx] = adjacency_matrix[end_index][i];

                    last_save_end_idx = save_end_idx;
                    last_save_i = save_i;
                    save_end_idx = end_index;
                    save_i = i;

                    if (checker == 0) {
                        checker++;
                        last_save_end_idx = save_end_idx;
                        last_save_i = save_i;
                    }

                    weight = temp;
                    end_index = i;
                    checked_vertices[last_idx] = i + 1;
                    last_idx++;

                }
            }
        }

        counter++;
    }

    if (checker == 1) {

        int **copy_adjacency_matrix = get_copy_matrix(adjacency_matrix, size);

        copy_adjacency_matrix[last_save_end_idx][last_save_i] = 0;
        copy_adjacency_matrix[last_save_i][last_save_end_idx] = 0;

        if (size_of_route( route, size) >= 1
            && begin_index == checked_vertices[last_idx - 1] - 1) {
            push_back_path(head, begin_index, copy_end_idx, last_idx, checked_vertices, route, distance[copy_end_idx], size);
        }
        mx_find_path(head, copy_adjacency_matrix, distance, size, begin_index, copy_end_idx);
        mx_del_int_arr(&copy_adjacency_matrix, size);
    } else if (size_of_route( route, size) >= 1
               && begin_index == checked_vertices[last_idx - 1] - 1) {
        push_back_path(head, begin_index, copy_end_idx, last_idx, checked_vertices, route, distance[copy_end_idx], size);

    }
    free(checked_vertices);
    free(route);
}


