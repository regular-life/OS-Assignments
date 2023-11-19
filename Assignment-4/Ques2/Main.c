#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

int capacity, passengers ;

sem_t se, travel, se2 ;

bool load_flag = false ;
bool unload_flag = false ;

void* car(void* args)
{
    load() ;
    sleep(5) ;
    for (int i = 0 ; i < min(capacity, passengers) ; i++)
    {
        sem_post(&se) ;
    }
    for (int i = 0 ; i < min(capacity, passengers) ; i++)
    {
        sem_wait(&se2) ;
    }
    printf("Car is moving") ;
    for (int i = 0 ; i < 10 ; i ++)
    {
        sleep(1) ;
        printf(".") ;
    }
    printf("\n") ;
    unload() ;
    for (int i = 0 ; i < min(capacity, passengers) ; i++)
    {
        sem_post(&travel) ;
    }
    return NULL ;
}

void* passenger(void* args)
{
    int id = (int)args ;
    sem_wait(&se) ;
    board(id) ;
    sem_post(&se2) ;
    sem_wait(&travel) ;
    offboard(id) ;
    return NULL ;
}

void load()
{
    printf("Car is starting loading process....\n") ;
    sleep(2) ;
    load_flag = true ;
    printf("Passengers can board the car now\n") ;
}

void unload()
{
    printf("Car is starting unloading process....\n") ;
    sleep(2) ;
    unload_flag = true ;
    printf("Passengers can offboard the car now\n") ;
}

void board(int id)
{
    if (load_flag == true)
    {
        printf("Passenger %d has boarded the car\n", id) ;
        sleep(0.5) ;
    }
    else
    {
        printf("Passengers cannot board the car now\n") ;
    }
}

void offboard(int id)
{
    if (unload_flag == true)
    {
        printf("Passenger %d has offboarded the car\n", id) ;
        sleep(0.5) ;
    }
    else
    {
        printf("Passengers cannot offboard the car now\n") ;
    }
}

int min(int a, int b)
{
    if (a < b)
    {
        return a ;
    }
    return b ;
}

signed main()
{
    printf("Capacity of the bus: ");
    scanf("%d", &capacity) ;
    printf("Total number of passengers: ") ;
    scanf("%d", &passengers) ;
    sem_init(&se, 0, 0) ;
    sem_init(&travel, 0, 0) ;
    sem_init(&se2, 0, 0) ;
    pthread_t janta[passengers] ;
    pthread_t car_thread ;
    int prev = 0 ;
    while (passengers > 0)
    {
        for (int i = prev ; i < prev + min(capacity, passengers) ; i++)
        {
            pthread_create(&janta[i], NULL, passenger, (void*)i) ;
        }
        pthread_create(&car_thread, NULL, car, NULL) ;
        pthread_join(car_thread, NULL) ;
        for (int i = prev ; i < prev + min(capacity, passengers) ; i++)
        {
            pthread_join(janta[i], NULL) ;
        }
        prev = prev + min(capacity, passengers) ;
        passengers -= min(capacity, passengers) ;
    }
    sem_destroy(&se) ;
    sem_destroy(&travel) ;
    sem_destroy(&se2) ;
    printf("All passengers have been transported\n") ;
}
