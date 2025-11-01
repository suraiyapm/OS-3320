// Suraiya Poberezhsky Mark, emplid 23756247

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 4

// Goal: Multithreaded program that can find the integer in the range 1 to 10000
// that has the largest number of divisors. Print that number as well as time spent
// to complete calculation. C/C++/Java/Python/etc.
// I will be attempting C since that is what we have some examples of, and I may as well practice it.

// Info to be shared across threads
int max = 0;
int culprit = 0;
pthread_mutex_t m;
// pthread_mutex_t distribution;

// For critical section issue, lock to preserve data consistency with the shared vars.


void *calculateDivisors(void *param)
{ // to calc 1 to sq root for number of divisors.

    int tid = (int) (long) param;
    int beg = tid*2500 +1;
    int end = (tid==NUM_THREADS-1) ? 10000 : (tid+1)*2500;

    // pthread_mutex_lock(&distribution);
    // int section = range - 2500;
    // pthread_mutex_unlock(&distribution);
    for (int i = beg; i<=end; i++)
    {
        int sum = 0;
        for (int j = 1; j*j <= i; j++)
        {
            if (i % j == 0) {
                if (j*j==i) {
                    sum++;
                } else {
                    sum+=2;
                }
            }
        }
        // Wrapping. These functions return 0 if successful.
        pthread_mutex_lock(&m);
        if (sum > max)
        {
            max = sum;
            culprit = i;
        }
        pthread_mutex_unlock(&m);
    }
    pthread_exit(0);
}

    void *printThread(void *tid)
    {
        // To print the thread id for current thread, only, then exits.
        printf("This is thread: %d\n", (int)tid);
        pthread_exit(NULL);
    }

    int main(int argc, char *argv[])
    {
        // Time calculation (I initially thought this was per thread, but I think it's for all)
        clock_t t1 = clock();

        // To create the specified (defined) number of threads, then exit.
        pthread_t threads[NUM_THREADS];
        int status, i;
        for (i = 0; i < NUM_THREADS; i++)
        {
            printf("Main. Creating thread number: %d\n", i);
            status = pthread_create(&threads[i], NULL, calculateDivisors, (void *)(long)i);

            if (status != 0)
            {
                printf("pthread create error code %d \n", status);
                exit(-1);
            }
        }

        // Wait for threads to all finish up
        for (i = 0; i < NUM_THREADS; i++)
        {
            pthread_join(threads[i], NULL);
        }

        // Mildly concerned about whatever amount of pc resources I've alotted for this VM.
        clock_t t2 = clock();
        double totalTime = (double)(t2-t1) /CLOCKS_PER_SEC;
        printf("So the most divs goes to: %d, with: %d divisors.", culprit, max);
        printf("Time taken to calculate: %.4f\n", totalTime); //Clock stuff yoinked from textbook!
        return 0;
    }

    // Sources used to write this:
    /*
    Dropbox multi-thread hello world code
    https://www.dropbox.com/scl/fo/3z5ot6qr99itnuupkosb3/ACKitIh13atPpHwSetWeYXQ/source%20code?dl=0&e=1&preview=multi_thread+hello_world.txt&rlkey=ey74b0tvsw3gkzahense6700n
    Slides/Textbook
    https://www.dropbox.com/scl/fo/3z5ot6qr99itnuupkosb3/ALMIu3soRz16ZjrlOToxbRU/Lectures?dl=0&preview=ch4+Threads+and+concurrency.pptx&rlkey=ey74b0tvsw3gkzahense6700n&subfolder_nav_tracking=1
    https://www.dropbox.com/scl/fo/3z5ot6qr99itnuupkosb3/ALMIu3soRz16ZjrlOToxbRU/Lectures?dl=0&e=1&preview=ch4+Threads+and+concurrency.pptx&rlkey=ey74b0tvsw3gkzahense6700n&subfolder_nav_tracking=1


    */