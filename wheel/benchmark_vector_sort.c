#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "vector.h"
#include "memory.h"

static void
print_vector_double (const vector *vec)
{
  if (vec->len == 0)
    printf ("{}");
  else
    {
      double *ptr = vec->data;
      size_t n = vec->len - 1;
      printf ("{");
      while (n--)
        printf (" %lf,", *(ptr++));
      printf (" %lf }", *ptr);
    }
}

static void
merge (void *base, void *begin, const void *end, void *buffer, size_t _size,
       int (*compar) (const void *, const void *))
{
  size_t tmp = (char *) begin - (char *) base;
  const void *buffer_end = buffer + tmp;
  memcpy (buffer, base, tmp);
  while (buffer < buffer_end && begin < end)
    {
      if (compar (buffer, begin) <= 0)
        {
          memcpy (base, buffer, _size);
          buffer = (char *) buffer + _size;
        }
      else
        {
          memcpy (base, begin, _size);
          begin = (char *) begin + _size;
        }
      base = (char *) base + _size;
    }
  if (buffer < buffer_end)
    memcpy (base, buffer, (char *) buffer_end - (char *) buffer);
}

static void
vector_merge_sort_rec (vector *vec, size_t begin, size_t end,
                       int (*compar) (const void *, const void *))
{
  if (end - begin < 2) return;
  size_t mid = (begin + end) >> 1, _size = vec->_size;
  void *buffer = alloc_func ((mid - begin) * _size);
  vector_merge_sort_rec (vec, begin, mid, compar);
  vector_merge_sort_rec (vec, mid, end, compar);
  merge ((char *) vec->data + begin * _size,
         (char *) vec->data + mid * _size,
         (char *) vec->data + end * _size,
         buffer, _size, compar);
  free_func (buffer);
}

static int
compar (const void *a, const void *b)
{
  return *(int *) a - *(int *) b;
}

static double
get_time ()
{
  struct timespec ts;
  timespec_get (&ts, TIME_UTC);
  return (double) ts.tv_sec + (double) ts.tv_nsec * 1e-9;
}

static vector *
make_random_vector (size_t n)
{
  vector *vec = vector_new_with_capacity (sizeof (int), n);
  while (n--)
    {
      int r = rand ();
      vector_insert (vec, vec->len, &r, 1);
    }
  return vec;
}

static double
test_sort (const vector *src_vec, size_t n,
           void (*sort) (vector *, size_t, size_t,
                         int (*) (const void *, const void *)))
{
  vector *vec = vector_new_with_capacity (src_vec->_size, n);
  vector_insert (vec, 0, src_vec->data, n);
  double begin_time = get_time ();
  sort (vec, 0, vec->len, compar);
  double end_time = get_time ();
  vector_free (vec);
  return end_time - begin_time;
}

static vector *
test_sort_with_num (const vector *src_vec, const size_t *num, size_t n,
                    void (*sort) (vector *, size_t, size_t,
                                  int (*) (const void *, const void *)))
{
  vector *t = vector_new_with_capacity (sizeof (double), n);
  while (n--)
    {
      double delta = test_sort (src_vec, *(num++), sort);
      vector_insert (t, t->len, &delta, 1);
    }
  return t;
}

int
main ()
{
  vector *src_vec = make_random_vector (1 << 24);
  size_t num[] = {16, 21, 64, 100, 256,
                  379, 1024, 1668, 4096, 5591,
                  16384, 24796, 65536, 127942, 262144,
                  502320, 1048576, 1462117, 4194304, 7478860,
                  16777216};
  vector *tmp;
  tmp = test_sort_with_num (src_vec, num,
                            sizeof (num) / sizeof (size_t),
                            vector_merge_sort);
  print_vector_double (tmp); printf ("\n");
  vector_free (tmp);
  tmp = test_sort_with_num (src_vec, num,
                            sizeof (num) / sizeof (size_t),
                            vector_merge_sort_rec);
  print_vector_double (tmp); printf ("\n");
  vector_free (tmp);
  vector_free (src_vec);
  return 0;
}
