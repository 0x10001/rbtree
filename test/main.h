#ifndef MAIN_H
#define MAIN_H

#include "../src/rbtree-inline.h"

static inline void _test_append_node(rb_node *node, rb_node *parent, rb_node **link, uintptr_t black) {
  *link = node;
  node->rb_parent = (uintptr_t)parent | black;
  node->rb_left = node->rb_right = NULL;
}

#endif  /* MAIN_H */
