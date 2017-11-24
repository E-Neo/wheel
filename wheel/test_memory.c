#include <stdio.h>
#include <string.h>
#include "memory.h"

static void
test_memmem (const char *str, size_t str_len,
             const char *ptr, size_t ptr_len,
             void *(*memmem_func) (const void *, size_t,
                                   const void *, size_t))
{
  char *sub_str = memmem_func (str, str_len, ptr, ptr_len);
  if (sub_str)
    printf ("found: %s\n", sub_str);
  else
    printf ("not found\n");
}

int
main ()
{
  char str[] = "abcabaaabaabcac";
  char ptr0[] = "abaabcac";
  char ptr1[] = "abcd";
  char *sub_str;

  puts ("expect:");
  sub_str = strstr (str, ptr0);
  if (sub_str)
    printf ("found: %s\n", sub_str);
  else
    printf ("not found\n");
  sub_str = strstr (str, ptr1);
  if (sub_str)
    printf ("found: %s\n", sub_str);
  else
    printf ("not found\n");
  puts ("");

  puts ("brute_force:");
  test_memmem (str, sizeof (str) - 1, ptr0, sizeof (ptr0) - 1, memmem_brute_force);
  test_memmem (str, sizeof (str) - 1, ptr1, sizeof (ptr1) - 1, memmem_brute_force);
  puts ("");

  puts ("kmp:");
  test_memmem (str, sizeof (str) - 1, ptr0, sizeof (ptr0) - 1, memmem_kmp);
  test_memmem (str, sizeof (str) - 1, ptr1, sizeof (ptr1) - 1, memmem_kmp);
  puts ("");
  return 0;
}
