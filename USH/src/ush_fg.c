#include "ush.h"

void init_fg(char **command_lines) {
    (void)command_lines;
    t_jobs_list *jobs = Jobs_list;
    for(; jobs->next != NULL;){
        jobs = jobs->next;
    }

    if(jobs == NULL){
        fprintf(stderr, "ush: fg: no such job\n");
        Exit_Status = 1;
        return;
    }

    if(jobs->p_id == Jobs_list->p_id){
        fprintf(stderr, "ush: fg: no current jobs\n");
        Exit_Status = 1;
        return;
    }

    kill(jobs->p_id, SIGCONT);
    int flag = 0;
    waitpid(jobs->p_id, &flag, WUNTRACED);
    Exit_Status = WEXITSTATUS(flag);
    if (!WIFSTOPPED(flag)){
        remove_some_job(&jobs, jobs->p_id);
    }
    if (WIFSIGNALED(flag)) {
        Exit_Status = 130;
    } else {
        Exit_Status = 0;
    }

}
