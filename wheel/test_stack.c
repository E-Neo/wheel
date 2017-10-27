#include <stdio.h>
#include "stack.h"

int
main ()
{
  int a[] = {1, 2, 3, 4, 5};
  size_t len = sizeof (a) / sizeof (int);
  stack *s = stack_new (sizeof (int));
  for (size_t i = 0; i < len; i++)
    stack_push (s, a + i);
  for (size_t i = 0; i < s->len; i++)
    {
      int *x = stack_at (s, i);
      printf ("%d\n", *x);
    }
  for (size_t i = 0; i < len - 1; i++)
    {
      int *x = stack_top (s); int y = *x; stack_pop (s);
      printf ("%d\n", y);
    }
  int *y = stack_top (s);
  printf ("%d\n", *y);
  stack_free (s);
  return 0;
}
