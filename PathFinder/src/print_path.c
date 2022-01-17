#include "pathfinder.h"

void print_path(t_path_holder *head, char **vertices, int size){
    while (head) {
        mx_printstr(DELIM);
        mx_printchar('\n');
        mx_printstr("Path: ");
        mx_printstr(vertices[head->begin_index]);
        mx_printstr(" -> ");
        mx_printstr(vertices[head->end_index]);
        mx_printchar('\n');
        mx_printstr("Route: ");
        int buf = 0;
        for (int i = head->last_index - 1; i >= 0; i--) {
            mx_printstr(vertices[head->checked_vertices[i] - 1]);
            if ((i - 1) >= 0) {
                mx_printstr(" -> ");
                buf++;
            }
        }
        mx_printchar('\n');
        mx_printstr("Distance: ");
        if (buf == 1) {
            mx_printint(head->final_distance);
        } else {
            for (int i = size - 1; i >= 0; --i) {
                if (head->route[i] != 0) {
                    mx_printint(head->route[i]);
                    if (head->route[i - 1] != 0) {
                        mx_printstr(" + ");
                    }
                }
            }
            mx_printstr(" = ");
            mx_printint(head->final_distance);
        }
        mx_printchar('\n');
        mx_printstr(DELIM);
        mx_printchar('\n');
        head = head->next;
    }
}
