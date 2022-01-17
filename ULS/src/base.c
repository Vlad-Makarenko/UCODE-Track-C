#include "uls.h"

t_base *create_base (char *name, struct stat *s_stat, char *path){
    t_base *new_node = malloc (sizeof (t_base));
    
    new_node->name = name;
    new_node->path = path;
    new_node->s_stat = s_stat;
    new_node->next = NULL;

    return new_node;
}   

void push_back_base ( t_base **head, char *name, struct stat *s_stat, char *path){

    t_base *new_node = create_base (name, s_stat, path);

    if (*head == NULL || head == NULL){
        *head = new_node;
        return;
    }
    t_base *temp = *head;
    while (temp->next){
        temp = temp->next;
    }
    temp->next = new_node;

}

void del_uls_node (t_base **head){
    t_base *temp = *head;
    t_base * prev = *head;
    while(temp != NULL) {   
        if (mx_strcmp (temp->name, "uls") == 0) {
            if (temp == *head) {
                *head = (*head)->next;
                del_base_node (&temp);
                temp = *head;
            } else {
                prev->next = temp->next;
                del_base_node (&temp);
                temp =  prev->next;
            }
        } else {
            prev=temp;
            temp=temp->next;
        }
    }
    

}

void del_hidden_one(t_base **head){
    t_base *temp = *head;
    t_base * prev = *head;
    while(temp != NULL) {   
        if (temp->name[0] == '.') {
            if (temp == *head) {
                *head = (*head)->next;
                del_base_node (&temp);
                temp = *head;
            } else {
                prev->next = temp->next;
                del_base_node (&temp);
                temp =  prev->next;
            }
        } else {
            prev=temp;
            temp=temp->next;
        }
    }
}

void del_dote_one(t_base **head){
    t_base *temp = *head;
    t_base * prev = *head;
    
    while(temp != NULL) {  
        if (mx_strcmp(temp->name, ".") == 0 || mx_strcmp(temp->name, "..") == 0) {
            if (temp == *head) {
                *head = (*head)->next;
                del_base_node (&temp);
                temp = *head;
            } else {
                prev->next = temp->next;
                del_base_node (&temp);
                temp =  prev->next;
            }
        } else {
            prev=temp;
            temp=temp->next;
        }
    }
}


void parse_to_base (t_base ** head, char* directory_name){
    DIR *folder;
    struct dirent *directory;
    errno = 0;
    folder = opendir(directory_name);
    if(errno){
        mx_printerr("uls: ");
        mx_printerr(directory_name);
        mx_printerr(": ");
        mx_printerr(strerror(errno));
        mx_printcharerr('\n');
        return;
    }

    if (folder != NULL) {
        while ((directory = readdir(folder))) {
                struct stat *s_stat = malloc (sizeof(struct stat));
                char *name = mx_strdup(directory_name);
                name = save_strjoin(name, SLESH);
                name = save_strjoin(name, directory->d_name);
                if( lstat(name, s_stat) == -1 ){
                    mx_printerr("uls: ");
                    mx_printerr(directory->d_name);
                    mx_printerr(": ");
                    mx_printerr(strerror(errno));
                    mx_printcharerr('\n');
                    exit(1);
                }

                push_back_base(head, mx_strdup(directory->d_name), s_stat, name);
        }
    }
    closedir(folder);
}

