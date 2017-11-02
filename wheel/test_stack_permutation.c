#include <stdio.h>
#include "stack_permutation.h"

int
main ()
{
  printf ("expect 42: %zu\n", stack_permutation_num (5));
  size_t p1[] = {3, 2, 4, 1, 5, 0};
  size_t p2[] = {2, 0, 1, 3, 4, 5};
  printf ("expect 1 0: %d %d\n",
          stack_permutation_valid_p (p1, 6),
          stack_permutation_valid_p (p2, 6));
  return 0;
}
