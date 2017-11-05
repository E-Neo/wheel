#include <stdio.h>
#include "digraph.h"
#include "vector.h"

static digraph *
make_digraph ()
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
  return G;
}

static void
visit (void *data, void *arg)
{
  vector *vec = arg;
  vector_insert (vec, vec->len, data, 1);
}

static void
print_vector (const vector *vec)
{
  if (vec->len == 0)
    printf ("{}");
  else
    {
      char *p = vec->data;
      size_t len = vec->len, _size = vec->_size;
      printf ("{");
      while (--len)
        {
          printf (" %s,", p);
          p += _size;
        }
      printf (" %s }", p);
    }
}

int
main ()
{
  digraph *G = make_digraph ();
  vector *vec = vector_new (G->_node_size);
  digraph_bfs (G, 0, visit, vec); /* SACDEBFG */
  printf ("expect { S, A, C, D, E, B, F, G }:\n");
  print_vector (vec); printf ("\n");
  vec->len = 0;
  digraph_dfs_preorder (G, 0, visit, vec);
  printf ("expect { S, D, B, C, A, E, G, F }: \n");
  print_vector (vec); printf ("\n");
  vector_free (vec);
  digraph_free (G);
  return 0;
}
