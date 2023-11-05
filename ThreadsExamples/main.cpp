#include <iostream>
#include "stdint.h"
#include "pthread.h" // For POSIX & Threads
#include "unistd.h" //For pause and sleep

using namespace std;

#define THREADS 4

void* thread_callback(void* arg)
{
    int threadID = (*(int*)arg);
    printf("Thread %d running program...\n", threadID);
    return NULL;
}

int main()
{
    pthread_t thread[THREADS];
    uint8_t threads_u8 = THREADS;

    for(uint8_t i = 0; i<THREADS; i++)
    {
        int threadID = i;
        /* Creates a thread that calles the funct "printHello" */
        if(pthread_create(&thread[i], NULL, thread_callback, &threadID) != 0)
        {
            printf("Failed to create thread");
        }
    }

    // Wait for threads to finish
    for (int i = 0; i < THREADS; ++i) {
        pthread_join(thread[i], NULL);
    }

    return 0;
}
