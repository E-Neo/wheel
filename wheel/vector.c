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

extern vector *
vector_copy (const vector *vec)
{
  vector *new = vector_new_with_capacity (vec->_size, vec->_capacity);
  new->len = vec->len;
  memcpy (new->data, vec->data, vec->len * vec->_size);
  return new;
}

extern void
vector_free (vector *vec)
{
  free_func (vec->data);
  free_func (vec);
}

extern void
vector_insert (vector *vec, size_t posi, const void *base, size_t n)
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

extern void
vector_remove_with_func (vector *vec, size_t begin, size_t end,
                         int (*func) (const void *))
{
  size_t _size = vec->_size, count = 0;
  char *base = vec->data;
  const char *base_end = base + end * _size;
  base += begin * _size;
  char *ptr = base;
  while (ptr < base_end)
    {
      if (func (ptr))
        {
          memcpy (base, ptr, _size);
          count++;
          base += _size;
        }
      ptr += _size;
    }
  vec->len = count;
}

extern void *
vector_at (const vector *vec, size_t n)
{
  return (char *) vec->data + n * vec->_size;
}

static void *
binary_search (const void *key, const void *base, size_t len,
               size_t _size, int (*compar) (const void *, const void *))
{
  while (len)
    {
      const char *begin = (char *) base + (len >> 1) * _size;
      int result = compar (key, begin);
      if (result == 0)
        return (void *) begin;
      if (result > 0)
        {
          base = begin + _size;
          len--;
        }
      len >>= 1;
    }
  return NULL;
}

extern void *
vector_binary_search (vector *vec, const void *key, size_t begin, size_t end,
                      int (*compar) (const void *, const void *))
{
  size_t _size = vec->_size;
  char *data = vec->data;
  /* replace binary_search() with bsearch() in stdlib.h if you want.  */
  return binary_search (key, data + begin * _size,
                        end - begin, _size, compar);
}

/* O(n) */
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

/* extern void */
/* vector_merge_sort (vector *vec, size_t begin, size_t end, */
/*                    int (*compar) (const void *, const void *)) */
/* { */
/*   if (end - begin < 2) return; */
/*   size_t mid = (begin + end) >> 1, _size = vec->_size; */
/*   void *buffer = alloc_func ((mid - begin) * _size); */
/*   vector_merge_sort (vec, begin, mid, compar); */
/*   vector_merge_sort (vec, mid, end, compar); */
/*   merge ((char *) vec->data + begin * _size, */
/*          (char *) vec->data + mid * _size, */
/*          (char *) vec->data + end * _size, */
/*          buffer, _size, compar); */
/*   free_func (buffer); */
/* } */

static void
merge_sort (void *base, size_t len, size_t _size,
            int (*compar) (const void *, const void *))
{
  size_t total_size = len * _size;
  const char *end = (char *) base + total_size;
  void *buffer = alloc_func (total_size);
  for (size_t width = _size; width < total_size; width <<= 1)
    for (char *ptr = base; ptr < end; ptr += width << 1)
      {
        char *tmp = ptr + width;
        char *sub_begin = tmp < end ? tmp : ptr;
        tmp += width;
        const char *sub_end = tmp < end ? tmp : end;
        merge (ptr, sub_begin, sub_end, buffer, _size, compar);
      }
  free_func (buffer);
}

/* Time: O(n log n)
   Space: O(n)  */
extern void
vector_merge_sort (vector *vec, size_t begin, size_t end,
                   int (*compar) (const void *, const void *))
{
  size_t _size = vec->_size;
  merge_sort (vec->data + begin * _size, end - begin, _size, compar);
}
