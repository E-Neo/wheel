#ifndef _GRAPH_H
#define _GRAPH_H

#include <stddef.h>

typedef struct graph graph;
typedef size_t graph_node;

struct graph
{
  void *data;
  size_t n, e;
  struct _internal *_internal;
  size_t _size, _node_size, _edge_size;
};

extern graph *graph_new (size_t _size, size_t _node_size, size_t _edge_size);
extern void graph_free (graph *G);
extern int graph_have_node_p (const graph *G, graph_node node);
extern int graph_have_edge_p (const graph *G, graph_node u, graph_node v);
extern void *graph_at_node (const graph *G, graph_node node);
extern void *graph_at_edge (const graph *G, graph_node u, graph_node v);
extern graph_node graph_insert_node (graph *G, const void *data);
extern void graph_insert_edge (graph *G, graph_node u, graph_node v,
                               const void *data);
extern void graph_remove_node (graph *G, graph_node node);
extern void graph_remove_edge (graph *G, graph_node u, graph_node v);
extern const void *graph_node_next (const graph *G,
                                    const void *idx, graph_node *node);
#define graph_node_foreach(G, node)                                     \
  for (graph_node node, keep = 1; keep;)                                \
    for (const void *idx = graph_node_next (G, NULL, &node);            \
         idx;                                                           \
         idx = graph_node_next (G, idx, &node), keep = idx != NULL)
extern const void *graph_node_nbr_next (const graph *G, graph_node node,
                                        const void *idx, graph_node *nbr);
#define graph_node_nbr_foreach(G, node, nbr)                            \
  for (graph_node nbr, keep = 1; keep;)                                 \
    for (const void *idx = graph_node_nbr_next (G, node, NULL, &nbr);   \
         idx;                                                           \
         idx = graph_node_nbr_next (G, node, idx, &nbr), keep = idx != NULL)
extern void graph_bfs (graph *G, graph_node s,
                       void (*visit) (graph_node, void *, void *), void *arg);
extern void graph_dfs_preorder (graph *G, graph_node s,
                                void (*visit) (graph_node, void *, void *),
                                void *arg);

#endif
