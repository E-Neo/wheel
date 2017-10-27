#include <stdio.h>
#include "vector.h"

int
main ()
{
  vector *vec = vector_new (sizeof (int));
  int array[] = {1, 2, 3};
  vector_insert (vec, vec->len, array, 3);
  for (size_t i = 0; i < 5; i++)
    vector_insert (vec, 1, &i, 1);
  vector_remove (vec, 1, 6);
  for (size_t i = 0; i < vec->len; i++)
    {
      int *x = vector_at (vec, i);
      printf ("%d\n", *x);
    }
  vector_free (vec);
  return 0;
}
