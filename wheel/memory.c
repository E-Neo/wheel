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
