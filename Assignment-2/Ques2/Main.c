#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define power 1e9
pid_t pida, pidb, pidc;
struct timespec sa, fa, sb, fb, sc, fc;

int main()
{
    pida = fork();
    if (pida == 0)
    {
        clock_gettime(0, &sa);
        sched_setscheduler(pida, SCHED_OTHER, NULL);
        execl("./Process1", "Process1", NULL, NULL);
    }
    else if (pida > 0)
    {
        pidb = fork();
        if (pidb == 0)
        {
            clock_gettime(0, &sb);
            sched_setscheduler(pidb, SCHED_FIFO, NULL);
            execl("./Process2", "Process2", NULL, NULL);
        }
        else if (pidb > 0)
        {
            pidc = fork();
            if (pidc == 0)
            {
                clock_gettime(0, &sc);
                sched_setscheduler(pidc, SCHED_RR, NULL);
                execl("./Process3", "Process3", NULL, NULL);
            }
            else if (pidc > 0)
            {
            }
            else if (pidc < 0)
            {
                perror("Error in Forking C");
            }
        }
        else if (pidb < 0)
        {
            perror("Error in Forking B");
        }
    }
    else if (pida < 0)
    {
        perror("Error in Forking A");
    }

    float time_store;
    pid_t piw = waitpid(-1, NULL, 0);
    FILE *file_pointer;
    while (piw != -1)
    {
        if (piw == pida)
        {
            clock_gettime(0, &fa);
            time_store = (fa.tv_sec - sa.tv_sec) + (fa.tv_nsec - sa.tv_nsec) / power;
            file_pointer = fopen("file.txt", "a");
            fprintf(file_pointer, "SCHED_OTHER: %f\n", time_store);
        }
        if (piw == pidb)
        {
            clock_gettime(0, &fb);
            time_store = (fb.tv_sec - sb.tv_sec) + (fb.tv_nsec - sb.tv_nsec) / power;
            file_pointer = fopen("file.txt", "a");
            fprintf(file_pointer, "SCHED_FIFO: %f\n", time_store);
        }
        if (piw == pidc)
        {
            clock_gettime(0, &fc);
            time_store = (fc.tv_sec - sc.tv_sec) + (fc.tv_nsec - sc.tv_nsec) / power;
            file_pointer = fopen("file.txt", "a");
            fprintf(file_pointer, "SCHED_RR: %f\n", time_store);
        }
    }
    // system("python3 Graph.py");
    fclose(file_pointer);
    return 0;
}
