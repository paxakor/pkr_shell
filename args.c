// Copyright 2017, Pavel Korozevtsev.

#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "args.h"
#include "defines.h"
#include "utils.h"

int read_args(char **args, const int p, const int q)
{
    char *line = NULL;
    size_t n;
    if (getline(&line, &n, stdin) <= 0) {
        return 0;
    }
    return split(line, args, isspace);
}

const char *find_env_var(char *const *envp, const char* var)
{
    size_t len = strlen(var);
    while(*envp && strncmp(*envp, var, len)) {
        ++envp;
    }
    return *envp + len + 1;  // remove "VAR=" in the beginning of the line
}

int is_colon(int x)
{
    return x == ':';
}

int get_path(char *const *envp, const char *cmd, char *path)
{
    char **vals = (char **) alloc_table(arg_cnt, arg_len, sizeof(**vals));
    split(find_env_var(envp, "PATH"), vals, is_colon);
    unsigned i = 0;
    while (vals[i]) {
        strcpy(path, vals[i]);
        strcat(path, "/");
        strcat(path, cmd);
        if (fexists(path)) {
            break;
        }
        ++i;
    }
    free_table((void **) vals);
    UNUSED(envp);
    return 0;
}
