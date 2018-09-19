#ifndef _HASH_TABLE_H
#define _HASH_TABLE_H

#include <stddef.h>
#include "bit_array.h"

typedef struct hash_table hash_table;

struct hash_table
{
  void **data;
  size_t M;
  size_t N;
  bit_array *lazy_removal;
  size_t (*hash_func) (const void *, size_t);
  int (*equal_func) (const void *, const void *);
  void *(*copy_func) (const void *);
  void (*free_func) (void *);
};

extern hash_table *hash_table_new \
(size_t (*hash_func) (const void *, size_t),
 int (*equal_func) (const void *, const void *),
 void *(*copy_func) (const void *),
 void (*free_func) (void *));
extern hash_table *hash_table_new_with_capacity \
(size_t (*hash_func) (const void *, size_t),
 int (*equal_func) (const void *, const void *),
 void *(*copy_func) (const void *),
 void (*free_func) (void *),
 size_t capacity);
extern void hash_table_free (hash_table *ht);
extern int hash_table_insert (hash_table *ht, const void *data);
/* We provide hash_table_insert_with_hash() for rolling hash.  */
extern int hash_table_insert_with_hash (hash_table *ht, const void *data,
                                        size_t hash);
extern int hash_table_remove (hash_table *ht, const void *data);
extern void *hash_table_find (hash_table *ht, const void *data);

#endif
