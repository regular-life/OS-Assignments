#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define power 1e9
pid_t pida, pidb, pidc;
struct timespec start_a, finish_a, start_b, finish_b, start_c, finish_c;
double time_store_a;
double time_store_b;
double time_store_c;
FILE *file;
int main()
{
    clock_gettime(0, &start_a);
    pida = fork();
    if (pida == 0)
    {
        sched_setscheduler(pida, SCHED_OTHER, NULL);
        execl("./Process1", "Process1", NULL, NULL);
    }
    else if (pida > 0)
    {
        wait(NULL);
        clock_gettime(0, &finish_a);
        time_store_a = (finish_a.tv_sec - start_a.tv_sec) + (finish_a.tv_nsec - start_a.tv_nsec) / power;
        file = fopen("file.txt", "a");
        fprintf(file, "SCHED_OTHER %f\n", time_store_a);
        clock_gettime(0, &start_b);
        pidb = fork();
        if (pidb == 0)
        {
            sched_setscheduler(pidb, SCHED_RR, NULL);
            execl("./Process2", "Process2", NULL, NULL);
        }
        else if (pidb > 0)
        {
            wait(NULL);
            clock_gettime(0, &finish_b);
            time_store_b = (finish_b.tv_sec - start_b.tv_sec) + (finish_b.tv_nsec - start_b.tv_nsec) / power;
            file = fopen("file.txt", "a");
            fprintf(file, "SCHED_RR %f\n", time_store_b);
            clock_gettime(0, &start_c);
            pidc = fork();
            if (pidc == 0)
            {
                sched_setscheduler(pidc, SCHED_FIFO, NULL);
                execl("./Process3", "Process3", NULL, NULL);
            }
            else if (pidc > 0)
            {
                wait(NULL);
                clock_gettime(0, &finish_c);
                time_store_c = (finish_c.tv_sec - start_c.tv_sec) + (finish_c.tv_nsec - start_c.tv_nsec) / power;
                file = fopen("file.txt", "a");
                fprintf(file, "SCHED_FIFO %f\n", time_store_c);
            }
            else if (pidc < 0)
            {
                // C
                fprintf(stderr, "fork failed\n");
            }
        }
        else if (pidb < 0)
        {
            // B
            fprintf(stderr, "fork failed\n");
        }
    }
    else if (pida < 0)
    {
        // A
        fprintf(stderr, "fork failed\n");
    }
    fclose(file);
    // system("python3 Graph.py");
    return 0;
}
