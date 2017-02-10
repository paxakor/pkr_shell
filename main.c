#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

#define UNUSED(name) (void) (name)

void type_prompt(int status)
{
    if (status) {
        printf("(%d) ", status);
    }
    printf(">>> ");
}

int read_args(char **args, const int p, const int q)
{
    enum { N = 80 };
    char format[N];
    sprintf(format, "%%%ds", q - 1);
    int i = 0;
    while (i + 1 < p && scanf(format, args[i]) == 1) {
        ++i;
    }
    args[i] = 0;
    return i;
}

int get_path(char *const *envp, const char *cmd, char *path)
{
    const char base[] = "/usr/bin/";
    strcpy(path, base);
    strcat(path, cmd);
    UNUSED(envp);
    return 0;
}

void alloc_args(char **args, const int n, const int m) {
    args[0] = calloc(sizeof(**args), m * n);
    for (int i = 0; i < n; ++i) {
        args[i] = args[0] + i * m * sizeof(**args);
    }
}

void free_args(char **args) {
    free(args[0]);
}

int main(int argc, char **argv, char **envp)
{
    enum { N = 80 };
    int status = 0;
    char path[N];
    char *args[N];
    alloc_args(args, N, N);
    while (1) {
        type_prompt(status);
        if (!read_args((char **) args, N, sizeof(*args))) {
            printf("no args was read. exit.\n");
            break;
        }
        get_path(envp, args[0], path);
        if (fork()) {
            wait(&status);
        } else {
            execv((char *) path, (char **) args);
            perror("execv returned to parent");
        }
    }
    free_args(args);
    UNUSED(argc);
    UNUSED(argv);
    return 0;
}
