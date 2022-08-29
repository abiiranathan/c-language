#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

// ping -c 5 google.com | grep rtt

int main(int argc, char const *argv[]) {
    int fd[2];

    if (pipe(fd) == -1) {
        return 1;
    }

    int pid1 = fork();
    if (pid1 == -1) {
        return 2;
    }

    if (pid1 == 0) {
        // ping process
        close(fd[0]);

        // duplicates fd[1] and connects it to stdout
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
        execlp("ping", "ping", "-c", "5", "localhost", NULL);
    }

    int pid2 = fork();
    if (pid2 == -1) {
        return 2;
    }

    if (pid2 == 0) {
        // grep process
        close(fd[1]);

        // duplicates fd[0] and connects it to stdout
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        execlp("grep", "grep", "rtt", NULL);
    }

    // Inside main process
    close(fd[1]);
    close(fd[0]);

    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    return 0;
}