// Copyright 2017, Pavel Korozevtsev.

#include <stdio.h>

void print_args(char **args)
{
    printf("args:\n");
    while (*args) {
        printf("%s\n", *args++);
    }
    printf("end args\n");
}
