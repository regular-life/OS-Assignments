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

void count(int policy_name)
{
    if (policy_name == 0)
    {
        nice(0);
        sched_setscheduler(getpid(), SCHED_OTHER, NULL);
        
        execl("./Process1", "Process1", NULL, NULL);
    }
    else if (policy_name == 1)
    {
        //nice(0);
        sched_setscheduler(getpid(), SCHED_RR, NULL);
        
        execl("./Process2", "Process2", NULL, NULL);
    }
    else if (policy_name == 2)
    {
        //nice(0);
        sched_setscheduler(getpid(), SCHED_FIFO, NULL);
        
        execl("./Process3", "Process3", NULL, NULL);
    }
}

signed main()
{
    int graph_banau = 0;

    clock_gettime(0, &start_a);
    pida = fork();
    if (pida == 0)
    {
        count(0);
    }
    else if (pida > 0)
    {
        clock_gettime(0, &start_b);
        pidb = fork();
        if (pidb == 0)
        {
            count(1);
            
        }
        else if (pidb > 0)
        {
            clock_gettime(0, &start_c);
            pidc = fork();
            if (pidc == 0)
            {
                count(2);
                
            }
            else if (pidc > 0)
            {
                int w3 = wait(NULL);
                clock_gettime(0, &finish_c);
                graph_banau++;
            }
            else
            {
                perr("fork error");
            }
            int w2 = wait(NULL);
            clock_gettime(0, &finish_b);
            graph_banau++;
        }
        else
        {
            perr("fork error");
        }
        int w1 = wait(NULL);
        clock_gettime(0, &finish_a);
        graph_banau++;
    }
    else
    {
        perr("fork error");
    }
    file = fopen("file.txt", "w");
    fprintf(file, "SCHED_OTHER %lf\n", finish_a.tv_sec - start_a.tv_sec + (finish_a.tv_nsec - start_a.tv_nsec) / power);
    fprintf(file, "SCHED_RR %lf\n", finish_b.tv_sec - start_b.tv_sec + (finish_b.tv_nsec - start_b.tv_nsec) / power);
    fprintf(file, "SCHED_FIFO %lf\n", finish_c.tv_sec - start_c.tv_sec + (finish_c.tv_nsec - start_c.tv_nsec) / power);
    fclose(file);
    if (graph_banau == 3)
    {
        system("python3 Graph.py");
    }
    return 0;
}
