// Copyright 2017, Pavel Korozevtsev.

#ifndef PSH_DEFINES_H
#define PSH_DEFINES_H

#define UNUSED(name) (void)(name)

#ifdef DEBUG
#define DODEBUG(expression) expression
#else
#define DODEBUG(expression)
#endif

enum { arg_cnt = 80, arg_len = 128 };

#endif  // PSH_DEFINES_H
