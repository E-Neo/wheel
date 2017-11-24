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

#endif
