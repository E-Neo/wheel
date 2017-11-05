#ifndef _AVL_TREE_H
#define _AVL_TREE_H

#include <stddef.h>

typedef struct avl_tree avl_tree;

struct avl_tree
{
  struct avl_node *root, *null;
  size_t n;
  size_t _size;
  int (*compar) (const void *, const void *);
};

extern avl_tree *avl_tree_new (size_t _size,
                               int (*compar) (const void *, const void *));
extern void avl_tree_free (avl_tree *T);
extern void *avl_tree_search (const avl_tree *T, const void *key);

#endif
