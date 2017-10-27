#include <stdio.h>
#include "queue.h"

struct _node
{
  int data;
};

int
main ()
{
  int a = 1, b = 2, c = 3;
  struct _node x; x.data = 4;
  queue *q = queue_new (sizeof (int));
  queue_enqueue (q, &a);
  queue_dequeue (q);
  queue_enqueue (q, &a);
  queue_enqueue (q, &b);
  queue_enqueue (q, &c);
  queue_enqueue (q, &x.data);
  for (size_t i = 0; i < q->len; i++)
    {
      int *t = queue_at (q, i);
      printf ("%d\n", *t);
    }
  queue_free (q);
  return 0;
}
