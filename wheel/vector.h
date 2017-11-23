#ifndef _VECTOR_H
#define _VECTOR_H

#include <stddef.h>

#define VECTOR_DEFAULT_CAPACITY (64)

typedef struct vector vector;

struct vector
{
  void *data;
  size_t len;
  size_t _size, _capacity;
};

/* We do not do any boundary checking. Be careful.  */
extern vector *vector_new (size_t _size);
extern vector *vector_new_with_capacity (size_t _size, size_t _capacity);
extern vector *vector_copy (const vector *vec);
extern void vector_free (vector *vec);
/* The memory areas base and vec->data must not overlap.  */
extern void vector_insert (vector *vec, size_t posi,
                           const void *base, size_t n);
extern void vector_remove (vector *vec, size_t posi, size_t n);
/* func should return 0 if data should be removed.  */
extern void vector_remove_with_func (vector *vec, size_t begin, size_t end,
                                     int (*func) (const void *));
extern void *vector_at (const vector *vec, size_t n);
#define vector_foreach(vec, elem, begin, end)                           \
  for (void *elem = (char *) (vec)->data + (begin) * (vec)->_size,      \
         *elem_end = (char *) (vec)->data + (end) * (vec)->_size;       \
       (char *) elem < (char *) elem_end;                               \
       elem = (char *) elem + (vec)->_size)
extern void vector_reverse (vector *vec, size_t begin, size_t end);
extern void *vector_binary_search (vector *vec, const void *key,
                                   size_t begin, size_t end,
                                   int (*compar) (const void *, const void *));
extern void vector_merge_sort (vector *vec, size_t begin, size_t end,
                               int (*compar) (const void *, const void *));
extern void vector_insertion_sort (vector *vec, size_t begin, size_t end,
                                   int (*compar) (const void *, const void *));
extern void vector_bubble_sort (vector *vec, size_t begin, size_t end,
                                int (*compar) (const void *, const void *));

#endif
