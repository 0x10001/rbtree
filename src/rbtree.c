#include "rbtree-inline.h"

static void _rb_rotate(rb_node **root, rb_node *node, int direction) {
  int opposite = !direction;
  rb_node *p = _rb_get_parent(node);         /* parent */
  rb_node *c = node->rb_children[opposite];  /* child */

  if ((node->rb_children[opposite] = c->rb_children[direction]) != NULL) {
    _rb_set_parent(node->rb_children[opposite], node);
  }
  c->rb_children[direction] = node;
  _rb_set_parent(node, c);

  _rb_set_parent(c, p);
  if (p) {
    p->rb_children[_get_direction(node, p)] = c;
  } else {
    *root = c;
  }
}

static void _rb_rotate2(rb_node **root, rb_node *node, int direction) {
  int opposite = !direction;
  rb_node *p = _rb_get_parent(node);         /* parent */
  rb_node *c = node->rb_children[opposite];  /* child */
  rb_node *gc = c->rb_children[direction];   /* grandchild */

  if ((node->rb_children[opposite] = gc->rb_children[direction]) != NULL) {
    _rb_set_parent(node->rb_children[opposite], node);
  }
  if ((c->rb_children[direction] = gc->rb_children[opposite]) != NULL) {
    _rb_set_parent(c->rb_children[direction], c);
  }
  gc->rb_children[direction] = node;
  _rb_set_parent(node, gc);
  gc->rb_children[opposite] = c;
  _rb_set_parent(c, gc);

  _rb_set_parent(gc, p);
  if (p) {
    p->rb_children[_get_direction(node, p)] = gc;
  } else {
    *root = gc;
  }
}

static void _rb_balance_insertion(rb_node **root, rb_node *node) {
  rb_node *p;  /* parent */
  rb_node *gp; /* grandparent */
  rb_node *ps; /* parent's sibling */
  int p_direction;
  int gp_direction;

  while ((p = _rb_get_parent(node)) != NULL && _rb_is_red(p)) {
    gp = _rb_get_parent(p);

    _rb_set_red(gp);

    p_direction = _get_direction(node, p);
    gp_direction = _get_direction(p, gp);
    ps = gp->rb_children[!gp_direction];

    if (ps != NULL && _rb_is_red(ps)) {
      _rb_set_black(p);
      _rb_set_black(ps);
      node = gp;
      continue;
    }

    if (p_direction == gp_direction) {
      _rb_set_black(p);
      _rb_rotate(root, gp, !gp_direction);
    } else {
      _rb_set_black(node);
      _rb_rotate2(root, gp, !gp_direction);
    }
    break;
  }

  _rb_set_black(*root);
}

void rb_insert(rb_node **root, rb_node *node, rb_node *parent, rb_node **link) {
  *link = node;
  node->rb_parent = (uintptr_t)parent;  /* implicitly marked RED */
  node->rb_left = node->rb_right = NULL;
  _rb_balance_insertion(root, node);
}

static void _rb_balance_removal(rb_node **root, rb_node *node) {
  rb_node *p, *s, *t;
  int direction;
  while ((p = _rb_get_parent(node)) != NULL) {
    direction = _get_direction(node, p);
    s = p->rb_children[!direction];

    if (_rb_is_red(p)) {
      goto RED_PARENT;
    }

    if (_rb_is_black(s)) {
      t = s->rb_children[direction];
      if (t != NULL && _rb_is_red(t)) {
        _rb_set_black(t);
        return _rb_rotate2(root, p, direction);
      }

      t = s->rb_children[!direction];
      if (t != NULL && _rb_is_red(t)) {
        _rb_set_black(t);
        return _rb_rotate(root, p, direction);
      }

      _rb_set_red(s);
      node = p;
      continue;
    }
    
    _rb_set_black(s);
    s = s->rb_children[direction];
    _rb_rotate(root, p, direction);

    RED_PARENT:
    s = s->rb_children[direction];
    if (s != NULL && _rb_is_red(s)) {
      _rb_set_black(p);
      _rb_rotate2(root, p, direction);
    } else {
      _rb_set_red(p);
      _rb_rotate(root, p, direction);
    }

    return _rb_set_black(*root);
  }
}

static rb_node *_rb_remove_left(rb_node **root, rb_node *node) {
  rb_node *p;
  rb_node *c = node->rb_left;
  while (c->rb_right != NULL) {
    c = c->rb_right;
  }

  if (_rb_is_black(c)) {
    if (c->rb_left == NULL) {
      _rb_balance_removal(root, c);
    } else {
      _rb_set_black(c->rb_left);
    }
  }

  if (c != node->rb_left) {
    p = _rb_get_parent(c);
    if ((p->rb_right = c->rb_left) != NULL) {
      _rb_set_parent(c->rb_left, p);
    }
    if ((c->rb_left = node->rb_left) != NULL) {
      _rb_set_parent(node->rb_left, c);
    }
  }
  c->rb_parent = node->rb_parent;

  if ((c->rb_right = node->rb_right) != NULL) {
    _rb_set_parent(node->rb_right, c);
  }
  return c;
}

void rb_remove(rb_node **root, rb_node *node) {
  rb_node *p, *r;
  if (node->rb_left == NULL) {
    if (node->rb_right != NULL) {
      node->rb_right->rb_parent = node->rb_parent;
    } else if (_rb_is_black(node)) {
      _rb_balance_removal(root, node);
    }
    r = node->rb_right;
  } else {
    r = _rb_remove_left(root, node);
  }

  if ((p = _rb_get_parent(node)) != NULL) {
    p->rb_children[_get_direction(node, p)] = r;
  } else {
    *root = r;
  }
}
