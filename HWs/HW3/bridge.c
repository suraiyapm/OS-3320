#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h> // for sleep()

pthread_mutex_t mutex;
char *northFarmer = "North Tunbridge";
char *southFarmer = "South Tunbridge";
#define LIMIT 10 // There were soo many with 25 so I'm shrinking it (hw didn't specify how many I think? but I started with 25)
int direction = 0;

pthread_cond_t northCondition;
pthread_cond_t southCondition;

void *northActivity(void *params);
void *southActivity(void *param);

int main()
{
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&northCondition, NULL);
    pthread_cond_init(&southCondition, NULL);

    pthread_t north, south;

    pthread_create(&north, NULL, northActivity, (void *)northFarmer);
    pthread_create(&south, NULL, southActivity, (void *)southFarmer);

    pthread_join(north, NULL);
    pthread_join(south, NULL);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&northCondition);
    pthread_cond_destroy(&southCondition);

    exit(0);

    // sync threads output screen access, prevent deadlock. indicate north/south.
    // Print n/s can cross AFTER access to lock, print n/s is traveling, sleep random time <=2 secs, print left bridge before release.
    // other waiting for clear bridge in the meantime
}

void *northActivity(void *params)
{
    int turn = 0;
    char *msg = (char *)params;
    while (1)
    {
        pthread_mutex_lock(&mutex);
        if (turn >= LIMIT)
        {
            pthread_cond_signal(&southCondition);
            pthread_mutex_unlock(&mutex);
            return NULL;
        }
        while (direction != 0)
        {
            pthread_cond_wait(&northCondition, &mutex);
        }
        turn++;
        printf("%s #%d farmer can cross the bridge\n", msg, turn);
        printf("%s #%d is traveling on the bridge\n", msg, turn);
        sleep(1 + rand() % 2);
        printf("%s #%d farmer has left the bridge\n", msg, turn);

        direction = 1;
        pthread_cond_signal(&southCondition);
        pthread_mutex_unlock(&mutex);
    }
}

void *southActivity(void *param)
{
    int turn = 0;
    char *msg = (char *)param;
    while (1)
    {
        pthread_mutex_lock(&mutex);
        if (turn >= LIMIT)
        {
            pthread_cond_signal(&northCondition);
            pthread_mutex_unlock(&mutex);
            return NULL;
        }
        while (direction != 1)
        {
            pthread_cond_wait(&southCondition, &mutex);
        }
        turn++;
        printf("%s #%d farmer can cross the bridge\n", msg, turn);
        printf("%s #%d is traveling on the bridge\n", msg, turn);
        sleep(1 + rand() % 2);
        printf("%s #%d farmer has left the bridge\n", msg, turn);
        direction = 0;
        pthread_cond_signal(&northCondition);
        pthread_mutex_unlock(&mutex);
    }
}