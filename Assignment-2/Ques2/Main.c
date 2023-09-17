#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define power 1e9
pid_t pida, pidb, pidc;
struct timespec sa, fa, sb, fb, sc, fc;
float time_store_a;
float time_store_b;
float time_store_c;
FILE *file;
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
        wait(NULL);
        clock_gettime(0, &fa);
        time_store_a = (fa.tv_sec - sa.tv_sec) + (fa.tv_nsec - sa.tv_nsec) / power;
        file = fopen("file.txt", "a");
        fprintf(file, "a %f\n", time_store_a);
        pidb = fork();
        if (pidb == 0)
        {
            clock_gettime(0, &sb);
            sched_setscheduler(pidb, SCHED_FIFO, NULL);
            execl("./Process2", "Process2", NULL, NULL);
        }
        else if (pidb > 0)
        {
            wait(NULL);
            clock_gettime(0, &fb);
            time_store_b = (fb.tv_sec - sb.tv_sec) + (fb.tv_nsec - sb.tv_nsec) / power;
            file = fopen("file.txt", "a");
            fprintf(file, "b %f\n", time_store_b);
            pidc = fork();
            if (pidc == 0)
            {
                clock_gettime(0, &sc);
                sched_setscheduler(pidc, SCHED_RR, NULL);
                execl("./Process3", "Process3", NULL, NULL);
            }
            else if (pidc > 0)
            {
                wait(NULL);
                clock_gettime(0, &fc);
                time_store_c = (fc.tv_sec - sc.tv_sec) + (fc.tv_nsec - sc.tv_nsec) / power;
                file = fopen("file.txt", "a");
                fprintf(file, "c %f\n", time_store_c);
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
    fclose(file);
    // system("python3 Graph.py");
    return 0;
}
