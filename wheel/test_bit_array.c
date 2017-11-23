#include <stdio.h>
#include "bit_array.h"

int
main ()
{
  bit_array *ba = bit_array_new (2048);
  bit_array_set (ba, 1280);
  printf ("%d\n", bit_array_test (ba, 1280));
  bit_array_clear (ba, 1280);
  printf ("%d\n", bit_array_test (ba, 1280));
  bit_array_free (ba);
  return 0;
}
