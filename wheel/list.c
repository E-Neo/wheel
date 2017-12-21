#include <string.h>
#include "list.h"
#include "memory.h"

extern list *
list_new (size_t _size)
{
  list *lst = alloc_func (sizeof (list));
  list_node *head = alloc_func (sizeof (list_node) << 1), *tail = head + 1;
  head->data = NULL; head->prev = NULL; head->next = tail;
  tail->data = NULL; tail->prev = head; tail->next = NULL;
  lst->head = head; lst->tail = tail; lst->len = 0; lst->_size = _size;
  return lst;
}

extern void
list_free (list *lst)
{
  list_node *node = lst->tail->prev;
  while (node != lst->head)
    {
      free_func (node->data);
      node = node->prev;
      free_func (node->next);
    }
  free_func (node);
  free_func (lst);
}

extern list_node *
list_insert (list *lst, list_node *posi, const void *base, size_t n)
{
  if (0 == n) return posi;
  void *data;
  list_node *res;
  size_t count;
  data = alloc_func (lst->_size);
  memcpy (data, base, lst->_size);
  res = alloc_func (sizeof (list_node));
  res->data = data;
  res->prev = posi->prev; res->next = posi;
  posi->prev->next = res; posi->prev = res;
  base = (char *) base + lst->_size;
  count = n - 1;
  while (count--)
    {
      data = alloc_func (lst->_size);
      memcpy (data, base, lst->_size);
      list_node *node = alloc_func (sizeof (list_node));
      node->data = data;
      node->prev = posi->prev; node->next = posi;
      posi->prev->next = node; posi->prev = node;
      base = (char *) base + lst->_size;
    }
  lst->len += n;
  return res;
}

extern list_node *
list_remove (list *lst, list_node *posi, size_t n)
{
  size_t count = n;
  while (count--)
    {
      list_node *node = posi->next;
      posi->prev->next = posi->next;
      posi->next->prev = posi->prev;
      free_func (posi->data);
      free_func (posi);
      posi = node;
    }
  lst->len -= n;
  return posi;
}

extern list_node *
list_at (const list *lst, size_t n)
{
  list_node *node = lst->head->next;
  while (n--) node = node->next;
  return node;
}

extern list_node *
list_search (const list *lst, const list_node *begin, const list_node *end,
             const void *key, int (*compar) (const void *, const void *))
{
  list_foreach (lst, node, (list_node *) begin, end)
    if (!compar (key, node->data))
      return node;
  return NULL;
}

extern void
list_insertion_sort (const list *lst,
                     const list_node *begin, const list_node *end,
                     int (*compar) (const void *, const void *))
{
  list_node *sorted_end = begin->next;
  while (sorted_end != end)
    {
      list_node *next = sorted_end->next;
      list_foreach (lst, node, (list_node *) begin, sorted_end)
        if (compar (node->data, sorted_end->data) > 0)
          {
            list_node *tmp0 = node->prev;
            node->prev = sorted_end;
            tmp0->next = sorted_end;
            list_node *tmp1 = sorted_end->prev;
            sorted_end->prev = tmp0;
            sorted_end->next = node;
            tmp1->next = next;
            next->prev = tmp1;
            break;
          }
      sorted_end = next;
    }
}
