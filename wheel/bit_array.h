#ifndef _BIT_ARRAY_H
#define _BIT_ARRAY_H

#include <stddef.h>

typedef struct bit_array bit_array;

struct bit_array
{
  unsigned long *data;
  size_t count, len;
};

extern bit_array *bit_array_new (size_t len);
extern void bit_array_free (bit_array *ba);
extern void bit_array_set (bit_array *ba, size_t n);
extern void bit_array_clear (bit_array *ba, size_t n);
extern int bit_array_test (const bit_array *ba, size_t n);

#endif
