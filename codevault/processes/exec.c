#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>  // waiting for process termination
#include <unistd.h>

int main(int argc, char const *argv[]) {
    int pid = fork();
    if (pid == -1) {
        return 1;
    }

    if (pid == 0) {
        // child process
        // Replaces the process
        execlp("ls", "ls", "-la", NULL);
    } else {
        // Parent process
        wait(NULL);  // wait for any child process
        printf("Success\n");
    }

    return 0;
}