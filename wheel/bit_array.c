#include <string.h>
#include "bit_array.h"
#include "memory.h"

extern bit_array *
bit_array_new (size_t len)
{
  size_t _capacity = len / (sizeof (unsigned long) * 8) + 1;
  bit_array *ba = alloc_func (sizeof (bit_array));
  unsigned long *data = alloc_func (_capacity * sizeof (unsigned long));
  memset (data, 0, _capacity * sizeof (unsigned long));
  ba->data = data;
  ba->len = len;
  return ba;
}

extern void
bit_array_free (bit_array *ba)
{
  free_func (ba->data);
  free_func (ba);
}

extern void
bit_array_set (bit_array *ba, size_t n)
{
  unsigned long *base = ba->data + n / (sizeof (unsigned long) * 8);
  n %= sizeof (unsigned long);
  unsigned long mask = 1;
  while (n--) mask <<= 1;
  *base |= mask;
}

extern void
bit_array_clear (bit_array *ba, size_t n)
{
  unsigned long *base = ba->data + n / (sizeof (unsigned long) * 8);
  n %= sizeof (unsigned long);
  unsigned long mask = 1;
  while (n--) mask <<= 1;
  *base &= ~mask;
}

extern int
bit_array_test (const bit_array *ba, size_t n)
{
  unsigned long x = ba->data[n / (sizeof (unsigned long) * 8)];
  n %= sizeof (unsigned long);
  unsigned long mask = 1;
  while (n--) mask <<= 1;
  return x & mask;
}
