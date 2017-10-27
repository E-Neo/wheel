#include <stdio.h>
#include "list.h"

int
main ()
{
  int a[] = {1, 2, 3, 4};
  list *lst = list_new (sizeof (int));
  list_insert (lst, lst->tail, a, 1);
  list_insert (lst, lst->head->next, a, 4);
  list_remove (lst, lst->head->next, 0);
  list_remove (lst, lst->head->next, 2);
  for (size_t i = 0; i < lst->len; i++)
    {
      list_node *node = list_at (lst, i);
      int *t = node->data;
      printf ("%d\n", *t);
    }
  list_free (lst);
  return 0;
}
