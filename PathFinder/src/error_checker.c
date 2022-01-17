#include "pathfinder.h"


void check_first_line(char **lines){
    for (int i = 0; lines[0][i] != '\0'; ++i) {
        if (!mx_isdigit(lines[0][i])){
            mx_printerr("error: line 1 is not valid\n");
            exit(0);
        }
    }
}

void print_line_error(int num){
    mx_printerr("error: line ");
    mx_printerr(mx_itoa(num + 1) );
    mx_printerr(" is not valid\n");
    exit(0);
}

void check_other_lines(char **lines){

    for (int i = 1; lines[i]; ++i) {
        if(mx_strlen(lines[i]) < 5) print_line_error(i);
        int Idx_i = 0;
        int Idx_j = 0;
        for ( ; mx_isalpha(lines[i][Idx_i]); ++Idx_i);
        if (Idx_i == 0 || lines[i][Idx_i] != '-') print_line_error(i);
        ++Idx_i;
        for ( ; mx_isalpha(lines[i][Idx_j + Idx_i]); ++Idx_j);
        if (Idx_j  + Idx_i == Idx_i || lines[i][Idx_j + Idx_i] != ',') print_line_error(i);
        Idx_j++;
        int cur_len = Idx_j + Idx_i;
        for (; mx_isdigit(lines[i][Idx_j + Idx_i]); ++Idx_j);
        if ( mx_strlen(lines[i]) - cur_len != (Idx_i + Idx_j) - cur_len) print_line_error(i);

    }
    
}

void check_enter(char *file_in_str){
    if (!mx_isdigit(file_in_str[0])){
        print_line_error(0);
    }
    int count_enter = 0;
    for (int i = 0; file_in_str[i]; ++i) {
        if (file_in_str[i] == '\n'){
            count_enter++;
        }
        if (file_in_str[i] == '\n' && file_in_str[i + 1] == '\n'){
            print_line_error(count_enter);
        }
    }
}

void mx_error_checker(int argc, char *argv[], char *file_in_str){
    if (argc != 2){
        mx_printerr("usage: ./pathfinder [filename]\n");
        exit(0);
    }
    if (file_in_str == NULL){
        mx_printerr("error: file ");
        mx_printerr(argv[1]);
        mx_printerr(" does not exist\n");
        exit(0);
    }
    if (mx_strlen(file_in_str) == 0){
        mx_printerr("error: file ");
        mx_printerr(argv[1]);
        mx_printerr(" is empty\n");
        exit(0);
    }

    char **lines = mx_strsplit(file_in_str, '\n');
    check_first_line(lines);
    check_other_lines(lines);
    check_enter(file_in_str);


    mx_del_strarr(&lines);
}

void mx_check_monograph(t_vertex_pair *head){
    t_vertex_pair *temp1 = head;
    t_vertex_pair *temp2 = head;
    int counter = 0;
    for (int i = 0; temp1; ++i) {
        for (int j = 0; temp2; ++j) {
            if ( ((mx_strcmp (temp1->first_name, temp2->first_name) == 0)
                || (mx_strcmp (temp1->first_name, temp2->second_name) == 0))
                || ((mx_strcmp (temp1->second_name, temp2->first_name) == 0)
                 || (mx_strcmp (temp1->second_name, temp2->second_name) == 0)) ){
                counter++;
            }
            temp2 = temp2->next;
        }
        if (counter <= 1) {
//            print_line_error(i + 1); // or i ?
            mx_printerr("error: invalid number of islands\n");
            exit(0);
        }
        temp2 = head;
        temp1 = temp1->next;
        counter = 0;
    }
}

void mx_check_for_same(t_vertex_pair *head){
    t_vertex_pair *temp = head;
    for (int i = 0; temp; ++i) {
        if (mx_strcmp(temp->first_name, temp->second_name) == 0){
            print_line_error(i + 1);
        }
        temp = temp->next;
    }
}

void mx_check_for_duplicate( t_vertex_pair *head){
    t_vertex_pair *temp = head;
    t_vertex_pair *buf = temp->next;
    for (int i = 0; temp; ++i) {
        for (int j = 0; buf; ++j) {
            if (((mx_strcmp(temp->first_name, buf->first_name) == 0
                && mx_strcmp(temp->second_name, buf->second_name) == 0 )
                || (mx_strcmp(temp->first_name, buf->second_name) == 0
                && mx_strcmp(temp->second_name, buf->first_name) == 0) )
                && (i != j)){
                mx_printerr("error: duplicate bridges\n");
                exit(0);
            }
            buf = buf->next;
        }
        temp = temp->next;
        buf = head;
    }
}

void mx_check_INT_MAX_error(t_vertex_pair *head){
    long count = 0;
    while (head){
        count += head->dist;
        if (count > INF){
            mx_printerr("error: sum of bridges lengths is too big\n");
            exit(0);
        }
        head = head->next;
    }
}


