#include <iostream>
#include <pthread.h>
#include <chrono>

using namespace std;

void* thread_function(void* arg) {
    int thread_id = *((int*)arg);
    printf("Thread %d is running... \n", thread_id);
    return NULL;
}

int main() {
    const int num_threads = 3;
    pthread_t threads[num_threads];

    // Create and start threads
    for (int i = 0; i < num_threads; ++i) {
        int thread_id = i;
        pthread_create(&threads[i], NULL, thread_function, &thread_id);
    }

    // Wait for threads to finish
    for (int i = 0; i < num_threads; ++i) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
