#include <stdio.h>
#include "list.h"

static list *
make_list ()
{
  int a[] = {3, 1, 4, 1, 5, 9, 2, 6, 5};
  list *lst = list_new (sizeof (int));
  list_insert (lst, lst->tail, a, sizeof (a) / sizeof (int));
  return lst;
}

static void
print_list (const list *lst)
{
  list_foreach (lst, node, lst->head->next, lst->tail)
    printf (" %d", *(int *) node->data);
}

static int
compar (const void *a, const void *b)
{
  return *(int *) a - *(int *) b;
}

int
main ()
{
  list *lst = make_list ();

  puts ("search");
  int x = 5;
  puts ("expect: 5");
  printf ("result: %d\n",
          *(int *)(list_search (lst, lst->head->next, lst->tail,
                                &x, compar))->data);
  puts ("expect: NULL");
  x = 0;
  printf ("result: %s\n",
          list_search (lst, lst->head->next, lst->tail, &x, compar)
          ? "ERROR"
          : "NULL");
  puts ("");

  puts ("insertion_sort");
  puts ("expect: 1 1 2 3 4 5 5 6 9");
  printf ("result:");
  list_insertion_sort (lst, lst->head->next, lst->tail, compar);
  print_list (lst);
  puts ("");
  list_free (lst);
  return 0;
}
