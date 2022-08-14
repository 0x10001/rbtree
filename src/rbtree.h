#ifndef RBTREE_H
#define RBTREE_H

#include <stdint.h>

#ifndef NULL
#define NULL ((void *)0)
#endif  /* NULL */

typedef struct rb_node {
  uintptr_t rb_parent;
  struct rb_node *rb_children[0];
  struct rb_node *rb_left;   /* rb_children[0] */
  struct rb_node *rb_right;  /* rb_children[1] */
} rb_node;


void rb_insert(rb_node **root, rb_node *node, rb_node *parent, rb_node **link);
void rb_remove(rb_node **root, rb_node *node);

#endif  /* RBTREE_H */
