#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Interprocess communication with pipes i.e in-memory file

int main(int argc, char const *argv[]) {
    int fd[2];
    // fd[0] - Read end
    // fd[1] - Write end

    if (pipe(fd) == -1) {
        fprintf(stderr, "An error occured with opening pipe\n");
        return 1;
    }

    int pid = fork();
    if (pid == 0) {
        // child process
        close(fd[0]);  // we do not read from this process

        int x;
        printf("Input a number: ");
        scanf("%d", &x);

        write(fd[1], &x, sizeof(int));  // could fail(-1)
        close(fd[1]);
    } else {
        close(fd[1]);  // we do not write to this pipe

        int y;
        read(fd[0], &y, sizeof(int));  // could fail (-1)
        close(fd[0]);
        printf("Got from child process: %d\n", y);
    }

    return 0;
}