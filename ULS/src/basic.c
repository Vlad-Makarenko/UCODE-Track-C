#include "uls.h"

char get_acl(t_base *head) {
    acl_t tmp;

    if (listxattr(head->path, NULL, 0, XATTR_NOFOLLOW) > 0)
        return ('@');
    if ((tmp = acl_get_file(head->path, ACL_TYPE_EXTENDED))) {
        acl_free(tmp);
        return ('+');
    }
    return (' ');
}

void print_roots (t_base *head){

    switch (head->s_stat->st_mode & S_IFMT) {
        case S_IFSOCK:
            mx_printchar('s');
            break;
        case S_IFLNK:
            mx_printchar('l');
            break;
        case S_IFREG:
            mx_printchar('-');
            break;
        case S_IFBLK:
            mx_printchar('b');
            break;
        case S_IFDIR:
            mx_printchar('d');
            break;
        case S_IFCHR:
            mx_printchar('c');
            break;
        case S_IFIFO:
            mx_printchar('p');
            break;
        default:
            break;
    }

    (head->s_stat->st_mode & S_IRUSR) ? mx_printchar('r') : mx_printchar('-');
    (head->s_stat->st_mode & S_IWUSR) ? mx_printchar('w') : mx_printchar('-');
    // (head->s_stat->st_mode & S_IXUSR) ? mx_printchar('x') : mx_printchar('-');

    if (!(head->s_stat->st_mode & S_IXUSR) && (S_ISUID & head->s_stat->st_mode)){
        mx_printchar('S');
    }else if ((head->s_stat->st_mode & S_IXUSR) && (S_ISUID & head->s_stat->st_mode)){
        mx_printchar('s');
    } else if ((head->s_stat->st_mode & S_IXUSR)){
        mx_printchar('x');
    } else {
        mx_printchar('-');
    }

    (head->s_stat->st_mode & S_IRGRP) ? mx_printchar('r') : mx_printchar('-');
    (head->s_stat->st_mode & S_IWGRP) ? mx_printchar('w') : mx_printchar('-');
    // (head->s_stat->st_mode & S_IXGRP) ? mx_printchar('x') : mx_printchar('-');
    if (!(head->s_stat->st_mode & S_IXUSR) && (S_ISGID & head->s_stat->st_mode)){
        mx_printchar('S');
    }else if ((head->s_stat->st_mode & S_IXUSR) && (S_ISGID & head->s_stat->st_mode)){
        mx_printchar('s');
    } else if ((head->s_stat->st_mode & S_IXUSR)){
        mx_printchar('x');
    } else {
        mx_printchar('-');
    }

    (head->s_stat->st_mode & S_IROTH) ? mx_printchar('r') : mx_printchar('-');
    (head->s_stat->st_mode & S_IWOTH) ? mx_printchar('w') : mx_printchar('-');
    // (head->s_stat->st_mode & S_IXOTH) ? mx_printchar('x') : mx_printchar('-');
    if (!(head->s_stat->st_mode & S_IXUSR) && (S_ISVTX & head->s_stat->st_mode)){
        mx_printchar('T');
    }else if ((head->s_stat->st_mode & S_IXUSR) && (S_ISVTX & head->s_stat->st_mode)){
        mx_printchar('t');
    } else if ((head->s_stat->st_mode & S_IXUSR)){
        mx_printchar('x');
    } else {
        mx_printchar('-');
    }

    mx_printchar(get_acl(head));


    mx_printchar(' ');

}   


void print_time(t_base *base, char *time, t_flags *flags){
    char *new_time = mx_strchr(time, ' ');
    new_time++;
    char new_new_time[30];
    int checker = 0;
    int i = 0;
    if(flags->T){
        for (; new_time[i] != '\n'; i++) {
            new_new_time[i] = new_time[i];
        }
    } else {
        if (1622840400 >= base->s_stat->st_mtime || 1654549200 <= base->s_stat->st_mtime) {
            for(int idx = 0; i < 6; i++, idx++){
                new_new_time[i] = new_time[idx];
            }
            new_new_time[i++] = ' ';
            new_new_time[i++] = ' ';
            for (int idx = 16; idx < 20; i++, idx++){
                 new_new_time[i] = new_time[idx];
            }
        } else {
            for (; checker != 2; i++) {
                if (new_time[i] == ':') {
                    checker++;
                }
                if(checker != 2){
                    new_new_time[i] = new_time[i];
                }
            }
        }
    }
    new_new_time[i] = '\0';
    mx_printstr(new_new_time);
    mx_printchar(' ');
}

int get_base_size (t_base *head) {
    int size = 0;

    if (head == NULL) {
        return 0;
    }

    t_base *current = head;

    while (current != NULL) {
        size++;
        current = current->next;
    }

    return size;
}

int *correct_space_nlinks (t_base *head, int size) {
    int *space_array = malloc(sizeof(int) * size);
    int temp[size];
    t_base *current = head;
    int max_length = 0;
    int i = 0;
    while(current != NULL)
    {
        char *temp_itoa = mx_itoa((int)current->s_stat->st_nlink);
        int number_length = mx_strlen(temp_itoa);
        temp[i] = number_length;

        if(number_length > max_length) {
            max_length = number_length;
            }
        i++;
        current = current->next;
        mx_strdel(&temp_itoa);
    }
    for (int i = 0; i < size; i++) {
        space_array[i] = max_length - temp[i];
    }

   return space_array;
}

int *correct_space_uid (t_base *head, int size) {
    int *space_array = malloc(sizeof(int) * size);
    int temp[size];
    t_base *current = head;
    int max_length = 0;
    int i = 0;
    while(current != NULL)
    {   
        int number_length = 0;
        struct passwd *pwd = getpwuid(head->s_stat->st_uid);
        if (pwd){
            number_length = mx_strlen(pwd->pw_name);
        } else {
            char *tmp_itoa = mx_itoa((int)head->s_stat->st_uid);
            number_length = mx_strlen(tmp_itoa);
            mx_strdel(&tmp_itoa);
        }
        temp[i] = number_length;

        if(number_length > max_length) {
            max_length = number_length;
            }
        i++;
        current = current->next;
    }
    for (int i = 0; i < size; i++) {
        space_array[i] = max_length - temp[i];
    }

   return space_array;
}

int *correct_space_gid (t_base *head, int size) {
    int *space_array = malloc(sizeof(int) * size);
    int temp[size];
    t_base *current = head;
    int max_length = 0;
    int i = 0;
    while(current != NULL)
    {   
        int number_length = 0;
        struct group *grp = getgrgid(head->s_stat->st_gid);
        if (grp){
            number_length = mx_strlen(grp->gr_name);
        } else {
            char *tmp_itoa = mx_itoa((int)head->s_stat->st_gid);
            number_length = mx_strlen(tmp_itoa);
            mx_strdel(&tmp_itoa);
        }
        temp[i] = number_length;

        if(number_length > max_length) {
            max_length = number_length;
            }
        i++;
        current = current->next;
    }
    for (int i = 0; i < size; i++) {
        space_array[i] = max_length - temp[i];
    }

   return space_array;
}

int *correct_space_bsize (t_base *head, int size) {
    int *space_array = malloc(sizeof(int) * size);
    int temp[size];
    t_base *current = head;
    int max_length = 0;
    int i = 0;
    while(current != NULL)
    {
        char *tmp_itoa = mx_itoa((int)current->s_stat->st_size);
        int number_length = mx_strlen(tmp_itoa);
        temp[i] = number_length;
        if(number_length > max_length) {
            max_length = number_length;
        }
        i++;
        current = current->next;
        mx_strdel(&tmp_itoa);
    }

    for (int i = 0; i < size; i++) {
        space_array[i] = max_length - temp[i];
    }

   return space_array;
}

void print_total(t_base *head){
    t_base *temp = head;
    int total = 0;
    while (temp) {
        total += temp->s_stat->st_blocks;
        temp = temp->next;
    }
    mx_printstr("total ");
    mx_printint(total);
    mx_printchar('\n');
}

void print_uid(t_base *head){
    struct passwd *pwd = getpwuid(head->s_stat->st_uid);
    if (pwd){
        mx_printstr(pwd->pw_name);
    } else {
        mx_printint(head->s_stat->st_uid);
    }
    mx_printstr("  ");
}

void print_gid(t_base *head){
    struct group *grp = getgrgid(head->s_stat->st_gid);
    if (grp)
    {
        mx_printstr(grp->gr_name);
    } else {
        mx_printint(head->s_stat->st_gid);
    }
    mx_printstr("  ");
}

void print_symlnk(t_base *head){
    ssize_t nbytes, bufsiz;
    bufsiz = head->s_stat->st_mode + 1;

    if (head->s_stat->st_mode == 0){
        bufsiz = PATH_MAX;
    }

    char *buf = mx_strnew(bufsiz);
    nbytes = readlink(head->path, buf, bufsiz);
    if (nbytes != -1){
        mx_printstr(" -> ");
        mx_printstr(buf);
    }
    mx_strdel(&buf);
}

void print_correct_name(t_base *head, t_flags* flags){
    if (flags){
        if(flags->G){
            print_colorful(head);
        } else {
            mx_printstr (head->name);
        }
        if (S_ISLNK(head->s_stat->st_mode) && (flags->l || flags->g || flags->o)){
            print_symlnk(head);
        }
    } else {
        mx_printstr (head->name);
    }
}

void ls_flag_l (t_base *head, t_flags* flags, bool is_dir){
    int len = get_base_size(head);
    
    int *space_arr_nl = correct_space_nlinks(head, len);
    int *space_arr_bs = correct_space_bsize(head, len);
    int *space_arr_uid = correct_space_uid(head, len);
    int *space_arr_gid = correct_space_gid(head, len);
    
    int idx = 0;

    if(is_dir && head){
        print_total(head);
    }

    while (head) {
        print_roots(head);

        for (int i = 0; i < space_arr_nl[idx]; i++) mx_printchar(' ');
        mx_printint((int)head->s_stat->st_nlink);
        mx_printchar(' ');
        
        if (!flags->g) {
            for (int i = 0; i < space_arr_uid[idx]; i++) mx_printchar(' ');
            print_uid(head);
        }else {
            mx_printchar(' ');
        }
        
        if (!flags->o) {
            for (int i = 0; i < space_arr_gid[idx]; i++) mx_printchar(' ');
            print_gid(head);
        }else {
            mx_printchar(' ');
        }

        for (int i = 0; i < space_arr_bs[idx]; i++) mx_printchar(' ');
        mx_printint((int)head->s_stat->st_size);
        mx_printchar(' ');

        // mx_printint(head->s_stat->st_mtime);
        // mx_printchar('\n');

        if (flags->u){
            print_time(head, ctime((&head->s_stat->st_atime)), flags);
        } else if (flags->c){
            print_time(head, ctime((&head->s_stat->st_ctime)), flags);
        } else {        
            print_time(head, ctime((&head->s_stat->st_mtime)), flags);
        }

        print_correct_name(head, flags);
        mx_printchar('\n');

        idx++;
        head = head->next;
    }
    free(space_arr_nl);
    free(space_arr_bs);
    free(space_arr_gid);
    free(space_arr_uid);

}

