#ifndef _QUEUE_H
#define _QUEUE_H

#include <stddef.h>

typedef struct queue queue;

struct queue
{
  struct _node *head, *back;
  size_t len;
  size_t _size;
};

extern queue *queue_new (size_t _size);
extern void queue_free (queue *q);
extern void queue_enqueue (queue *q, const void *x);
extern void queue_dequeue (queue *q);
extern void *queue_front (const queue *q);
extern void *queue_at (const queue *q, size_t n);

#endif
