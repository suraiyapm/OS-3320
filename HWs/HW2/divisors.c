// Suraiya Poberezhsky Mark, emplid 23756247

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 4

// Goal: Multithreaded program that can find the integer in the range 1 to 10000
// that has the largest number of divisors. Print that number as well as time spent
// to complete calculation. C/C++/Java/Python/etc.
// I will be attempting C since that is what we have some examples of, and I may as well practice it.

void *printThread(void *tid) {
    // To print the thread id for current thread, only, then exits.
    printf("This is thread: %d\n", (int) tid);
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    // To create the specified (defined) number of threads, then exit.
    pthread_t threads[NUM_THREADS];
    int status, i;
    for (i=0; i<NUM_THREADS; i++) {
        printf("Main. Creating thread number: %d\n", i);
        status = pthread_create(&threads[i], NULL, printThread, (void *)i);
        if (status!=0) {
            printf("pthread create error code %d \n", status);
            exit(-1);
        }
    }

    // Wait for threads to all finish up
    for (i=0; i<NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    return 0;
}