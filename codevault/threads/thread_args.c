#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

void* routine(void* arg) {
    int index = *(int*)arg;
    printf("%d ", primes[index]);

    free(arg);
    return NULL;
}

int main(int argc, char const* argv[]) {
    pthread_t th[10];

    for (int i = 0; i < 10; i++) {
        int* index = malloc(sizeof(int));
        *index = i;

        if (pthread_create(&th[i], NULL, &routine, index) != 0) {
            perror("failed to create thread");
        };
    }

    for (int i = 0; i < 10; i++) {
        if (pthread_join(th[i], NULL) != 0) {
            perror("failed to join thread");
        };
    }
    printf("\n");

    return 0;
}