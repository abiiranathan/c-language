#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
    int pid = fork();
    if (pid == -1) {
        return 1;
    }

    if (pid == 0) {
        while (1) {
            printf("Some text goes here\n");
            usleep(50000);
        }
    } else {
        sleep(2);
        kill(pid, SIGKILL);
        wait(NULL);
    }

    return 0;
}