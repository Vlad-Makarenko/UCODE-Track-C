#include "ush.h"

void CTRL_C(int signal) {
    t_jobs_list *list = Jobs_list;
    for (;list->next != NULL;) {
        list = list->next;
    }
    pid_t pid = list->p_id;

    mx_printchar('\n');

    if (pid == Jobs_list->p_id) {
        exit(ES_CTRL_C);
    } else {
        kill(pid, signal);
    }
}

void CTRL_Z(int signal) {
    t_jobs_list *list = Jobs_list;
    int job_id = 0;
    for (;list->next != NULL; ) {
        if (list->j_id > job_id) {
            job_id = list->j_id;
        }
        list = list->next;
    }
    pid_t pid = list->p_id;

    if (pid == list->p_id) {
        return;
    }else {
        kill(pid, signal);
        job_id++;
        list->j_id = job_id;
        mx_printchar('[');
        mx_printint(job_id);
        mx_printstr("]  Stopped\t\t\t");
        mx_printstr(list->command);
        mx_printchar('\n');
    }

}
