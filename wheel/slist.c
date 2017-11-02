#include <string.h>
#include "slist.h"
#include "memory.h"

extern slist *
slist_new (const void *data, size_t _size)
{
  slist *lst = alloc_func (sizeof (slist));
  lst->data = alloc_func (_size);
  memcpy (lst->data, data, _size);
  lst->next = NULL;
  return lst;
}

extern void
slist_free (slist *lst)
{
  while (lst)
    {
      slist *tmp = lst->next;
      free_func (lst->data);
      free_func (lst);
      lst = tmp;
    }
}

/* Return node before the old lst->next.  */
extern slist *
slist_insert_after (slist *lst, const void *data, size_t n, size_t _size)
{
  slist *tmp = lst->next;
  while (n--)
    {
      lst->next = slist_new (data, _size);
      lst = lst->next;
      data = (char *) data + _size;
    }
  lst->next = tmp;
  return lst;
}

/* Return the first node that is not removed.  */
extern slist *
slist_remove (slist *lst, size_t n)
{
  slist *tmp;
  while (n--)
    {
      tmp = lst->next;
      free_func (lst->data);
      free_func (lst);
      lst = tmp;
    }
  return lst;
}

extern slist *
slist_at (const slist *lst, size_t n)
{
  while (n--) lst = lst->next;
  return (slist *) lst;
}

/* Return the reverse nth node in O(n).  */
extern slist *
slist_at_r (const slist *lst, size_t n)
{
  const slist *node = lst;
  while (n--) node = node->next;
  while (node)
    {
      lst = lst->next;
      node = node->next;
    }
  return (slist *) lst;
}

/* O(n) */
extern slist *
slist_first_common_node (const slist *lst1, const slist *lst2)
{
  size_t len1 = 0, len2 = 0;
  const slist *ptr = lst1;
  while (ptr) { len1++; ptr = ptr->next; }
  ptr = lst2;
  while (ptr) { len2++; ptr = ptr->next; }
  if (len1 < len2)
    {
      size_t k = len2 - len1;
      while (k--) lst2 = lst2->next;
    }
  else
    {
      size_t k = len1 - len2;
      while (k--) lst1 = lst1->next;
    }
  while (lst1 != lst2) { lst1 = lst1->next; lst2 = lst2->next; }
  return (slist *) lst1;
}

/* O(n) */
extern int
slist_have_cycle_p (const slist *lst)
{
  const slist *tortoise = lst, *hare = lst->next;
  while (1)
    {
      if (hare == tortoise) return 1;
      if (hare == NULL
          || hare->next == NULL
          || hare->next->next == NULL)
        return 0;
      hare = hare->next->next;
      tortoise = tortoise->next;
    }
}
