#include "stack_permutation.h"
#include "stack.h"

/* Time: O(n)
   Space: O(1)  */
extern size_t
stack_permutation_num (size_t n)
{
  /* Catalan number: Cn = (2n choose n) / (n + 1) */
  size_t a = 1, b = 1, c = 2 * n, d = n;
  while (d)
    {
      a *= c--;
      b *= d--;
    }
  return a / b / (n + 1);
}

/* Time: O(n)
   Space: O(n)  */
extern int
stack_permutation_valid_p (size_t *p, size_t n)
{
  stack *s = stack_new (sizeof (size_t));
  size_t count = 0;
  while (n)
    {
      if (*p < count)
        {
          if (*(size_t *) stack_top (s) != *p)
            {
              stack_free (s);
              return 0;
            }
          stack_pop (s); p++; n--;
        }
      else
        {
          stack_push (s, &count); count++;
        }
    }
  stack_free (s);
  return 1;
}
