#include <string.h>
#include "vector.h"
#include "memory.h"

extern vector *
vector_new_with_capacity (size_t _size, size_t _capacity)
{
  vector *vec = alloc_func (sizeof (vector));
  vec->data = alloc_func (_size * _capacity);
  vec->len = 0; vec->_size = _size; vec->_capacity = _capacity;
  return vec;
}

extern vector *
vector_new (size_t _size)
{
  return vector_new_with_capacity (_size, VECTOR_DEFAULT_CAPACITY);
}

extern void
vector_free (vector *vec)
{
  free_func (vec->data);
  free_func (vec);
}

extern void
vector_insert (vector *vec, size_t posi, void *base, size_t n)
{
  if (vec->len + n > vec->_capacity)
    {
      size_t capacity = vec->_capacity << 1;
      while (vec->len + n > capacity) capacity <<= 1;
      vec->data = realloc_func (vec->data, capacity * vec->_size);
      vec->_capacity = capacity;
    }
  memmove ((char *) vec->data + (posi + n) * vec->_size,
           (char *) vec->data + posi * vec->_size,
           (vec->len - posi) * vec->_size);
  memcpy ((char *) vec->data + posi * vec->_size, base, n * vec->_size);
  vec->len += n;
}

extern void
vector_remove (vector *vec, size_t posi, size_t n)
{
  memmove ((char *) vec->data + posi * vec->_size,
           (char *) vec->data + (posi + n) * vec->_size,
           (vec->len - posi - n) * vec->_size);
  vec->len -= n;
}

extern void *
vector_at (const vector *vec, size_t n)
{
  return (char *) vec->data + n * vec->_size;
}
