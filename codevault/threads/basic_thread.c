#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void* routine() {
    printf("Executing routine...\n");
    sleep(3);

    return NULL;
}

int main(int argc, char const* argv[]) {
    pthread_t th;

    if (pthread_create(&th, NULL, &routine, NULL) != 0) {
        return EXIT_FAILURE;
    };

    pthread_join(th, NULL);
    printf("%s\n", "Done!");
    return 0;
}