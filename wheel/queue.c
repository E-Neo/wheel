#include <string.h>
#include "queue.h"
#include "memory.h"

typedef struct _node _node;

struct _node
{
  void *data;
  struct _node *next;
};

extern queue *
queue_new (size_t _size)
{
  _node *head = alloc_func (sizeof (_node));
  head->data = NULL; head->next = NULL;
  queue *q = alloc_func (sizeof (queue));
  q->head = head; q->back = head;
  q->len = 0; q->_size = _size;
  return q;
}

extern void
queue_free (queue *q)
{
  _node *ptr = q->head, *tmp;
  while (ptr != NULL)
    {
      tmp = ptr->next;
      free_func (ptr->data);
      free_func (ptr);
      ptr = tmp;
    }
  free_func (q);
}

extern void
queue_enqueue (queue *q, const void *x)
{
  void *data = alloc_func (q->_size);
  memcpy (data, x, q->_size);
  _node *node = alloc_func (sizeof (_node));
  node->data = data; node->next = NULL;
  q->back->next = node;
  q->back = node;
  q->len++;
}

extern void
queue_dequeue (queue *q)
{
  _node *ptr = q->head;
  q->head = q->head->next;
  free_func (ptr->data);
  free_func (ptr);
  q->len--;
}

extern void *
queue_front (const queue *q)
{
  return q->head->next->data;
}

extern void *
queue_at (const queue *q, size_t n)
{
  _node *node = q->head->next;
  while (n--) node = node->next;
  return node->data;
}
