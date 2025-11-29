// Suraiya P M

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h> // for sleep()

pthread_mutex_t mutex;
char *northFarmer = "North Tunbridge"; // so that I don't have to write these a billion times
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
    // creating a thread for each just once, then running to completion.

    pthread_t north, south;

    pthread_create(&north, NULL, northActivity, (void *)northFarmer);
    pthread_create(&south, NULL, southActivity, (void *)southFarmer);

    pthread_join(north, NULL);
    pthread_join(south, NULL);
    // recombining
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&northCondition);
    pthread_cond_destroy(&southCondition);
    // getting rid of stuff at the end
    exit(0);

    // sync threads output screen access, prevent deadlock. indicate north/south.
    // Print n/s can cross AFTER access to lock, print n/s is traveling, sleep random time <=2 secs, print left bridge before release.
    // other waiting for clear bridge in the meantime
}

void *northActivity(void *params) // lines for north crossing
{
    int turn = 0;
    char *msg = (char *)params;
    while (1) // loops (I think there's a better way for this)
    {
        pthread_mutex_lock(&mutex);
        if (turn >= LIMIT) // I placed a limit because I don't think the hw specified
        {
            pthread_cond_signal(&southCondition);
            pthread_mutex_unlock(&mutex);
            return NULL;
        }
        while (direction != 0)
        {
            pthread_cond_wait(&northCondition, &mutex); // northActivity waits on condition signal for this section
        }
        turn++;
        printf("%s #%d farmer can cross the bridge\n", msg, turn);
        printf("%s #%d is traveling on the bridge\n", msg, turn);
        sleep(rand() % 2); // sleeping
        printf("%s #%d farmer has left the bridge\n", msg, turn); // could probably make a quick function for this printing part, but don't want to break what's working!

        direction = 1;
        pthread_cond_signal(&southCondition); // signalling south
        pthread_mutex_unlock(&mutex); // unlocking
    }
}

void *southActivity(void *param) // the lines for south farmer crossing
{
    int turn = 0;
    char *msg = (char *)param;
    while (1)
    {
        pthread_mutex_lock(&mutex);
        if (turn >= LIMIT)
        {
            pthread_cond_signal(&northCondition); // signals north
            pthread_mutex_unlock(&mutex);
            return NULL;
        }
        while (direction != 1)
        {
            pthread_cond_wait(&southCondition, &mutex); // waits on signal for south
        }
        turn++;
        printf("%s #%d farmer can cross the bridge\n", msg, turn);
        printf("%s #%d is traveling on the bridge\n", msg, turn);
        sleep(rand() % 2); // sleeping
        printf("%s #%d farmer has left the bridge\n", msg, turn);
        direction = 0;
        pthread_cond_signal(&northCondition); // signalling north
        pthread_mutex_unlock(&mutex); // unlocking
    }
}

// https://www.cs.cmu.edu/afs/cs/academic/class/15492-f07/www/pthreads.html
// https://pages.cs.wisc.edu/~remzi/OSTEP/threads-cv.pdf
// Then just lecture slides and src code stuff a bit I think