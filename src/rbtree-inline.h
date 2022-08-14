#ifndef RBTREE_INLINE_H
#define RBTREE_INLINE_H

#include "rbtree.h"

static inline rb_node *_rb_get_parent(rb_node *node) {
  return (rb_node *)(node->rb_parent & ~3);
}

static inline void _rb_set_parent(rb_node *node, rb_node *parent) {
  node->rb_parent = (uintptr_t)parent | node->rb_parent & 1;
}

static inline void _rb_set_red(rb_node *node) {
  node->rb_parent = node->rb_parent & ~1;
}

static inline void _rb_set_black(rb_node *node) {
  node->rb_parent = node->rb_parent | 1;
}

static inline int _rb_is_black(rb_node *node) {
  return node->rb_parent & 1;
}

static inline int _rb_is_red(rb_node *node) {
  return !_rb_is_black(node);
}

static inline int _get_direction(rb_node *node, rb_node *parent) {
  return node == parent->rb_children[1];
}

#endif  /* RBTREE_INLINE_H */
