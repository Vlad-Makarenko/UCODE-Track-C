
#ifndef PATHFINDER_PATHFINDER_H
#define PATHFINDER_PATHFINDER_H

#include "libmx.h"

#define DELIM "========================================"
#define INF 2147483647


typedef struct  s_vertex_pair{
    char *first_name;
    char *second_name;
    int dist;
    struct s_vertex_pair *next;
}               t_vertex_pair;

typedef struct s_path_holder {
    int begin_index;
    int end_index;
    int last_index;
    int *checked_vertices;
    int *route;
    int final_distance;
    struct s_path_holder *next;
}               t_path_holder;

//ERRORS
void mx_error_checker(int argc, char *argv[], char *file_in_str);

void mx_check_monograph(t_vertex_pair *head);

void mx_check_for_same(t_vertex_pair *head);

void mx_check_for_duplicate( t_vertex_pair *head);

void mx_check_INT_MAX_error(t_vertex_pair *head);


//Part of libmx
void mx_printerr(const char *s);

int mx_atoi(const char *str);

int *get_copy_arr (int *arr, int size);

int **get_copy_matrix (int **arr, int size);

int size_of_route ( const int *arr, int size);


//Parsing
t_vertex_pair *mx_parse_to_vertices (char *file_in_str);

char **mx_unique_vertices(t_vertex_pair *head, int size);

int **mx_create_adjacency_matrix(char **vertices_arr, t_vertex_pair *head, int size);

int mx_get_dist( char *name1, char *name2,  t_vertex_pair *head);


//Path holding
t_path_holder *create_path_node(int begin_index, int end_index, int last_idx, int *checked_vertices, int *route, int final_dist, int size);

void push_back_path (t_path_holder **head, int begin_index, int end_index, int last_idx, int *checked_vertices, int *route, int final_dist, int size);

void print_path(t_path_holder *head, char **vertices, int size);

void mx_sort_path(t_path_holder **head);

int mx_path_size(t_path_holder *list);

void swap_node (t_path_holder **node1, t_path_holder **node2);


//Algorithm
void mx_Dijkstra_algorithm( int **adjacency_matrix, int **distance, int size, int begin_index);

void mx_find_path (t_path_holder **head, int **adjacency_matrix, int *distance, int size, int begin_index, int end_index);



//Free memory
void mx_del_vertex_pair(t_vertex_pair **head);

void mx_del_int_arr(int ***arr, int size);

void mx_del_path_holder( t_path_holder **head);

#endif //PATHFINDER_PATHFINDER_H
