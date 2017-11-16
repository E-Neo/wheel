#include <stdio.h>
#include "binary_tree.h"
#include "vector.h"

static void
print_vector (const vector *vec)
{
  if (vec->len == 0) { puts ("[]"); return; }
  printf ("[");
  size_t i;
  for (i = 0; i < vec->len - 1; i++)
    printf ("%s, ", (char *) vector_at (vec, i));
  printf ("%s]\n", (char *) vector_at (vec, i));
}

static binary_tree *
make_test_binary_tree ()
{
  binary_tree *T = binary_tree_new (2);
  binary_tree_insert (T, T->root, 0, "i");
  binary_tree_insert (T, T->root, 0, "d");
  binary_tree_insert (T, T->root, 1, "l");
  binary_tree_insert (T, T->root->lc, 0, "c");
  binary_tree_insert (T, T->root->lc, 1, "h");
  binary_tree_insert (T, T->root->rc, 0, "k");
  binary_tree_insert (T, T->root->rc, 1, "n");
  binary_tree_insert (T, T->root->lc->lc, 0, "a");
  binary_tree_insert (T, T->root->lc->rc, 0, "f");
  binary_tree_insert (T, T->root->rc->lc, 0, "j");
  binary_tree_insert (T, T->root->rc->rc, 0, "m");
  binary_tree_insert (T, T->root->rc->rc, 1, "p");
  binary_tree_insert (T, T->root->lc->lc->lc, 1, "b");
  binary_tree_insert (T, T->root->lc->rc->lc, 0, "e");
  binary_tree_insert (T, T->root->lc->rc->lc, 1, "g");
  binary_tree_insert (T, T->root->rc->rc->rc, 0, "o");
  return T;
}

static binary_tree *
make_complete_binary_tree ()
{
  binary_tree *T = binary_tree_new (2);
  binary_tree_insert (T, T->root, 0, "1");
  binary_tree_insert (T, T->root, 0, "2");
  binary_tree_insert (T, T->root, 1, "3");
  binary_tree_insert (T, T->root->lc, 0, "4");
  return T;
}

static void
visit (void *data, void *arg)
{
  vector *vec = arg;
  vector_insert (vec, vec->len, data, 1);
}

int
main ()
{
  binary_tree *T = make_test_binary_tree ();
  binary_tree *complete_T = make_complete_binary_tree ();
  vector *vec = vector_new (2);

  printf ("height, expect 5: %zu\n", binary_tree_height (T));
  printf ("width, expect 5: %zu\n", binary_tree_width (T));
  printf ("complete_p, expect 0: %d\n", binary_tree_complete_p (T));
  printf ("complete_p, expect 1: %d\n", binary_tree_complete_p (complete_T));
  puts ("");

  puts ("expect");
  puts ("[i, d, l, c, h, k, n, a, f, j, m, p, b, e, g, o]");
  vec->len = 0;
  puts ("bfs");
  binary_tree_bfs (T, visit, vec);
  print_vector (vec);
  vec->len = 0;
  puts ("bfs_next");
  for (bin_node *posi = binary_tree_bfs_front (T);
       posi != NULL;
       posi = binary_tree_bfs_next (T, posi))
    vector_insert (vec, vec->len, posi->data, 1);
  print_vector (vec);
  vec->len = 0;
  puts ("bfs_prev");
  for (bin_node *posi = binary_tree_bfs_back (T);
       posi != NULL;
       posi = binary_tree_bfs_prev (T, posi))
    vector_insert (vec, vec->len, posi->data, 1);
  vector_reverse (vec, 0, vec->len);
  print_vector (vec);
  puts ("");

  puts ("expect");
  puts ("[i, d, c, a, b, h, f, e, g, l, k, j, n, m, p, o]");
  vec->len = 0;
  puts ("dfs_preorder");
  binary_tree_dfs_preorder (T, visit, vec);
  print_vector (vec);
  vec->len = 0;
  puts ("dfs_preorder_next");
  for (bin_node *posi = binary_tree_dfs_preorder_front (T);
       posi != NULL;
       posi = binary_tree_dfs_preorder_next (T, posi))
    vector_insert (vec, vec->len, posi->data, 1);
  print_vector (vec);
  vec->len = 0;
  puts ("dfs_preorder_prev");
  for (bin_node *posi = binary_tree_dfs_preorder_back (T);
       posi != NULL;
       posi = binary_tree_dfs_preorder_prev (T, posi))
    vector_insert (vec, vec->len, posi->data, 1);
  vector_reverse (vec, 0, vec->len);
  print_vector (vec);
  puts ("");

  puts ("expect");
  puts ("[a, b, e, d, e, f, g, h, i, j, k, l, m, n, o, p]");
  vec->len = 0;
  puts ("dfs_inorder");
  binary_tree_dfs_inorder (T, visit, vec);
  print_vector (vec);
  vec->len = 0;
  puts ("dfs_inorder_next");
  for (bin_node *posi = binary_tree_dfs_inorder_front (T);
       posi != NULL;
       posi = binary_tree_dfs_inorder_next (T, posi))
    vector_insert (vec, vec->len, posi->data, 1);
  print_vector (vec);
  vec->len = 0;
  puts ("dfs_inorder_prev");
  for (bin_node *posi = binary_tree_dfs_inorder_back (T);
       posi != NULL;
       posi = binary_tree_dfs_inorder_prev (T, posi))
    vector_insert (vec, vec->len, posi->data, 1);
  vector_reverse (vec, 0, vec->len);
  print_vector (vec);
  puts ("");

  puts ("expect");
  puts ("[b, a, c, e, g, f, h, d, j, k, m, o, p, n, l, i]");
  vec->len = 0;
  puts ("dfs_postorder");
  binary_tree_dfs_postorder (T, visit, vec);
  print_vector (vec);
  vec->len = 0;
  puts ("dfs_postorder_next");
  for (bin_node *posi = binary_tree_dfs_postorder_front (T);
       posi != NULL;
       posi = binary_tree_dfs_postorder_next (T, posi))
    vector_insert (vec, vec->len, posi->data, 1);
  print_vector (vec);
  vec->len = 0;
  puts ("dfs_postorder_prev");
  for (bin_node *posi = binary_tree_dfs_postorder_back (T);
       posi != NULL;
       posi = binary_tree_dfs_postorder_prev (T, posi))
    vector_insert (vec, vec->len, posi->data, 1);
  vector_reverse (vec, 0, vec->len);
  print_vector (vec);

  vector_free (vec);
  binary_tree_free (T);
  binary_tree_free (complete_T);
  return 0;
}
