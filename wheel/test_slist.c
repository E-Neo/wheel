#include <stdio.h>
#include "slist.h"

static void
make_intersect_slists (slist **lst1_ref, slist **lst2_ref)
{
  /* lst1 = { 0, 1, 2,    7, 8, 9 }
     lst2 = { 3, 4, 5, 6, 7, 8, 9 }  */
  int array[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
  slist *lst1 = slist_new (array + 0, sizeof (int));
  slist *lst2 = slist_new (array + 3, sizeof (int));
  slist *common = slist_new (array + 7, sizeof (int));
  slist *tmp;
  slist_insert_after (common, array + 8, 2, sizeof (int));
  tmp = slist_insert_after (lst1, array + 1, 2, sizeof (int));
  tmp->next = common;
  tmp = slist_insert_after (lst2, array + 4, 3, sizeof (int));
  tmp->next = common;
  *lst1_ref = lst1; *lst2_ref = lst2;
}

static slist *
make_slist_with_cycle ()
{
  int array[] = { 0, 1, 2, 3, 4, 5, 6 };
  slist *lst = slist_new (array, sizeof (int));
  slist *cycle = slist_insert_after (lst, array + 1, 3, sizeof (int));
  slist *back = slist_insert_after (cycle, array + 4, 3, sizeof (int));
  back->next = cycle;
  return lst;
}

static void
print_slist (const slist *lst)
{
  if (lst == NULL) puts ("{}");
  printf ("{");
  while (lst->next)
    {
      printf (" %d,", *(int *) lst->data);
      lst = lst->next;
    }
  printf (" %d }\n", *(int *) lst->data);
}

int
main ()
{
  slist *lst1, *lst2, *tmp;
  make_intersect_slists (&lst1, &lst2);
  print_slist (lst1);
  print_slist (lst2);
  tmp = slist_first_common_node (lst1, lst2);
  printf ("expected 7: %d\n", *(int *) tmp->data);
  tmp = slist_at (lst2, 2);
  printf ("expected 5: %d\n", *(int *) tmp->data);
  tmp = slist_at_r (lst2, 4);
  printf ("expected 6: %d\n", *(int *) tmp->data);
  slist *lst = make_slist_with_cycle ();
  printf ("expected 0 1: %d %d\n",
          slist_have_cycle_p (lst1),
          slist_have_cycle_p (lst));
  slist_remove (lst1, 6); slist_remove (lst2, 4);
  slist_remove (lst, 7);
}
