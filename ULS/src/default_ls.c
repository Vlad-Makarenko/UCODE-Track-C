#include "uls.h"

void print_one(t_base * head, t_flags *flags){
    while (head){
        print_correct_name(head, flags);
        // mx_printstr(head->name);
        mx_printchar('\n');
        head = head->next;
    }
    
}

int max_len_of_name(t_base *head) {
    int max = 0;
    while (head){
        int tmp = mx_strlen (head->name);
        if (tmp > max)
            max = tmp;

        head = head->next;
    }

    if (max % 8 == 0){
        max += 8;
    }else{
        max = 8 - (max % 8) + max;
    }
    return max;
}


void print_tab(int max_len, char * name){
    int tab_count = 0;
    int temp = max_len - mx_strlen(name);
    tab_count = (temp % 8 != 0) ? (temp / 8) + 1 : temp / 8;
    for (int i = 0; i < tab_count; i++) mx_printchar('\t');
}

void print_cols(t_base *head, int count_rows, int count, int len, t_flags *flags) {
    for (int i = 0; i < count_rows; i++) {
        for (int j = 0; i + j < count; j += count_rows) {
            t_base *temp = get_base_by_idx(head, i + j);
            print_correct_name(temp, flags);
            // mx_printstr(temp->name);
            if (get_base_by_idx(head, i + j + 1) && (i + j + count_rows < count))
                print_tab(len, temp->name);
        }
        if (i != count_rows - 1)
            mx_printchar('\n');
    }
}

void names_ouput(t_base *head, int len, int col, t_flags *flags){
    bool is_empty = true;
    int count_cols = 1;
    int count_rows = 0;
    if ( col / len  != 0 ) {
        count_cols = col / len;
    }
    int count_files = directory_count (head);
    if (len * count_cols > col && count_cols != 1){
        count_cols--;
    }
    if (count_files * len > col) {
        count_rows = count_files / count_cols;
        if (count_rows == 0 || count_files % count_cols != 0){
            count_rows += 1;
        }
        print_cols(head, count_rows, count_files, len, flags);
        is_empty = false;
    } else{
        while (head) {
            print_correct_name(head, flags);
            is_empty = false;
            // mx_printstr(head->name);
            if (head->next){
                print_tab(len, head->name);
            }
            head = head->next;
        }
    }
    if (!is_empty) mx_printchar('\n');
}

void default_ls (t_base *head, t_flags *flags){
    if (flags) {
        if (!isatty(1) && !flags->C){    
            print_one(head, flags);
            return;
        } 

        struct winsize win_size;
        int len = max_len_of_name(head);

        ioctl(1, TIOCGWINSZ, &win_size);
        if (isatty(1)){
            names_ouput(head, len, win_size.ws_col, flags);
        }else{
            names_ouput(head, len, 80, flags);
        }
        // mx_printchar('\n');
    } else {
        if (!isatty(1)){    
            print_one(head, flags);
            return;
        } 
        struct winsize win_size;
        int len = max_len_of_name(head);

        ioctl(1, TIOCGWINSZ, &win_size);
        if (isatty(1)){
            names_ouput(head, len, win_size.ws_col, flags);
        }
        // mx_printchar('\n');
    }
    
    
}


