#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5
#define NUM_BOWLS 2

int forks[NUM_PHILOSOPHERS] ;
int number_of_bowls_in_use = 0 ;

pthread_mutex_t overall_lock = PTHREAD_MUTEX_INITIALIZER;

void forks_status()
{
    printf("Forks: ") ;
    for (int i = 0 ; i < NUM_PHILOSOPHERS ; i++)
    {
        printf("%d ", forks[i]) ;
    }
    printf("\n") ;
}

void bowls_status()
{
    printf("Bowls in use: %d\n", number_of_bowls_in_use) ;
}

void* philosopher(void* args)
{
    int id = (int) args ;
    while (1)
    {
        printf("Philosopher %d is thinking\n", id) ;
        thinking() ;
        pthread_mutex_lock(&overall_lock) ;
        if (number_of_bowls_in_use < NUM_BOWLS)
        {
            number_of_bowls_in_use++ ;
            if (forks[id] == 0 && forks[(id + 1) % NUM_PHILOSOPHERS] == 0)
            {
                forks[id] = 1 ;
                forks[(id + 1) % NUM_PHILOSOPHERS] = 1 ;
                printf("Philosopher %d is eating\n", id) ;
                forks_status() ;
                bowls_status() ;
                pthread_mutex_unlock(&overall_lock) ;
                eating() ;
                pthread_mutex_lock(&overall_lock) ;
                forks[id] = 0 ;
                forks[(id + 1) % NUM_PHILOSOPHERS] = 0 ;
                number_of_bowls_in_use-- ;
                pthread_mutex_unlock(&overall_lock) ;
            }
            else
            {
                number_of_bowls_in_use-- ;
                pthread_mutex_unlock(&overall_lock) ;
            }
            pthread_mutex_unlock(&overall_lock) ;
        }
        else
        {
            pthread_mutex_unlock(&overall_lock) ;
        }
    }
    return NULL ;
}

void eating()
{
    sleep(1) ;
}

void thinking()
{
    sleep(1) ;
}

signed main(int argc, char *argv[])
{
    pthread_t philosophers[NUM_PHILOSOPHERS] ;
    for (int i = 0 ; i < NUM_PHILOSOPHERS ; i++)
    {
        pthread_create(&philosophers[i], NULL, philosopher, (void*) i) ;
    }
    for (int i = 0 ; i < NUM_PHILOSOPHERS ; i++)
    {
        pthread_join(philosophers[i], NULL) ;
    }
    return 0 ;
}
