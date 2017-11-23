#ifndef _LIST_H
#define _LIST_H

#include <stddef.h>

typedef struct list_node list_node;
typedef struct list list;

struct list_node
{
  void *data;
  list_node *prev, *next;
};

struct list
{
  list_node *head, *tail;
  size_t len;
  size_t _size;
};

extern list *list_new (size_t _size);
extern void list_free (list *lst);
extern list_node *list_insert (list *lst, list_node *posi,
                               const void *base, size_t n);
extern list_node *list_remove (list *lst, list_node *posi, size_t n);
extern list_node *list_at (const list *lst, size_t n);
#define list_foreach(lst, node, begin, end)\
  for (list_node *node = (begin); node != (end); node = node->next)
#endif
