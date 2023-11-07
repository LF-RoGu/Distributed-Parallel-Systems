/*
 * Exercise for garden problem
 */


#include <iostream>
#include "stdint.h"
#include "pthread.h" // For POSIX & Threads
#include "unistd.h" //For pause and sleep
#include "math.h"

#include <time.h>

using namespace std;

/* Total number of threads to be using */
#define THREADS 4

/* Shared mutex for the software */
pthread_mutex_t lock;
/* Use global variable to obtain result, it is easier than using setters & getters */
float g_sumPi = 0;

/* Callback prototype */
void* thread_callback(void* arg);

int main()
{
    /* Variable used to obtain total and locally the value of pi */
    float sumPi = 0;
    /* Creation of THREADS */
    pthread_t thread[THREADS];
    int threadID[THREADS];

    /* Init function to obtain time of the whole process */
    struct timespec start, finish;
    long long elapsed_ts = 0;
    long long elapsed_tms = 0;
    clock_gettime(CLOCK_MONOTONIC, &start);

    /*
     * Create a mutex, if the attribute is set as NULL, the funct
     * will ser as non-recursive.
     * if it is not created successfully it will return -1
     * else returns 0
     */
    if( pthread_mutex_init(&lock,NULL) != 0)
    {
        /* Special function to print if an error occurs */
        perror("mutex not created\n");
    }

    for(uint8_t i = 0; i<THREADS; i++)
    {
        threadID[i] = i;
        /*
         * &thread[i] -> Link the corresponding thread that was created.
         * thread_callback -> Function to be called that receives an argument "void* arg" for each thread.
         * threadID -> Current process being called
         */
        if(pthread_create(&thread[i], NULL, thread_callback, &threadID[i]) != 0)
        {
            printf("Failed to create thread");
        }
    }

    for(int i = 0; i < THREADS; i++)
    {
        pthread_join(thread[i],NULL);
    }

    /* Obtain total time that has elapsed */
    clock_gettime(CLOCK_MONOTONIC, &finish);
    elapsed_ts = (finish.tv_sec - start.tv_sec) + (finish.tv_nsec - start.tv_nsec) / 1e9;
    elapsed_tms = (finish.tv_sec - start.tv_sec) * 1000.0 + (finish.tv_nsec - start.tv_nsec) / 1e6;
    /* Obtain final value into a local variable */
    sumPi = g_sumPi;

    puts("*************************");
    printf("Pi value: %2.20f \n",sumPi);

    puts("*************************");
    printf("Time passed: %lld sec \n",elapsed_ts);
    printf("Time passed: %lld msec \n",elapsed_tms);

    /* Most important step, destroy objects */
    pthread_mutex_destroy(&lock);
    pthread_exit(0);

    return 0;
}

/*
 * Calculate the value of pi in this callback
 */
void* thread_callback(void* arg)
{
    int threadID = (*(int*)arg);
    printf("Thread %d running program...\n", threadID);

    int32_t temp = (*(uint32_t*)arg);
    int32_t r_init = temp*(POINTS/THREADS);
    int32_t r_end = (temp+1)*(POINTS/THREADS);
    float temp_sum = 0;

    /* Allow multiple threads to share the operations */
    for(int i = r_init; i < r_end; i++)
    {
        temp_sum = temp_sum + pow(-1,i)*(4.0/((2.0*i+1)));
    }

    /* Lock all threads and process for the addition */
    pthread_mutex_lock(&lock);
    g_sumPi = g_sumPi + temp_sum;
    /* Release the mutex */
    pthread_mutex_unlock(&lock);
    /* Return 0 or nothing */
    return NULL;
}