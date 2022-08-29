#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

void* roll_dice(void* arg) {
    int value = (rand() % 6) + 1;

    *(int*)arg = value;
    pthread_exit(NULL);
}

int main(int argc, char const* argv[]) {
    srand(time(NULL));  // seed the random number generator

    int* res = malloc(sizeof(int));
    pthread_t th;

    if (pthread_create(&th, NULL, &roll_dice, (void*)res) != 0) {
        return 1;
    }

    if (pthread_join(th, NULL) != 0) {
        return 2;
    }

    printf("Result: %d\n", *res);
    free(res);
    return 0;
}