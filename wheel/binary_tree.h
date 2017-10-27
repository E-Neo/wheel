#ifndef _BINARY_TREE_H
#define _BINARY_TREE_H

#include <stddef.h>

typedef struct bin_node bin_node;

struct bin_node
{
  void *data;
  struct bin_node *parent, *lc, *rc;
};

/* In the following functions, the parameter node cannot be NULL.  */
extern bin_node *bin_node_new (const void *data, const bin_node *parent,
                               const bin_node *lc, const bin_node *rc);
extern void bin_node_free (bin_node *node);
extern bin_node *bin_node_bfs (bin_node *node, int (*visit) (bin_node *));
extern bin_node *bin_node_dfs_preorder (bin_node *node,
                                        int (*visit) (bin_node *));
extern bin_node *bin_node_dfs_inorder (bin_node *node,
                                       int (*visit) (bin_node *));
extern bin_node *bin_node_dfs_postorder (bin_node *node,
                                         int (*visit) (bin_node *));
extern bin_node *bin_node_bfs_front (const bin_node *node);
extern bin_node *bin_node_bfs_back (const bin_node *node);
extern bin_node *bin_node_bfs_next (const bin_node *node);
extern bin_node *bin_node_bfs_prev (const bin_node *node);
extern bin_node *bin_node_dfs_preorder_front (const bin_node *node);
extern bin_node *bin_node_dfs_preorder_back (const bin_node *node);
extern bin_node *bin_node_dfs_preorder_next (const bin_node *node);
extern bin_node *bin_node_dfs_preorder_prev (const bin_node *node);
extern bin_node *bin_node_dfs_inorder_front (const bin_node *node);
extern bin_node *bin_node_dfs_inorder_back (const bin_node *node);
extern bin_node *bin_node_dfs_inorder_next (const bin_node *node);
extern bin_node *bin_node_dfs_inorder_prev (const bin_node *node);
extern bin_node *bin_node_dfs_postorder_front (const bin_node *node);
extern bin_node *bin_node_dfs_postorder_back (const bin_node *node);
extern bin_node *bin_node_dfs_postorder_next (const bin_node *node);
extern bin_node *bin_node_dfs_postorder_prev (const bin_node *node);

#endif
