#include "uls.h"


int main(int argc, char *argv[] ){

    t_base *head = NULL;
    bool is_error = false;    

    if (argc == 1){
        parse_to_base(&head, ".");
        // del_uls_node(&head);
        del_hidden_one(&head);
        sort_files(&head, sort_flag_default); 
        default_ls(head, NULL);
    } else {
        t_flags *flags = get_flags(argv);
        bool checker_argv = false;
        bool checker_files = false;
        if (flags == NULL) { 
            if (argc > 2){
                sort_argv_without_flags(argv, argc);
            }
            char **arr = check_argv(argv, &argc, flags, &checker_argv, &checker_files, &is_error);
            if (checker_argv) {
                if(checker_files) mx_printchar('\n');
                for (int i = 1; i < argc; i++){
                    if (argc > 2 || argv[argc + 1] == NULL){
                        mx_printstr(arr[i]);
                        mx_printstr(":\n");
                    }
                    parse_to_base(&head, arr[i]);
                    del_hidden_one(&head);
                    sort_files(&head, sort_flag_default); 
                    default_ls(head, NULL);
                    if (i + 1 != argc) {
                        mx_printstr("\n");      
                    }
                    
                    del_base_nodes(&head);
                }
            }
            mx_del_strarr(&arr);
        }else {
            sort_argv(argv, argc);
            if(argc >= 3){
                
                char **arr = check_argv(argv, &argc, flags, &checker_argv, &checker_files, &is_error);
                if (checker_argv) {
                    if(checker_files) mx_printchar('\n');
                    correct_output(arr, argc, flags);
                }
                mx_del_strarr(&arr);
            }else {
                correct_output(argv, argc, flags);
            }
            
            
        }

    }
    del_base_nodes(&head);
    
    return (int)is_error;

}
