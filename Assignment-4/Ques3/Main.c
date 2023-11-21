#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define LEFT -1
#define RIGHT 1

#define MAX_CARS 5

int total_left, total_right ;
int left_count = 0, right_count = 0 ;
sem_t on_bridge ;

int curr_dir = 0 ;

void* left(void* args)
{
    int id = (int)args ;
    if (curr_dir == 0 || curr_dir == LEFT)
    {
        curr_dir = LEFT ;
        if (sem_wait(&on_bridge) != 0)
        {
            perror("Error in sem_wait\n") ;
            exit(1) ;
        }
        crossing(LEFT, id) ;
        if (sem_post(&on_bridge) != 0)
        {
            perror("Error in sem_post\n") ;
            exit(1) ;
        }
    }
    else
    {
        while (right_count != total_right) ;
        curr_dir = LEFT ;
        if (sem_wait(&on_bridge) != 0)
        {
            perror("Error in sem_wait\n") ;
            exit(1) ;
        }
        crossing(LEFT, id) ;
        if (sem_post(&on_bridge) != 0)
        {
            perror("Error in sem_post\n") ;
            exit(1) ;
        }
    }
}

void* right(void* args)
{
    int id = (int)args ;
    if (curr_dir == 0 || curr_dir == RIGHT)
    {
        curr_dir = RIGHT ;
        if (sem_wait(&on_bridge) != 0)
        {
            perror("Error in sem_wait\n") ;
            exit(1) ;
        }
        crossing(RIGHT, id) ;
        if (sem_post(&on_bridge) != 0)
        {
            perror("Error in sem_post\n") ;
            exit(1) ;
        }
    }
    else
    {
        while (left_count != total_left) ;
        curr_dir = RIGHT ;
        if (sem_wait(&on_bridge) != 0)
        {
            perror("Error in sem_wait\n") ;
            exit(1) ;
        }
        crossing(RIGHT, id) ;
        if (sem_post(&on_bridge) != 0)
        {
            perror("Error in sem_post\n") ;
            exit(1) ;
        }
    }
}

void crossing(int dir, int id)
{
    printf("Car %d is crossing the bridge from %s\n", id, dir == LEFT ? "left" : "right") ;
    sleep(2) ;
    printf("Car %d has crossed the bridge from %s\n", id, dir == LEFT ? "left" : "right") ;
    if (dir == LEFT)
    {
        left_count++ ;
    }
    else if (dir == RIGHT)
    {
        right_count++ ;
    }
}

signed main()
{
    printf("Enter total number of cars from left: ");
    scanf("%d", &total_left);
    printf("Enter total number of cars from right: ");
    scanf("%d", &total_right);

    if (sem_init(&on_bridge, 0, MAX_CARS) != 0)
    {
        perror("Error in sem_init\n") ;
        exit(1) ;
    }

    pthread_t left_thread[total_left], right_thread[total_right];

    for (int i = 0; i < total_left; i++)
    {
        if (pthread_create(&left_thread[i], NULL, left, (void*)i) != 0)
        {
            perror("Error in pthread_create\n") ;
            exit(1) ;
        }
    }
    for (int i = 0; i < total_right; i++)
    {
        if (pthread_create(&right_thread[i], NULL, right, (void*)i) != 0)
        {
            perror("Error in pthread_create\n") ;
            exit(1) ;
        }
    }

    for (int i = 0; i < total_left; i++)
    {
        if (pthread_join(left_thread[i], NULL) != 0)
        {
            perror("Error in pthread_join\n") ;
            exit(1) ;
        }
    }
    for (int i = 0; i < total_right; i++)
    {
        if (pthread_join(right_thread[i], NULL) != 0)
        {
            perror("Error in pthread_join\n") ;
            exit(1) ;
        }
    }
    
    if (sem_destroy(&on_bridge) != 0)
    {
        perror("Error in sem_destroy\n") ;
        exit(1) ;
    }

    return 0;
}
