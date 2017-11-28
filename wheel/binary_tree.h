#ifndef _BINARY_TREE_H
#define _BINARY_TREE_H

#include <stddef.h>

typedef struct bin_node bin_node;
typedef struct binary_tree binary_tree;

struct bin_node
{
  void *data;
  struct bin_node *parent, *lc, *rc;
};

struct binary_tree
{
  struct bin_node *root;
  size_t n;
  size_t _size;
};

extern binary_tree *binary_tree_new (size_t _size);
extern void binary_tree_free (binary_tree *T);
/* Return number of levels of T.   */
extern size_t binary_tree_height (const binary_tree *T);
extern size_t binary_tree_width (const binary_tree *T);
extern int binary_tree_complete_p (const binary_tree *T);
extern int binary_tree_bst_p (const binary_tree *T,
                              int (*compar) (const void *, const void *));
extern void binary_tree_insert (binary_tree *T, bin_node *parent, int rc,
                                const void *data);
extern void binary_tree_remove (binary_tree *T, bin_node *posi);
extern void binary_tree_bfs (binary_tree *T,
                             void (*visit) (void *, void *),
                             void *arg);
extern void binary_tree_dfs_preorder (binary_tree *T,
                                      void (*visit) (void *, void *),
                                      void *arg);
extern void binary_tree_dfs_inorder (binary_tree *T,
                                     void (*visit) (void *, void *),
                                     void *arg);
extern void binary_tree_dfs_postorder (binary_tree *T,
                                       void (*visit) (void *, void *),
                                       void *arg);
extern bin_node *binary_tree_bfs_front (const binary_tree *T);
extern bin_node *binary_tree_bfs_back (const binary_tree *T);
extern bin_node *binary_tree_bfs_next (const binary_tree *T,
                                       const bin_node *posi);
extern bin_node *binary_tree_bfs_prev (const binary_tree *T,
                                       const bin_node *posi);
extern bin_node *binary_tree_dfs_preorder_front (const binary_tree *T);
extern bin_node *binary_tree_dfs_preorder_back (const binary_tree *T);
extern bin_node *binary_tree_dfs_preorder_next (const binary_tree *T,
                                                const bin_node *posi);
extern bin_node *binary_tree_dfs_preorder_prev (const binary_tree *T,
                                                const bin_node *posi);
extern bin_node *binary_tree_dfs_inorder_front (const binary_tree *T);
extern bin_node *binary_tree_dfs_inorder_back (const binary_tree *T);
extern bin_node *binary_tree_dfs_inorder_next (const binary_tree *T,
                                               const bin_node *posi);
extern bin_node *binary_tree_dfs_inorder_prev (const binary_tree *T,
                                               const bin_node *posi);
extern bin_node *binary_tree_dfs_postorder_front (const binary_tree *T);
extern bin_node *binary_tree_dfs_postorder_back (const binary_tree *T);
extern bin_node *binary_tree_dfs_postorder_next (const binary_tree *T,
                                                 const bin_node *posi);
extern bin_node *binary_tree_dfs_postorder_prev (const binary_tree *T,
                                                 const bin_node *posi);

#endif
