#include <stdio.h>
#include "graph.h"

static graph *
make_graph00 ()
{
  int w;
  graph *G = graph_new (0, 3, sizeof (int));
  graph_insert_node (G, "V0");
  graph_insert_node (G, "V1");
  graph_insert_node (G, "V2");
  graph_insert_node (G, "V3");
  graph_insert_node (G, "V4");
  graph_insert_node (G, "V5");
  graph_insert_node (G, "V6");
  w = 0; graph_insert_edge (G, 0, 1, &w);
  w = 0; graph_insert_edge (G, 0, 2, &w);
  w = 6; graph_insert_edge (G, 1, 2, &w);
  w = 1; graph_insert_edge (G, 1, 3, &w);
  w = 5; graph_insert_edge (G, 1, 4, &w);
  w = 0; graph_insert_edge (G, 1, 5, &w);
  w = 0; graph_insert_edge (G, 0, 3, &w);
  w = 5; graph_insert_edge (G, 2, 3, &w);
  w = 3; graph_insert_edge (G, 2, 5, &w);
  graph_remove_edge (G, 5, 1);
  w = 5; graph_insert_edge (G, 3, 4, &w);
  w = 6; graph_insert_edge (G, 3, 5, &w);
  w = 4; graph_insert_edge (G, 3, 6, &w);
  w = 2; graph_insert_edge (G, 4, 6, &w);
  w = 6; graph_insert_edge (G, 5, 6, &w);
  graph_remove_node (G, 0);
  return G;
}

int
main ()
{
  graph *G = make_graph00 ();
  graph_free (G);
  return 0;
}
