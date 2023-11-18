#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

// make a struct for queue
typedef struct queue
{
    int index;
    pthread_t thr;
    int direction;
    struct queue *next;
} Queue;

sem_t left_sem[5], right_sem[5];

void *left(void *args)
{
}

void *right(void *args)
{
}

void passing(int dir)
{
}

signed main()
{
    int left_cars, right_cars;
    printf("Enter the number of cars on left: ");
    scanf("%d", &left_cars);
    printf("Enter the number of cars on right: ");
    scanf("%d", &right_cars);
    Queue *Q_left;
    Queue *Q_right;
    pthread_t left_thread[left_cars], right_thread[right_cars];

    for (int i = 0; i < left_cars; i++)
    {
        void *arr1[2];
        arr1[0] = (void *)Q_left;
        arr1[1] = (void *)i;
        pthread_create(&left_thread[i], NULL, left, (void *)arr1);
    }
    for (int i = 0; i < right_cars; i++)
    {
        void *arr2[2];
        arr2[0] = (void *)Q_right;
        arr2[1] = (void *)i;
        pthread_create(&right_thread[i], NULL, right, (void *)arr2);
    }
}
