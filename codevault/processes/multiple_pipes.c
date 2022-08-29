#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

// Create 3 processes i.e 2 forks

int main(int argc, char const *argv[]) {
    // Warning: all child processes inherit all file descriptors
    int fd[3][2];  // creates a total of 18 file descriptors
    int i;

    for (i = 0; i < 3; i++) {
        if (pipe(fd[i]) < 0) {
            return 1;
        }
    }

    int pid1 = fork();
    if (pid1 < 0) {
        return 2;
    }

    if (pid1 == 0) {
        // child process 1
        close(fd[0][1]);
        close(fd[1][0]);
        close(fd[2][0]);
        close(fd[2][1]);

        int x;
        read(fd[0][0], &x, sizeof(int));
        x += 5;
        write(fd[1][1], &x, sizeof(int));
        close(fd[0][0]);
        close(fd[1][1]);
        return 0;
    }

    int pid2 = fork();
    if (pid2 < 0) {
        return 3;
    }

    if (pid2 == 0) {
        // child process 2
        close(fd[0][0]);
        close(fd[0][1]);
        close(fd[1][1]);
        close(fd[2][0]);

        int x;
        read(fd[1][0], &x, sizeof(int));
        x += 5;
        write(fd[2][1], &x, sizeof(int));
        close(fd[1][0]);
        close(fd[2][1]);
        return 0;
    }

    // parent process
    close(fd[0][0]);
    close(fd[1][0]);
    close(fd[1][1]);
    close(fd[2][1]);

    int x = 0;
    write(fd[0][1], &x, sizeof(int));
    read(fd[2][0], &x, sizeof(int));

    printf("Result: %d\n", x);
    close(fd[0][1]);
    close(fd[2][0]);

    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    return 0;
}