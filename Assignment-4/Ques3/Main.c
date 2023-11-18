#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

sem_t left_sem[5], right_sem[5];

void* left(void* args)
{
    
}

void* right(void* args)
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

    pthread_t left_thread[left_cars], right_thread[right_cars];

    for (int i = 0 ; i < left_cars ; i++)
    {
        pthread_create(&left_thread[i], NULL, left, (void*)i);
    }
    for (int i = 0 ; i < right_cars ; i++)
    {
        pthread_create(&right_thread[i], NULL, right, (void*)i);
    }

}
