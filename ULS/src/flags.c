#include "uls.h"

void mx_printcharerr(char c){
    char *sym = &c;
    write(2, sym, 1);
}

t_flags *create_flags(){
    t_flags *new_node = malloc (sizeof (t_flags));

    new_node->A = false;
    new_node->a = false;
    new_node->C = false;
    new_node->c = false;
    new_node->R = false;
    new_node->r = false;
    new_node->dog = false;
    new_node->e = false;
    new_node->T = false;
    new_node->h = false;
    new_node->t = false;
    new_node->u = false;
    new_node->o = false;
    new_node->one = false;
    new_node->s = false;
    new_node->l = false;
    new_node->S = false;
    new_node->G = false;
    new_node->g = false;

    return new_node;
}


t_flags *get_flags (char *argv[]){
    if (argv[1][0] == '-'){
        t_flags *flags = create_flags();
        int len = mx_strlen(argv[1]);
        for (int i = 1; i < len; i++) {
            switch (argv[1][i])
            {
            case 'l':
                flags->l = true;
                flags->C = false;
                flags->one = false;
                break;
            case 'A':
                flags->A = true;
                break;
            case 'a':
                flags->a = true;
                break;
            case 'C':
                flags->C = true;
                flags->l = false;
                break;
            case 'c':
                flags->c = true;
                flags->u = false;
                break;
            case 'R':
                flags->R = true;
                break;
            case 'r':
                flags->r = true;
                break;
            case '@':
                flags->dog = true;
                break;
            case 'e':
                flags->e = true;
                break;
            case 'T':
                flags->T = true;
                break;
            case 'h':
                flags->h = true;
                break;
            case 't':
                flags->t = true;
                break;
            case 'u':
                flags->u = true;
                flags->c = false;
                break;
            case 'o':
                flags->o = true;
                flags->C = false;
                flags->one = false;
                break;
            case '1':
                flags->one = true;
                flags->l = false;
                flags->o = false;
                flags->g = false;
                break;
            case 's':
                flags->s = true;
                break;
            case 'S':
                flags->S = true;
                break;
            case 'G':
                flags->G = true;
                break;
            case 'g':
                flags->g = true;
                flags->C = false;
                flags->one = false;
                break;
            default:
                free(flags);
                mx_printerr("uls: illegal option -- ");
                mx_printcharerr(argv[1][i]);
                mx_printcharerr('\n');
                mx_printerr("usage: uls [-ACGRSTcgehlortu1] [file ...]\n");
                exit(1);
                break;
            }
        }
        if (!isatty(1)){
            flags->G = false;
        }
        
        return flags;
    } else {
        return NULL;
    }

}



