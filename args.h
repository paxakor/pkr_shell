// Copyright 2017, Pavel Korozevtsev.

#ifndef PSH_ARGS_H
#define PSH_ARGS_H

int get_path(char *const *, const char *, char *);
int read_args(char **, const int, const int);
void alloc_args(char **, const int, const int);
void free_args(char **);
void print_args(char **);

#endif  // PSH_ARGS_H
