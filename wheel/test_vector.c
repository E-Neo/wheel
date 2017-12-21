#include <stdio.h>
#include "vector.h"

static void
print_vector_int (const vector *vec)
{
  vector_foreach (vec, x, 0, vec->len)
    printf (" %d", *(int *) x);
  puts ("");
}

static int
compar (const void *a, const void *b)
{
  return *(int *) a - *(int *) b;
}

static int
remove_func (const void *x)
{
  return *(int *) x >= 0;
}

int
main ()
{
  vector *vec_src = vector_new (sizeof (int));
  int array[] = {-4, 6, 3, 2, 7, 1, 5, 8, 4, 0, -1, -3};
  vector_insert (vec_src, 0, array, sizeof (array) / sizeof (int));
  vector_insert (vec_src, 5, array, 7);
  vector_remove (vec_src, 5, 7);
  vector_remove_with_func (vec_src, 0, vec_src->len, remove_func);
  printf ("vec:");
  print_vector_int (vec_src);
  puts ("");
  vector *vec;

  vec = vector_copy (vec_src);
  vector_insertion_sort (vec, 0, vec->len, compar);
  int x = 6;
  printf ("binary_search\nexpect: 6\nresult: %d\n\n",
          *(int *) vector_binary_search (vec, &x, 0, vec->len, compar));
  vector_free (vec);

  vec = vector_copy (vec_src);
  printf ("quicksort\nexpect: 0 1 2 3 4 5 6 7 8\nresult:");
  vector_quicksort (vec, 0, vec->len, compar);
  print_vector_int (vec);
  vector_free (vec);
  puts ("");

  vec = vector_copy (vec_src);
  printf ("merge_sort\nexpect: 0 1 2 3 4 5 6 7 8\nresult:");
  vector_merge_sort (vec, 0, vec->len, compar);
  print_vector_int (vec);
  vector_free (vec);
  puts ("");

  vec = vector_copy (vec_src);
  printf ("insertion_sort\nexpect: 0 1 2 3 4 5 6 7 8\nresult:");
  vector_insertion_sort (vec, 0, vec->len, compar);
  print_vector_int (vec);
  vector_free (vec);
  puts ("");

  vec = vector_copy (vec_src);
  printf ("bubble_sort\nexpect: 0 1 2 3 4 5 6 7 8\nresult:");
  vector_bubble_sort (vec, 0, vec->len, compar);
  print_vector_int (vec);
  vector_free (vec);

  vector_free (vec_src);
  return 0;
}
