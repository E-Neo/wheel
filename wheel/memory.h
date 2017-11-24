#ifndef _MEMORY_H
#define _MEMORY_H

#include <stddef.h>

extern void *(*alloc_func) (size_t);
extern void *(*realloc_func) (void *, size_t);
extern void (*free_func) (void *);
extern void set_memory_functions (void *(*alloc_func) (size_t),
                                  void *(*realloc_func) (void *, size_t),
                                  void (*free_func) (void *));
extern void *memmem_brute_force (const void *haystack, size_t haystacklen,
                                 const void *needle, size_t needlelen);
extern void *memmem_kmp (const void *haystack, size_t haystacklen,
                         const void *needle, size_t needlelen);

#endif
