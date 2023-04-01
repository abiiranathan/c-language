#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "os.h"

#define NUM_THREADS 5
#define FILENAME "data.txt"

File* file;

void* thread_func(void* arg) {
    int i;
    for (i = 0; i < 10; i++) {
        if (file_lock(file, 0, 0) == 0) {
            printf("Thread %ld locked file\n", (long)arg);
            // Do some file I/O here
            char buffer[100];
            snprintf(buffer, sizeof(buffer), "Thread %ld wrote %d\n", (long)arg, i);
            file_write(file, buffer, strlen(buffer));
            // Unlock the file
            file_unlock(file, 0, 0);
            printf("Thread %ld unlocked file\n", (long)arg);
        } else {
            printf("Thread %ld waiting on the file lock\n", (long)arg);
        }
    }
    pthread_exit(NULL);
}

int main() {
    int i;
    pthread_t threads[NUM_THREADS];
    file = file_open(FILENAME, "w");
    if (file == NULL) {
        printf("Failed to open file\n");
        exit(1);
    }

    for (i = 0; i < NUM_THREADS; i++) {
        int rc = pthread_create(&threads[i], NULL, thread_func, (void*)(long)i);
        if (rc) {
            printf("Failed to create thread %d\n", i);
            exit(1);
        }
    }
    for (i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    file_free(file);
    return 0;
}
