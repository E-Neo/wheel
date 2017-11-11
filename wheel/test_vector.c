#include <stdio.h>
#include "vector.h"

static void
print_vector_int (const vector *vec)
{
  if (vec->len == 0)
    {
      puts ("{}");
      return;
    }
  printf ("{");
  const int *data_end = (int *) vec->data + vec->len;
  for (int *data = vec->data; data < data_end - 1; data++)
    printf (" %d,", *data);
  printf (" %d }\n", *(data_end - 1));
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
  vector *vec = vector_new (sizeof (int));
  int array[] = {-4, 6, 3, 2, 7, 1, 5, 8, 4, 0, -1, -3};
  vector_insert (vec, 0, array, sizeof (array) / sizeof (int));
  vector_insert (vec, 5, array, 7);
  vector_remove (vec, 5, 7);
  vector_remove_with_func (vec, 0, vec->len, remove_func);
  vector *vec_cpy = vector_copy (vec);
  print_vector_int (vec);
  vector_merge_sort (vec, 0, vec->len, compar);
  puts ("merge_sort: expect { 0, 1, 2, 3, 4, 5, 6, 7, 8 }");
  print_vector_int (vec);
  printf ("expect 6: %d\n",
          *(int *) vector_binary_search (vec, array + 1, 0, vec->len, compar));
  vector_free (vec);
  vec = vector_copy (vec_cpy);
  vector_insertion_sort (vec, 0, vec->len, compar);
  puts ("insertion_sort: expect { 0, 1, 2, 3, 4, 5, 6, 7, 8 }");
  print_vector_int (vec);
  vector_free (vec);
  vec = vector_copy (vec_cpy);
  vector_bubble_sort (vec, 0, vec->len, compar);
  puts ("bubble_sort: expect { 0, 1, 2, 3, 4, 5, 6, 7, 8 }");
  print_vector_int (vec);
  vector_free (vec);
  vector_free (vec_cpy);
  return 0;
}
