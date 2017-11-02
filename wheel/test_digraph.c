#include <stdio.h>
#include "digraph.h"

static void
visit (void *data)
{
  puts ((char *) data);
}

int
main ()
{
  digraph *G = digraph_new (0, 2, 3);
  digraph_insert_node (G, "S"); /* 0 */
  digraph_insert_node (G, "A"); /* 1 */
  digraph_insert_node (G, "B"); /* 2 */
  digraph_insert_node (G, "C"); /* 3 */
  digraph_insert_node (G, "X");
  digraph_insert_edge (G, 0, 4, "SX");
  digraph_insert_edge (G, 4, 1, "XA");
  digraph_insert_node (G, "D"); /* 4 */
  digraph_insert_node (G, "E"); /* 5 */
  digraph_insert_node (G, "F"); /* 6 */
  digraph_insert_node (G, "G"); /* 7 */
  digraph_remove_node (G, 4);
  digraph_insert_edge (G, 0, 4, "SD");
  digraph_insert_edge (G, 0, 3, "SC");
  digraph_insert_edge (G, 0, 1, "SA");
  digraph_insert_edge (G, 1, 5, "AE");
  digraph_insert_edge (G, 1, 3, "AC");
  digraph_insert_edge (G, 3, 2, "CB");
  digraph_insert_edge (G, 4, 2, "DB");
  digraph_insert_edge (G, 5, 7, "EG");
  digraph_insert_edge (G, 5, 6, "EF");
  digraph_insert_edge (G, 7, 6, "GF");
  digraph_insert_edge (G, 7, 2, "GB");
  digraph_bfs (G, 0, visit); /* SACDEBFG */
  digraph_free (G);
  return 0;
}
