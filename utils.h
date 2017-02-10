// Copyright 2017, Pavel Korozevtsev.

#ifndef PSH_UTILS_H
#define PSH_UTILS_H

int fexists(const char *);
void **alloc_table(const unsigned, const unsigned, const unsigned);
void free_table(void **);
int split(const char *, char **, int (*)(int));

#endif  // PSH_UTILS_H
