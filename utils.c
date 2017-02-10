// Copyright 2017, Pavel Korozevtsev.

#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "defines.h"

int fexists(const char *path)
{
    struct stat st;
    return stat(path, &st) == 0;
}

void **alloc_table(const unsigned n, const unsigned m, const unsigned sz)
{
    char **table = calloc(n, sizeof(char *));
    table[0] = calloc(n * m, sz);
    for (unsigned i = 1; i < n; ++i) {
        table[i] = table[0] + i * m * sz / sizeof(**table);
    }
    return (void **) table;
}

void free_table(void **table) {
    free(table[0]);
    free(table);
}

int split(const char *line, char **words, int (*is_delim)())
{
    unsigned bias = 0, iter = 0;
    while (iter + 1 < arg_cnt) {
        while (line[bias] && is_delim(line[bias])) {
            ++bias;
        }
        if (!line[bias]) {
            break;
        }
        unsigned t = bias;
        while (line[t] && !is_delim(line[t])) {
            ++t;
        }
        unsigned len = t - bias;
        strncpy(words[iter], line + bias, len);
        words[iter][len] = 0;
        bias = ++t;
        ++iter;
    }
    words[iter] = 0;
    return iter;
}
