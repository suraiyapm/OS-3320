#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h> // for sleep()

// struct BridgeControl {
// };

pthread_mutex_t mutex;
char *northFarmer = "North Tunbridge";
char *southFarmer = "South Tunbridge";
int turn = 0;
#define LIMIT 25
int direction = 0;

int main()
{

    pthread_mutex_init(&mutex, NULL);

    pthread_t north, south;

    pthread_create(&north, NULL, northActivity, (void*) northFarmer);
    pthread_create(&south, NULL, southActivity, (void*) southFarmer);

    pthread_join(north, NULL);
    pthread_join(south, NULL);

    exit(0);

    // sync threads output screen access, prevent deadlock. indicate north/south.
    // Print n/s can cross AFTER access to lock, print n/s is traveling, sleep random time <=2 secs, print left bridge before release.
    // other waiting for clear bridge in the meantime
}

void *northActivity(void *params)
{
    if (direction!=0) ;
    while (turn <= LIMIT && direction==0)
    {
        pthread_mutex_lock(&mutex);
        char *msg = (char *)params;
        turn++;
        printf("%s #%d farmer can cross the bridge\n", msg, turn);
        printf("%s is traveling", msg);
        sleep(rand() % 2);
        printf("%s farmer is leaving the bridge.", msg);
        direction=1;
        pthread_mutex_unlock(&mutex);
    }
}

void *southActivity(void *param)
{
    if (direction!=1) ;
    while (turn <= LIMIT && direction==1)
    {
        pthread_mutex_lock(&mutex);
        char *msg = (char *)param;
        turn++;
        printf("%s #%d farmer can cross the bridge\n", msg, turn);
        printf("%s is traveling\n", msg);
        sleep(1 + (rand() % 2));
        printf("%s farmer is leaving the bridge.\n", msg);
        direction=0;
        pthread_mutex_unlock(&mutex);
    }
}