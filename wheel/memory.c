#include <stdlib.h>
#include <stdio.h>
#include "memory.h"

static void *
default_alloc (size_t size)
{
  void *res = malloc (size);
  if (NULL == res)
    {
      fprintf (stderr, "wheel: cannot allocate memory (size=%zu)\n", size);
      abort ();
    }
  return res;
}

static void *
default_realloc (void *ptr, size_t size)
{
  if (NULL == (ptr = realloc (ptr, size)))
    {
      fprintf (stderr, "wheel: cannot reallocate memory (size=%zu)\n", size);
      abort ();
    }
  return ptr;
}

static void
default_free (void *ptr)
{
  free (ptr);
}

void *(*alloc_func) (size_t) = default_alloc;
void *(*realloc_func) (void *, size_t) = default_realloc;
void (*free_func) (void *) = default_free;

extern void *
memmem_brute_force (const void *haystack, size_t haystacklen,
                    const void *needle, size_t needlelen)
{
  const char *haystack_begin = haystack;
  const char *needle_begin = needle;
  const char *haystack_end = (char *) haystack + haystacklen;
  const char *needle_end = (char *) needle + needlelen;
  const char *i = haystack_begin, *j = needle_begin;
  while (j < needle_end && i < haystack_end)
    if (*i == *j)
      {
        i++;
        j++;
      }
    else
      {
        i = i - (j - needle_begin) + 1;
        j = needle_begin;
      }
  return j == needle_end ? (void *) (i - (j - needle_begin)) : NULL;
}

extern void *
memmem_kmp (const void *haystack, size_t haystacklen,
            const void *needle, size_t needlelen)
{
  const char *haystack_begin = haystack;
  const char *needle_begin = needle;
  const char *haystack_end = (char *) haystack + haystacklen;
  const char *needle_end = (char *) needle + needlelen;
  /* build next */
  const char **next = alloc_func (needlelen * sizeof (const char *));
  const char *i, *j;
  i = needle_begin;
  j = needle_begin - 1;
  next[0] = needle_begin - 1;
  while (i < needle_end - 1)
    if (j < needle_begin || *i == *j)
      {
        i++;
        j++;
        next[i - needle_begin] = j;
      }
    else
      j = next[j - needle_begin];
  /* match */
  i = haystack_begin;
  j = needle_begin;
  while (j < needle_end && i < haystack_end)
    if (j < needle_begin || *i == *j)
      {
        i++;
        j++;
      }
    else
      j = next[j - needle_begin];
  free_func (next);
  return j == needle_end ? (void *) (i - (j - needle_begin)) : NULL;
  return NULL;
}
