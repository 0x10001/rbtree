#include "assert.h"
#include "main.h"

void test_root() {
  rb_node node;
  rb_node *root = NULL;

  rb_insert(&root, &node, root, &root);
  assert(&node == root);
  assert(_rb_is_black(root));
  assert(root->rb_left == NULL);
  assert(root->rb_right == NULL);

  rb_remove(&root, root);
  assert(root == NULL);
}

void test_insert_0() {
  rb_node nodes[3];
  rb_node *root = NULL;

  /*
    0B
  */
  _test_append_node(&nodes[0], NULL, &root, 1);

  /*
    0B
      \
      1R
  */
  rb_insert(&root, &nodes[1], &nodes[0], &nodes[0].rb_right);
  assert(&nodes[0] == root);
  assert(_rb_is_black(root));
  assert(root->rb_left == NULL);
  assert(root->rb_right == &nodes[1]);
  assert(root == _rb_get_parent(&nodes[1]));

  /*
      0B
     /  \
    2R  1R
  */
  rb_insert(&root, &nodes[2], &nodes[0], &nodes[0].rb_left);
  assert(&nodes[0] == root);
  assert(_rb_is_black(root));
  assert(root->rb_left == &nodes[2]);
  assert(root == _rb_get_parent(&nodes[2]));
  assert(root->rb_right == &nodes[1]);
  assert(root == _rb_get_parent(&nodes[1]));
}

void test_insert_1() {
  rb_node nodes[10];
  rb_node *root = NULL;

  /*
            0B
          /    \
        1R      2B
       /  \    /  \
      3B  4B  5R  6R
     /  \
    7R  8R
  */
  _test_append_node(&nodes[0], NULL, &root, 1);
  _test_append_node(&nodes[1], &nodes[0], &nodes[0].rb_left, 0);
  _test_append_node(&nodes[2], &nodes[0], &nodes[0].rb_right, 1);
  _test_append_node(&nodes[3], &nodes[1], &nodes[1].rb_left, 1);
  _test_append_node(&nodes[4], &nodes[1], &nodes[1].rb_right, 1);
  _test_append_node(&nodes[5], &nodes[2], &nodes[2].rb_left, 0);
  _test_append_node(&nodes[6], &nodes[2], &nodes[2].rb_right, 0);
  _test_append_node(&nodes[7], &nodes[3], &nodes[3].rb_left, 0);
  _test_append_node(&nodes[8], &nodes[3], &nodes[3].rb_right, 0);

  /*
            1B
          /    \
        3R      0B
       /  \    /  \
      7B  8B  4B  2B
     /           /  \
    9R          5R  6R
  */
  rb_insert(&root, &nodes[9], &nodes[7], &nodes[7].rb_left);
  assert(root == &nodes[1]);
  assert(_rb_is_black(root));
  assert(nodes[1].rb_left == &nodes[3]);
  assert(&nodes[1] == _rb_get_parent(&nodes[3]));
  assert(_rb_is_red(&nodes[3]));
  assert(nodes[1].rb_right == &nodes[0]);
  assert(&nodes[1] == _rb_get_parent(&nodes[0]));
  assert(_rb_is_red(&nodes[0]));
  assert(nodes[0].rb_left == &nodes[4]);
  assert(&nodes[0] == _rb_get_parent(&nodes[4]));
  assert(_rb_is_red(&nodes[0]));
  assert(nodes[3].rb_left == &nodes[7]);
  assert(&nodes[3] == _rb_get_parent(&nodes[7]));
  assert(_rb_is_black(&nodes[7]));
  assert(nodes[3].rb_right == &nodes[8]);
  assert(&nodes[3] == _rb_get_parent(&nodes[8]));
  assert(_rb_is_black(&nodes[8]));
  assert(nodes[7].rb_left == &nodes[9]);
  assert(&nodes[7] == _rb_get_parent(&nodes[9]));
  assert(_rb_is_red(&nodes[9]));
}

void test_insert_2() {
  rb_node nodes[10];
  rb_node *root = NULL;

  /*
          0B
        /    \
      1B      2R
     /  \    /  \
    3R  4R  5B  6B
           /  \
          7R  8R
  */
  _test_append_node(&nodes[0], NULL, &root, 1);
  _test_append_node(&nodes[1], &nodes[0], &nodes[0].rb_left, 1);
  _test_append_node(&nodes[2], &nodes[0], &nodes[0].rb_right, 0);
  _test_append_node(&nodes[3], &nodes[1], &nodes[1].rb_left, 0);
  _test_append_node(&nodes[4], &nodes[1], &nodes[1].rb_right, 0);
  _test_append_node(&nodes[5], &nodes[2], &nodes[2].rb_left, 1);
  _test_append_node(&nodes[6], &nodes[2], &nodes[2].rb_right, 1);
  _test_append_node(&nodes[7], &nodes[5], &nodes[5].rb_left, 0);
  _test_append_node(&nodes[8], &nodes[5], &nodes[5].rb_right, 0);

  /*
            5B
          /    \
        0R      2R
       /  \    /  \
      1B  7B  8B  6B
     /  \   \
    3R  4R  9R
  */
  rb_insert(&root, &nodes[9], &nodes[7], &nodes[7].rb_right);
  assert(root == &nodes[5]);
  assert(_rb_is_black(root));
  assert(nodes[5].rb_left == &nodes[0]);
  assert(&nodes[5] == _rb_get_parent(&nodes[0]));
  assert(_rb_is_red(&nodes[0]));
  assert(nodes[5].rb_right == &nodes[2]);
  assert(&nodes[5] == _rb_get_parent(&nodes[2]));
  assert(_rb_is_red(&nodes[2]));
  assert(nodes[0].rb_left == &nodes[1]);
  assert(&nodes[0] == _rb_get_parent(&nodes[1]));
  assert(_rb_is_black(&nodes[1]));
  assert(nodes[0].rb_right == &nodes[7]);
  assert(&nodes[0] == _rb_get_parent(&nodes[7]));
  assert(_rb_is_black(&nodes[7]));
  assert(nodes[2].rb_left == &nodes[8]);
  assert(&nodes[2] == _rb_get_parent(&nodes[8]));
  assert(_rb_is_black(&nodes[8]));
  assert(nodes[2].rb_right == &nodes[6]);
  assert(&nodes[2] == _rb_get_parent(&nodes[6]));
  assert(_rb_is_black(&nodes[6]));
  assert(nodes[7].rb_right == &nodes[9]);
  assert(&nodes[7] == _rb_get_parent(&nodes[9]));
  assert(_rb_is_red(&nodes[9]));
}

void test_remove_0() {
  rb_node nodes[7];
  rb_node *root = NULL;

  /*
          0B
        /    \
      1B      2B
     /  \    /
    3R  4R  5R
  */

  _test_append_node(&nodes[0], NULL, &root, 1);
  _test_append_node(&nodes[1], &nodes[0], &nodes[0].rb_left, 1);
  _test_append_node(&nodes[2], &nodes[0], &nodes[0].rb_right, 1);
  _test_append_node(&nodes[3], &nodes[1], &nodes[1].rb_left, 0);
  _test_append_node(&nodes[4], &nodes[1], &nodes[1].rb_right, 0);
  _test_append_node(&nodes[5], &nodes[2], &nodes[2].rb_left, 0);

  /*
        4B
       /  \
      1B  2B
     /   /
    3R  5R
  */
  rb_remove(&root, &nodes[0]);
  assert(root == &nodes[4]);
  assert(_rb_is_black(&nodes[4]));
  assert(nodes[4].rb_left == &nodes[1]);
  assert(&nodes[4] == _rb_get_parent(&nodes[1]));
  assert(_rb_is_black(&nodes[1]));
  assert(nodes[4].rb_right == &nodes[2]);
  assert(&nodes[4] == _rb_get_parent(&nodes[2]));
  assert(_rb_is_black(&nodes[2]));
  assert(nodes[1].rb_left == &nodes[3]);
  assert(&nodes[1] == _rb_get_parent(&nodes[3]));
  assert(_rb_is_red(&nodes[3]));
  assert(nodes[1].rb_right == NULL);

  /*
      1B
     /  \
    3B  2B
       /
      5R
  */
  rb_remove(&root, &nodes[4]);
  assert(root == &nodes[1]);
  assert(_rb_is_black(&nodes[1]));
  assert(nodes[1].rb_left == &nodes[3]);
  assert(&nodes[1] == _rb_get_parent(&nodes[3]));
  assert(_rb_is_black(&nodes[3]));
  assert(nodes[1].rb_right == &nodes[2]);
  assert(&nodes[1] == _rb_get_parent(&nodes[2]));
  assert(_rb_is_black(&nodes[2]));

  /*
      1B
     /  \
    3B  5B
  */
  rb_remove(&root, &nodes[2]);
  assert(root == &nodes[1]);
  assert(_rb_is_black(&nodes[1]));
  assert(nodes[1].rb_left == &nodes[3]);
  assert(&nodes[1] == _rb_get_parent(&nodes[3]));
  assert(_rb_is_black(&nodes[3]));
  assert(nodes[1].rb_right == &nodes[5]);
  assert(&nodes[1] == _rb_get_parent(&nodes[5]));
  assert(_rb_is_black(&nodes[5]));
}

void test_remove_1() {
  rb_node nodes[13];
  rb_node *root = NULL;

  /*
           0B
        /      \
      1B        2R
     /  \     /    \
    3B  4B  5B      6B
           /  \    /  \
          7B  8B  9R  10B
                 /  \
                11B 12B
  */
  _test_append_node(&nodes[0], NULL, &root, 1);
  _test_append_node(&nodes[1], &nodes[0], &nodes[0].rb_left, 1);
  _test_append_node(&nodes[2], &nodes[0], &nodes[0].rb_right, 0);
  _test_append_node(&nodes[3], &nodes[1], &nodes[1].rb_left, 1);
  _test_append_node(&nodes[4], &nodes[1], &nodes[1].rb_right, 1);
  _test_append_node(&nodes[5], &nodes[2], &nodes[2].rb_left, 1);
  _test_append_node(&nodes[6], &nodes[2], &nodes[2].rb_right, 1);
  _test_append_node(&nodes[7], &nodes[5], &nodes[5].rb_left, 1);
  _test_append_node(&nodes[8], &nodes[5], &nodes[5].rb_right, 1);
  _test_append_node(&nodes[9], &nodes[6], &nodes[6].rb_left, 0);
  _test_append_node(&nodes[10], &nodes[6], &nodes[6].rb_right, 1);
  _test_append_node(&nodes[11], &nodes[9], &nodes[9].rb_left, 1);
  _test_append_node(&nodes[12], &nodes[9], &nodes[9].rb_right, 1);

  /*
           0B
        /      \
      1B        9R
     /  \     /    \
    3B  4B  2B      6B
           /  \    /  \
          7B  11B 12B 10B
            \
            8R
  */
  rb_remove(&root, &nodes[5]);
  assert(root == &nodes[0]);
  assert(_rb_is_black(&nodes[0]));
  assert(nodes[0].rb_left == &nodes[1]);
  assert(&nodes[0] == _rb_get_parent(&nodes[1]));
  assert(_rb_is_black(&nodes[1]));
  assert(nodes[0].rb_right == &nodes[9]);
  assert(&nodes[0] == _rb_get_parent(&nodes[9]));
  assert(_rb_is_red(&nodes[9]));
  assert(nodes[9].rb_left == &nodes[2]);
  assert(&nodes[9] == _rb_get_parent(&nodes[2]));
  assert(_rb_is_black(&nodes[2]));
  assert(nodes[9].rb_right == &nodes[6]);
  assert(&nodes[9] == _rb_get_parent(&nodes[6]));
  assert(_rb_is_black(&nodes[6]));
  assert(nodes[2].rb_left == &nodes[7]);
  assert(&nodes[2] == _rb_get_parent(&nodes[7]));
  assert(_rb_is_black(&nodes[7]));
  assert(nodes[2].rb_right == &nodes[11]);
  assert(&nodes[2] == _rb_get_parent(&nodes[11]));
  assert(_rb_is_black(&nodes[11]));
  assert(nodes[7].rb_left == NULL);
  assert(nodes[7].rb_right == &nodes[8]);
  assert(&nodes[7] == _rb_get_parent(&nodes[8]));
  assert(_rb_is_red(&nodes[8]));
  assert(nodes[6].rb_left == &nodes[12]);
  assert(&nodes[6] == _rb_get_parent(&nodes[12]));
  assert(_rb_is_black(&nodes[12]));
}

void test_remove_2() {
  rb_node nodes[13];
  rb_node *root = NULL;

  /*
                 0B
              /      \
            1R        2B
          /    \     /  \
        3B      4B  5B  6B
       /  \    /  \
      7R  8B  9B  10B
     /  \
    11B 12B
  */
  _test_append_node(&nodes[0], NULL, &root, 1);
  _test_append_node(&nodes[1], &nodes[0], &nodes[0].rb_left, 0);
  _test_append_node(&nodes[2], &nodes[0], &nodes[0].rb_right, 1);
  _test_append_node(&nodes[3], &nodes[1], &nodes[1].rb_left, 1);
  _test_append_node(&nodes[4], &nodes[1], &nodes[1].rb_right, 1);
  _test_append_node(&nodes[5], &nodes[2], &nodes[2].rb_left, 1);
  _test_append_node(&nodes[6], &nodes[2], &nodes[2].rb_right, 1);
  _test_append_node(&nodes[7], &nodes[3], &nodes[3].rb_left, 0);
  _test_append_node(&nodes[8], &nodes[3], &nodes[3].rb_right, 1);
  _test_append_node(&nodes[9], &nodes[4], &nodes[4].rb_left, 1);
  _test_append_node(&nodes[10], &nodes[4], &nodes[4].rb_right, 1);
  _test_append_node(&nodes[11], &nodes[7], &nodes[7].rb_left, 1);
  _test_append_node(&nodes[12], &nodes[7], &nodes[7].rb_right, 1);

  /*
               10B
            /       \
          3B         2B
        /    \      /  \
      7R      1R   5B  6B
     /  \    /  \
    11B 12B 8B  4B
               /
              9R
  */
  rb_remove(&root, &nodes[0]);
  assert(root == &nodes[10]);
  assert(_rb_is_black(&nodes[10]));
  assert(nodes[10].rb_left == &nodes[3]);
  assert(&nodes[10] == _rb_get_parent(&nodes[3]));
  assert(_rb_is_black(&nodes[3]));
  assert(nodes[10].rb_right == &nodes[2]);
  assert(&nodes[10] == _rb_get_parent(&nodes[2]));
  assert(_rb_is_black(&nodes[2]));
  assert(nodes[3].rb_left == &nodes[7]);
  assert(&nodes[3] == _rb_get_parent(&nodes[7]));
  assert(_rb_is_red(&nodes[7]));
  assert(nodes[3].rb_right == &nodes[1]);
  assert(&nodes[3] == _rb_get_parent(&nodes[1]));
  assert(_rb_is_red(&nodes[1]));
  assert(nodes[1].rb_left == &nodes[8]);
  assert(&nodes[1] == _rb_get_parent(&nodes[8]));
  assert(_rb_is_black(&nodes[8]));
  assert(nodes[1].rb_right == &nodes[4]);
  assert(&nodes[1] == _rb_get_parent(&nodes[4]));
  assert(_rb_is_black(&nodes[4]));
  assert(nodes[4].rb_left == &nodes[9]);
  assert(&nodes[4] == _rb_get_parent(&nodes[9]));
  assert(_rb_is_red(&nodes[9]));
  assert(nodes[4].rb_right == NULL);
}

void test_remove_3() {
  rb_node nodes[11];
  rb_node *root = NULL;

  /*
           0B
        /      \
      1B        2R
     /  \     /    \
    3B  4B  5B      6B
           /  \    /  \
          7B  8B  9B  10B
  */
  _test_append_node(&nodes[0], NULL, &root, 1);
  _test_append_node(&nodes[1], &nodes[0], &nodes[0].rb_left, 1);
  _test_append_node(&nodes[2], &nodes[0], &nodes[0].rb_right, 0);
  _test_append_node(&nodes[3], &nodes[1], &nodes[1].rb_left, 1);
  _test_append_node(&nodes[4], &nodes[1], &nodes[1].rb_right, 1);
  _test_append_node(&nodes[5], &nodes[2], &nodes[2].rb_left, 1);
  _test_append_node(&nodes[6], &nodes[2], &nodes[2].rb_right, 1);
  _test_append_node(&nodes[7], &nodes[5], &nodes[5].rb_left, 1);
  _test_append_node(&nodes[8], &nodes[5], &nodes[5].rb_right, 1);
  _test_append_node(&nodes[9], &nodes[6], &nodes[6].rb_left, 1);
  _test_append_node(&nodes[10], &nodes[6], &nodes[6].rb_right, 1);

  /*
              2B
            /    \
          5B      6B
         /  \    /  \
        4R  8B  9B  10B
       /  \
      1B  7B
     /
    3R
  */
  rb_remove(&root, &nodes[0]);
  assert(root == &nodes[2]);
  assert(_rb_is_black(&nodes[2]));
  assert(nodes[2].rb_left == &nodes[5]);
  assert(&nodes[2] == _rb_get_parent(&nodes[5]));
  assert(_rb_is_black(&nodes[5]));
  assert(nodes[2].rb_right == &nodes[6]);
  assert(&nodes[2] == _rb_get_parent(&nodes[6]));
  assert(_rb_is_black(&nodes[6]));
  assert(nodes[5].rb_left == &nodes[4]);
  assert(&nodes[5] == _rb_get_parent(&nodes[4]));
  assert(_rb_is_red(&nodes[4]));
  assert(nodes[5].rb_right == &nodes[8]);
  assert(&nodes[5] == _rb_get_parent(&nodes[8]));
  assert(_rb_is_black(&nodes[8]));
  assert(nodes[6].rb_left == &nodes[9]);
  assert(&nodes[6] == _rb_get_parent(&nodes[9]));
  assert(_rb_is_black(&nodes[9]));
  assert(nodes[6].rb_right == &nodes[10]);
  assert(&nodes[6] == _rb_get_parent(&nodes[10]));
  assert(_rb_is_black(&nodes[10]));
  assert(nodes[4].rb_left == &nodes[1]);
  assert(&nodes[4] == _rb_get_parent(&nodes[1]));
  assert(_rb_is_black(&nodes[1]));
  assert(nodes[4].rb_right == &nodes[7]);
  assert(&nodes[4] == _rb_get_parent(&nodes[7]));
  assert(_rb_is_black(&nodes[7]));
  assert(nodes[1].rb_left == &nodes[3]);
  assert(&nodes[1] == _rb_get_parent(&nodes[3]));
  assert(_rb_is_red(&nodes[3]));
  assert(nodes[1].rb_right == NULL);
}

void test_remove_4() {
  rb_node nodes[17];
  rb_node *root = NULL;

  /*
                  0B
            /            \
          1B              2B
        /    \          /    \
      3B      4B      5B      6B
     /  \    /  \    /  \    /  \
    7B  8R  9B  10B 11B 12B 13B 14B
       /  \
      15B 16B
  */
  _test_append_node(&nodes[0], NULL, &root, 1);
  _test_append_node(&nodes[1], &nodes[0], &nodes[0].rb_left, 1);
  _test_append_node(&nodes[2], &nodes[0], &nodes[0].rb_right, 1);
  _test_append_node(&nodes[3], &nodes[1], &nodes[1].rb_left, 1);
  _test_append_node(&nodes[4], &nodes[1], &nodes[1].rb_right, 1);
  _test_append_node(&nodes[5], &nodes[2], &nodes[2].rb_left, 1);
  _test_append_node(&nodes[6], &nodes[2], &nodes[2].rb_right, 1);
  _test_append_node(&nodes[7], &nodes[3], &nodes[3].rb_left, 1);
  _test_append_node(&nodes[8], &nodes[3], &nodes[3].rb_right, 0);
  _test_append_node(&nodes[9], &nodes[4], &nodes[4].rb_left, 1);
  _test_append_node(&nodes[10], &nodes[4], &nodes[4].rb_right, 1);
  _test_append_node(&nodes[11], &nodes[5], &nodes[5].rb_left, 1);
  _test_append_node(&nodes[12], &nodes[5], &nodes[5].rb_right, 1);
  _test_append_node(&nodes[13], &nodes[6], &nodes[6].rb_left, 1);
  _test_append_node(&nodes[14], &nodes[6], &nodes[6].rb_right, 1);
  _test_append_node(&nodes[15], &nodes[8], &nodes[8].rb_left, 1);
  _test_append_node(&nodes[16], &nodes[8], &nodes[8].rb_right, 1);

  /*
                  10B
            /            \
          8B              2B
        /    \          /    \
      3B      1B      5B      6B
     /  \    /  \    /  \    /  \
    7B  15B 16B 4B  11B 12B 13B 14B
               /
              9R
  */
  rb_remove(&root, &nodes[0]);
  assert(root == &nodes[10]);
  assert(_rb_is_black(&nodes[10]));
  assert(nodes[10].rb_left == &nodes[8]);
  assert(&nodes[10] == _rb_get_parent(&nodes[8]));
  assert(_rb_is_black(&nodes[8]));
  assert(nodes[10].rb_right == &nodes[2]);
  assert(&nodes[10] == _rb_get_parent(&nodes[2]));
  assert(_rb_is_black(&nodes[2]));
  assert(nodes[8].rb_left == &nodes[3]);
  assert(&nodes[8] == _rb_get_parent(&nodes[3]));
  assert(_rb_is_black(&nodes[3]));
  assert(nodes[8].rb_right == &nodes[1]);
  assert(&nodes[8] == _rb_get_parent(&nodes[1]));
  assert(_rb_is_black(&nodes[1]));
  assert(nodes[3].rb_left == &nodes[7]);
  assert(&nodes[3] == _rb_get_parent(&nodes[7]));
  assert(_rb_is_black(&nodes[7]));
  assert(nodes[3].rb_right == &nodes[15]);
  assert(&nodes[3] == _rb_get_parent(&nodes[15]));
  assert(_rb_is_black(&nodes[15]));
  assert(nodes[1].rb_left == &nodes[16]);
  assert(&nodes[1] == _rb_get_parent(&nodes[16]));
  assert(_rb_is_black(&nodes[16]));
  assert(nodes[1].rb_right == &nodes[4]);
  assert(&nodes[1] == _rb_get_parent(&nodes[4]));
  assert(_rb_is_black(&nodes[4]));
  assert(nodes[4].rb_left == &nodes[9]);
  assert(&nodes[4] == _rb_get_parent(&nodes[9]));
  assert(_rb_is_red(&nodes[9]));
  assert(nodes[4].rb_right == NULL);
}

void test_remove_5() {
  rb_node nodes[17];
  rb_node *root = NULL;

  /*
                    0B
              /            \
            1B              2B
          /    \          /    \
        3B      4B      5B      6B
       /  \    /  \    /  \    /  \
      7R  8B  9B  10B 11B 12B 13B 14B
     /  \
    15B 16B
  */
  _test_append_node(&nodes[0], NULL, &root, 1);
  _test_append_node(&nodes[1], &nodes[0], &nodes[0].rb_left, 1);
  _test_append_node(&nodes[2], &nodes[0], &nodes[0].rb_right, 1);
  _test_append_node(&nodes[3], &nodes[1], &nodes[1].rb_left, 1);
  _test_append_node(&nodes[4], &nodes[1], &nodes[1].rb_right, 1);
  _test_append_node(&nodes[5], &nodes[2], &nodes[2].rb_left, 1);
  _test_append_node(&nodes[6], &nodes[2], &nodes[2].rb_right, 1);
  _test_append_node(&nodes[7], &nodes[3], &nodes[3].rb_left, 0);
  _test_append_node(&nodes[8], &nodes[3], &nodes[3].rb_right, 1);
  _test_append_node(&nodes[9], &nodes[4], &nodes[4].rb_left, 1);
  _test_append_node(&nodes[10], &nodes[4], &nodes[4].rb_right, 1);
  _test_append_node(&nodes[11], &nodes[5], &nodes[5].rb_left, 1);
  _test_append_node(&nodes[12], &nodes[5], &nodes[5].rb_right, 1);
  _test_append_node(&nodes[13], &nodes[6], &nodes[6].rb_left, 1);
  _test_append_node(&nodes[14], &nodes[6], &nodes[6].rb_right, 1);
  _test_append_node(&nodes[15], &nodes[7], &nodes[7].rb_left, 1);
  _test_append_node(&nodes[16], &nodes[7], &nodes[7].rb_right, 1);

  /*
                 10B
            /            \
          3B              2B
        /    \          /    \
      7B      1B      5B      6B
     /  \    /  \    /  \    /  \
    15B 16B 8B  4B  11B 12B 13B 14B
               /
              9R
  */
  rb_remove(&root, &nodes[0]);
  assert(root == &nodes[10]);
  assert(_rb_is_black(&nodes[10]));
  assert(nodes[10].rb_left == &nodes[3]);
  assert(&nodes[10] == _rb_get_parent(&nodes[3]));
  assert(_rb_is_black(&nodes[3]));
  assert(nodes[10].rb_right == &nodes[2]);
  assert(&nodes[10] == _rb_get_parent(&nodes[2]));
  assert(_rb_is_black(&nodes[2]));
  assert(nodes[3].rb_left == &nodes[7]);
  assert(&nodes[3] == _rb_get_parent(&nodes[7]));
  assert(_rb_is_black(&nodes[7]));
  assert(nodes[3].rb_right == &nodes[1]);
  assert(&nodes[3] == _rb_get_parent(&nodes[1]));
  assert(_rb_is_black(&nodes[1]));
  assert(nodes[7].rb_left == &nodes[15]);
  assert(&nodes[7] == _rb_get_parent(&nodes[15]));
  assert(_rb_is_black(&nodes[15]));
  assert(nodes[7].rb_right == &nodes[16]);
  assert(&nodes[7] == _rb_get_parent(&nodes[16]));
  assert(_rb_is_black(&nodes[16]));
  assert(nodes[1].rb_left == &nodes[8]);
  assert(&nodes[1] == _rb_get_parent(&nodes[8]));
  assert(_rb_is_black(&nodes[8]));
  assert(nodes[1].rb_right == &nodes[4]);
  assert(&nodes[1] == _rb_get_parent(&nodes[4]));
  assert(_rb_is_black(&nodes[4]));
  assert(nodes[4].rb_left == &nodes[9]);
  assert(&nodes[4] == _rb_get_parent(&nodes[9]));
  assert(_rb_is_red(&nodes[9]));
  assert(nodes[4].rb_right == NULL);
}

void test() {
  test_root();
  test_insert_0();
  test_insert_1();
  test_insert_2();
  test_remove_0();
  test_remove_1();
  test_remove_2();
  test_remove_3();
  test_remove_4();
  test_remove_5();
}

int main() {
  test();
  return 0;
}
