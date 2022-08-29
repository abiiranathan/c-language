#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char **argv) {
    DIR *dir;
    struct dirent *ent;
    char *path = NULL;

    if (argc > 1)
        path = argv[1];
    else
        path = ".";

    if ((dir = opendir(path)) == NULL) {
        perror("opendir");
        exit(1);
    }

    // print total size of all files in current directory
    struct stat st;
    int total_size = 0;

    while ((ent = readdir(dir)) != NULL) {
        // pretty print
        struct stat st;
        stat(ent->d_name, &st);
        total_size += st.st_size;

        char *perms = malloc(10);
        char *time = malloc(20);
        char *date = malloc(20);

        // permissions
        if (st.st_mode & S_IRUSR)
            perms[0] = 'r';
        else
            perms[0] = '-';
        if (st.st_mode & S_IWUSR)
            perms[1] = 'w';
        else
            perms[1] = '-';
        if (st.st_mode & S_IXUSR)
            perms[2] = 'x';
        else
            perms[2] = '-';
        if (st.st_mode & S_IRGRP)
            perms[3] = 'r';
        else
            perms[3] = '-';

        if (st.st_mode & S_IWGRP)
            perms[4] = 'w';
        else
            perms[4] = '-';

        if (st.st_mode & S_IXGRP)
            perms[5] = 'x';
        else
            perms[5] = '-';

        if (st.st_mode & S_IROTH)
            perms[6] = 'r';
        else
            perms[6] = '-';

        if (st.st_mode & S_IWOTH)
            perms[7] = 'w';
        else
            perms[7] = '-';

        if (st.st_mode & S_IXOTH)
            perms[8] = 'x';
        else
            perms[8] = '-';

        perms[9] = '\0';

        // time
        time_t t = st.st_mtime;
        struct tm *tm = localtime(&t);
        strftime(time, 20, "%H:%M", tm);

        // date
        strftime(date, 20, "%d-%m-%Y", tm);

        // print each item in a column
        printf("%1s %10s %10s %10ld %s\n", perms, time, date, st.st_size,
               ent->d_name);
    }

    printf("Total size of all files in current directory: %d\n", total_size);

    closedir(dir);
    return 0;
}
