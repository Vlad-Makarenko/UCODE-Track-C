#include "uls.h"


void tree_function(char *directory_name, t_base **head) {
    DIR *folder;
    struct dirent *directory;
    errno = 0;
    folder = opendir(directory_name);
    if (errno){
        return;
    }

    if (folder != NULL) {
        while ((directory = readdir(folder))) {
            if (mx_strcmp(directory->d_name, ".") != 0 && mx_strcmp(directory->d_name, "..") != 0) {
                
                char *full_name_of_subdirectory = NULL;
                full_name_of_subdirectory = save_strjoin(full_name_of_subdirectory, directory_name);
                full_name_of_subdirectory = save_strjoin(full_name_of_subdirectory, SLESH);
                full_name_of_subdirectory = save_strjoin(full_name_of_subdirectory, directory->d_name);
                struct stat *s_stat = malloc(sizeof (struct stat));
                lstat(full_name_of_subdirectory, s_stat);
                if (S_ISDIR (s_stat->st_mode)){
                    push_back_base(head, mx_strdup(directory->d_name), s_stat, full_name_of_subdirectory);
                }
                tree_function(full_name_of_subdirectory, head);

            }
        }
    }
    closedir(folder);
}

void correct_output(char *argv[], int argc, t_flags *flags){
    t_base *head = NULL;
    int i = 2;
    
    do{
        if (flags->R){
            correct_output_true(i, argv, argc, head, flags, NULL);
            if (argc == 2)
            {
                tree_function(".", &head);
            }else {
                tree_function(argv[i], &head);
            }
            while (head != NULL){
                correct_output_true(i, NULL, argc, NULL, flags, head->path);
                if (head->next) {
                    mx_printstr("\n");      
                 }
                head = head->next;
            }
        }else{
            correct_output_true(i, argv, argc, head, flags, NULL);
        }
        i++;
    } while (i < argc);
    
}
