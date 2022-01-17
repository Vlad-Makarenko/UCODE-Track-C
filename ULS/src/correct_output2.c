#include "uls.h"



void correct_output_true(int i, char *argv[], int argc, t_base *head, t_flags *flags, char *d_name){
    if (d_name){
        mx_printstr(d_name);
        mx_printstr(":\n");
        parse_to_base(&head, d_name);
    }else {
    
        if (argc > 3 || argv[argc + 1] == NULL){
                mx_printstr(argv[i]);
                mx_printstr(":\n");
            }
        
        if (argc == 2 )
        {
            parse_to_base(&head, ".");
        }else {
            parse_to_base(&head, argv[i]);
        }
    }

    //HIDDEN flags
    if(flags->a){
        flags->A = false;
    } else if (flags->A) {
        del_dote_one(&head);
    } else if (!flags->a) {
        del_hidden_one(&head);
    }

    //SORTING flags
    sort_files(&head, sort_flag_default);
    if (flags->S){
        sort_files(&head, sort_flag_S);
    }else if (flags->u && flags->t) {
        sort_files(&head, sort_flag_u);
    }else if (flags->c && flags->t) {
        sort_files(&head, sort_flag_c);
    }else if (flags->t){
        sort_files(&head, sort_flag_t);
    }
    if (flags->r) {
        sort_flag_r(&head);
    }
    
    
    //LONG OUT flags
    if (flags->l || flags->g || flags->o) {
        ls_flag_l(head, flags, true);
    } else if (flags->one){
        print_one(head, flags);
    } else{
        default_ls(head, flags);
    }
    

    if (i + 1 < argc) {
        mx_printstr("\n");      
    }
    
    del_base_nodes(&head);
}


