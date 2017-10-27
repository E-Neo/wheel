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
extern void vector_free (vector *vec);
/* The memory areas base and vec->data must not overlap.  */
extern void vector_insert (vector *vec, size_t posi, void *base, size_t n);
extern void vector_remove (vector *vec, size_t posi, size_t n);
extern void *vector_at (const vector *vec, size_t n);

#endif
