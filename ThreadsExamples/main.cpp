/*
 * In this example, we use the pthread library to create and manage threads.
 * We create three threads and assign a unique ID to each thread.
 * The thread_function is the function that will be executed by each thread,
 * and it simply prints the thread's ID. We wait for all threads to finish using pthread_join.
 */


#include <iostream>
#include "stdint.h"
#include "pthread.h" // For POSIX & Threads
#include "unistd.h" //For pause and sleep

using namespace std;

#define THREADS 4

uint8_t g_varProcess;

void set_processFromThread(uint8_t varProcess)
{
    g_varProcess = varProcess;
}

uint8_t get_processFromThread()
{
    return g_varProcess;
}

void* thread_callback(void* arg)
{
    int threadID = (*(int*)arg);
    printf("Process... %d. Thread %d running program...\n", get_processFromThread(), threadID);
    return NULL;
}

int main()
{
    pthread_t thread[THREADS];
    uint8_t threads_u8 = THREADS;

    for(uint8_t i = 0; i<THREADS; i++)
    {
        int threadID = i;
        set_processFromThread(threadID);
        /*
         * &thread[i] -> Link the corresponding thread that was created.
         * thread_callback -> Function to be called that receives an argument "void* arg" for each thread.
         * threadID -> Current process being called
         */
        if(pthread_create(&thread[i], NULL, thread_callback, &threadID) != 0)
        {
            printf("Failed to create thread");
        }
    }

    // Wait for threads to finish
    for (int i = 0; i < THREADS; ++i) {
        printf("Waiting on Thread... %d \n", get_processFromThread());
        pthread_join(thread[i], NULL);
    }

    return 0;
}
