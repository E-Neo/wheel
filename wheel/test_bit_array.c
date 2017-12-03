#include <stdio.h>
#include "bit_array.h"

static void
print_bit_array (const bit_array *ba, size_t begin, size_t end)
{
  for (size_t i = begin, count = 0;
       i < end;
       i++, count = (count + 1) % (sizeof (unsigned long) * 8))
    {
      if (!count) puts ("");
      printf ("%d", bit_array_test (ba, i));
    }
  puts ("");
}

int
main ()
{
  bit_array *ba = bit_array_new (128);
  bit_array_set (ba, 1);
  bit_array_set (ba, 64);
  bit_array_set (ba, 127);
  print_bit_array (ba, 0, ba->len);
  printf ("count: %zu\n", ba->count);
  bit_array_clear (ba, 1);
  print_bit_array (ba, 0, ba->len);
  printf ("count: %zu\n", ba->count);
  bit_array_free (ba);
  return 0;
}
