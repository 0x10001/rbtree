#ifndef ASSERT_H
#define ASSERT_H

#include <stdio.h>


static inline int __assert_failed(const char *file, int line) {
  return fprintf(stderr, "\033[01;31m[ERROR]\033[00m assertion failed: \033[04m%s:%d\033[00m\n", file, line);
}

#define assert(p) ((p) || __assert_failed(__FILE__, __LINE__))

#endif  /* ASSERT_H */
