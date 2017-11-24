#include <stdio.h>
#include "graph.h"

static graph *
make_graph00 ()
{
  int w;
  graph *G = graph_new (0, 3, sizeof (int));
  graph_node v0 = graph_insert_node (G, "V0");
  graph_node v1 = graph_insert_node (G, "V1");
  graph_node v2 = graph_insert_node (G, "V2");
  graph_node v3 = graph_insert_node (G, "V3");
  graph_node v4 = graph_insert_node (G, "V4");
  graph_node v5 = graph_insert_node (G, "V5");
  graph_node v6 = graph_insert_node (G, "V6");
  w = 0; graph_insert_edge (G, v0, v1, &w);
  w = 0; graph_insert_edge (G, v0, v2, &w);
  w = 6; graph_insert_edge (G, v1, v2, &w);
  w = 1; graph_insert_edge (G, v1, v3, &w);
  w = 5; graph_insert_edge (G, v1, v4, &w);
  w = 0; graph_insert_edge (G, v1, v5, &w);
  w = 0; graph_insert_edge (G, v0, v3, &w);
  w = 5; graph_insert_edge (G, v2, v3, &w);
  w = 3; graph_insert_edge (G, v2, v5, &w);
  graph_remove_edge (G, v5, v1);
  w = 5; graph_insert_edge (G, v3, v4, &w);
  w = 6; graph_insert_edge (G, v3, v5, &w);
  w = 4; graph_insert_edge (G, v3, v6, &w);
  w = 2; graph_insert_edge (G, v4, v6, &w);
  w = 6; graph_insert_edge (G, v5, v6, &w);
  graph_remove_node (G, v0);
  return G;
}

int
main ()
{
  graph *G = make_graph00 ();
  graph_free (G);
  return 0;
}
