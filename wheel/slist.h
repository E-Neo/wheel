#ifndef _SLIST_H
#define _SLIST_H

#include <stddef.h>

typedef struct slist slist;

struct slist
{
  void *data;
  slist *next;
};

extern slist *slist_new (const void *data, size_t _size);
extern void slist_free (slist *lst);
/* Return node before the old lst->next.  */
extern slist *slist_insert_after (slist *lst, const void *data, size_t n,
                                  size_t _size);
/* Return the first node that is not removed.  */
extern slist *slist_remove (slist *lst, size_t n);
extern slist *slist_at (const slist *lst, size_t n);
/* Return the reverse nth node.  */
extern slist *slist_at_r (const slist *lst, size_t n);
extern slist *slist_first_common_node (const slist *lst1, const slist *lst2);
extern int slist_have_cycle_p (const slist *lst);
extern size_t slist_cycle_length (const slist *lst);
extern slist *slist_cycle_front (const slist *lst);

#endif
