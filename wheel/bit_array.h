#ifndef _BIT_ARRAY_H
#define _BIT_ARRAY_H

#include <stddef.h>

#define BIT_ARRAY_DEFAULT_LEN (1024)

typedef struct bit_array bit_array;

struct bit_array
{
  unsigned long *data;
  size_t _capacity;
};

/* bit_array_set() will let the array grow when need, but bit_array_clear()
   and bit_array_test() will not do any boundary checking. Be careful.   */
extern bit_array *bit_array_new ();
extern bit_array *bit_array_new_with_len (size_t _capacity);
extern void bit_array_set_len (bit_array *ba, size_t _capacity);
extern void bit_array_free (bit_array *ba);
extern void bit_array_set (bit_array *ba, size_t n);
extern void bit_array_clear (bit_array *ba, size_t n);
extern int bit_array_test (const bit_array *ba, size_t n);

#endif
