#include <stdio.h>
#include "binary_tree.h"
#include "stack.h"
#include "memory.h"

bin_node *
make_test_bin_node ()
{
  char *data_array[16];
  bin_node *node_array[16];
  for (size_t i = 0; i < 16; i++)
    {
      data_array[i] = alloc_func (2);
      data_array[i][0] = 'a' + i;
      data_array[i][1] = '\0';
      node_array[i] = bin_node_new (data_array[i], NULL, NULL, NULL);
    }
  node_array['a' - 'a']->parent = node_array['c' - 'a'];
  node_array['a' - 'a']->rc = node_array['b' - 'a'];
  node_array['b' - 'a']->parent = node_array['a' - 'a'];
  node_array['c' - 'a']->parent = node_array['d' - 'a'];
  node_array['c' - 'a']->lc = node_array['a' - 'a'];
  node_array['d' - 'a']->parent = node_array['i' - 'a'];
  node_array['d' - 'a']->lc = node_array['c' - 'a'];
  node_array['d' - 'a']->rc = node_array['h' - 'a'];
  node_array['e' - 'a']->parent = node_array['f' - 'a'];
  node_array['f' - 'a']->parent = node_array['h' - 'a'];
  node_array['f' - 'a']->lc = node_array['e' - 'a'];
  node_array['f' - 'a']->rc = node_array['g' - 'a'];
  node_array['g' - 'a']->parent = node_array['f' - 'a'];
  node_array['h' - 'a']->parent = node_array['d' - 'a'];
  node_array['h' - 'a']->lc = node_array['f' - 'a'];
  node_array['i' - 'a']->lc = node_array['d' - 'a'];
  node_array['i' - 'a']->rc = node_array['l' - 'a'];
  node_array['j' - 'a']->parent = node_array['k' - 'a'];
  node_array['k' - 'a']->parent = node_array['l' - 'a'];
  node_array['k' - 'a']->lc = node_array['j' - 'a'];
  node_array['l' - 'a']->parent = node_array['i' - 'a'];
  node_array['l' - 'a']->lc = node_array['k' - 'a'];
  node_array['l' - 'a']->rc = node_array['n' - 'a'];
  node_array['m' - 'a']->parent = node_array['n' - 'a'];
  node_array['n' - 'a']->parent = node_array['l' - 'a'];
  node_array['n' - 'a']->lc = node_array['m' - 'a'];
  node_array['n' - 'a']->rc = node_array['p' - 'a'];
  node_array['o' - 'a']->parent = node_array['p' - 'a'];
  node_array['p' - 'a']->parent = node_array['n' - 'a'];
  node_array['p' - 'a']->lc = node_array['o' - 'a'];
  return node_array['i' - 'a'];
}

int
visit_bfs (bin_node *node)
{
  printf ("%s\n", (char *) node->data);
  return 1;
}

void
dfs_preorder_print_front_back (bin_node *node)
{
  bin_node *front = bin_node_dfs_preorder_front (node);
  bin_node *back = bin_node_dfs_preorder_back (node);
  char *front_data = front ? front->data : "NULL";
  char *back_data = back ? back->data : "NULL";
  printf ("%s %s\n", front_data, back_data);
}

int
visit_dfs_preorder_print_data (bin_node *node)
{
  bin_node *prev = bin_node_dfs_preorder_prev (node);
  bin_node *next = bin_node_dfs_preorder_next (node);
  char *prev_data = prev ? prev->data : "NULL";
  char *next_data = next ? next->data : "NULL";
  printf ("%s -> %s -> %s\n", prev_data, (char *) node->data, next_data);
  return 1;
}

void
dfs_inorder_print_front_back (bin_node *node)
{
  bin_node *front = bin_node_dfs_inorder_front (node);
  bin_node *back = bin_node_dfs_inorder_back (node);
  char *front_data = front ? front->data : "NULL";
  char *back_data = back ? back->data : "NULL";
  printf ("%s %s\n", front_data, back_data);
}

int
visit_dfs_inorder_print_data (bin_node *node)
{
  bin_node *prev = bin_node_dfs_inorder_prev (node);
  bin_node *next = bin_node_dfs_inorder_next (node);
  char *prev_data = prev ? prev->data : "NULL";
  char *next_data = next ? next->data : "NULL";
  printf ("%s -> %s -> %s\n", prev_data, (char *) node->data, next_data);
  return 1;
}

void
dfs_postorder_print_front_back (bin_node *node)
{
  bin_node *front = bin_node_dfs_postorder_front (node);
  bin_node *back = bin_node_dfs_postorder_back (node);
  char *front_data = front ? front->data : "NULL";
  char *back_data = back ? back->data : "NULL";
  printf ("%s %s\n", front_data, back_data);
}

int
visit_dfs_postorder_print_data (bin_node *node)
{
  bin_node *prev = bin_node_dfs_postorder_prev (node);
  bin_node *next = bin_node_dfs_postorder_next (node);
  char *prev_data = prev ? prev->data : "NULL";
  char *next_data = next ? next->data : "NULL";
  printf ("%s -> %s -> %s\n", prev_data, (char *) node->data, next_data);
  return 1;
}

int
main ()
{
  bin_node *root = make_test_bin_node ();
  puts ("bfs:");
  bin_node_bfs (root, visit_bfs);
  puts ("\ndfs_preorder:");
  dfs_preorder_print_front_back (root);
  bin_node_dfs_preorder (root, visit_dfs_preorder_print_data);
  puts ("\ndfs_inorder:");
  dfs_inorder_print_front_back (root);
  bin_node_dfs_inorder (root, visit_dfs_inorder_print_data);
  puts ("\ndfs_postorder:");
  dfs_postorder_print_front_back (root);
  bin_node_dfs_postorder (root, visit_dfs_postorder_print_data);
  bin_node_free (root);
  return 0;
}
