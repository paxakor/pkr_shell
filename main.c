// Copyright 2017, Pavel Korozevtsev.

#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

#include "args.h"
#include "debug.h"
#include "defines.h"
#include "utils.h"

void type_prompt(int status)
{
    if (status) {
        printf("(%d) ", status);
    }
    printf(">>> ");
}

int main(int argc, char **argv, char **envp)
{
    int status = 0;
    while (1) {
        type_prompt(status);
        char path[arg_len];
        char **args = (char **) alloc_table(arg_cnt, arg_len, sizeof(**args));
        if (!read_args((char **) args, arg_cnt, arg_len)) {
            DODEBUG(printf("exit.\n"));
            break;
        }
        DODEBUG(print_args(args));
        get_path(envp, args[0], path);
        if (fork()) {
            wait(&status);
        } else {
            execv((char *) path, (char **) args);
            perror("execv returned to parent");
        }
        free_table((void **) args);
    }
    UNUSED(argc);
    UNUSED(argv);
    return 0;
}
