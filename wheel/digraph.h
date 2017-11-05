#ifndef _DIGRAPH_H
#define _DIGRAPH_H

#include <stddef.h>
#include "vector.h"

typedef struct digraph digraph;

struct digraph
{
  void *data;
  size_t n, e;
  vector *node;
  vector *succ;
  size_t _size, _node_size, _edge_size;
};

extern digraph *digraph_new (size_t _size, size_t _node_size,
                             size_t _edge_size);
extern void digraph_free (digraph *G);
extern void digraph_insert_node (digraph *G, const void *base);
extern void digraph_insert_edge (digraph *G, size_t u, size_t v,
                                 const void *base);
extern void digraph_remove_node (digraph *G, size_t n);
extern void digraph_remove_edge (digraph *G, size_t u, size_t v);
extern void *digraph_at_node (digraph *G, size_t n);
extern void *digraph_at_edge (digraph *G, size_t u, size_t v);
extern void digraph_bfs (digraph *G, size_t s,
                         void (*visit) (void *, void *), void *arg);
extern void digraph_dfs_preorder (digraph *G, size_t s,
                                  void (*visit) (void *, void *), void *arg);

#endif
