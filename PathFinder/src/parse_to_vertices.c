#include "pathfinder.h"

t_vertex_pair *create_node_vertex_pair(char* f_name, char *s_name, int dist){

    t_vertex_pair *new_node = (t_vertex_pair *)malloc((sizeof(t_vertex_pair)));

    new_node->first_name = f_name;
    new_node->second_name = s_name;
    new_node->dist = dist;
    new_node->next = NULL;

    return new_node;
}

void mx_push_back_vertex_pair(t_vertex_pair **head, char* f_name, char* s_name, int dist){
    t_vertex_pair *new_node = create_node_vertex_pair(f_name, s_name, dist);
    if (*head == NULL || head == NULL){
        *head = new_node;
        return;
    }

    t_vertex_pair *temp = *head;
    while (temp->next){
        temp = temp->next;
    }
    temp->next = new_node;
}


t_vertex_pair *mx_parse_to_vertices (char *file_in_str){

    file_in_str = mx_strchr(file_in_str, '\n');
    file_in_str++;
    char **lines = mx_strsplit(file_in_str, '\n');
    t_vertex_pair *head = NULL;
    for (int i = 0; lines[i]; ++i) {
        int Idx = mx_get_char_index(lines[i], '-');
        char *first_name = mx_strndup(lines[i], Idx);
        char *tmp = mx_strchr(lines[i], '-');
        tmp++;
        Idx = mx_get_char_index(tmp, ',');
        char *second_name = mx_strndup(tmp, Idx);
        tmp = mx_strchr(lines[i], ',');
        tmp++;
        int dist = mx_atoi(tmp);
        mx_push_back_vertex_pair(&head, first_name, second_name, dist);
        first_name = NULL;
        second_name = NULL;
    }


    mx_del_strarr(&lines);
    return head;
}

