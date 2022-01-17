#include "pathfinder.h"


int main(int argc, char *argv[]) {

    char *file_in_str = mx_file_to_str(argv[1]);


    // ERRORS CHECK
    mx_error_checker(argc, argv, file_in_str);

    t_vertex_pair *head = mx_parse_to_vertices(file_in_str);

    mx_check_for_same(head);

    mx_check_monograph(head);

    int count_of_vertices = mx_atoi(file_in_str);

    char **arr_of_vertices = mx_unique_vertices(head, count_of_vertices);

    mx_check_for_duplicate(head);

    mx_check_INT_MAX_error(head);
    // ERRORS END


    int **adjacency_matrix = mx_create_adjacency_matrix(arr_of_vertices, head, count_of_vertices);


    int *distance = (int *)malloc(sizeof(int) * count_of_vertices);
    t_path_holder *path_head = NULL;

    for (int i = 0; i < count_of_vertices; ++i) {
        mx_Dijkstra_algorithm(adjacency_matrix, &distance, count_of_vertices, i);
        for (int j = i + 1; j < count_of_vertices; ++j) {
            mx_find_path(&path_head, adjacency_matrix, distance, count_of_vertices, i, j);
        }
    }

    mx_sort_path(&path_head);
    print_path(path_head, arr_of_vertices, count_of_vertices);

    //mem_free
    mx_del_int_arr(&adjacency_matrix, count_of_vertices);
    mx_del_vertex_pair(&head);
    mx_del_strarr(&arr_of_vertices);
    mx_del_path_holder(&path_head);
    mx_strdel(&file_in_str);
    free(distance);

    return 0;
}
