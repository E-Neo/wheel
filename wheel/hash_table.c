#include <string.h>
#include "hash_table.h"
#include "memory.h"

static void **
data_array_new (size_t _capacity, size_t *M)
{
  size_t PRIME_MAX_IDX = 25;
  size_t primes[] = { 67, 137, 277, 557,
                      1117, 2237, 4481, 8963,
                      17929, 35863, 71741, 143483,
                      286973, 573953, 1147921, 2295859,
                      4591721, 9183457, 18366923, 36733847,
                      73467739, 146935499, 293871013, 587742049,
                      1175484103, 2350968209 };
  size_t i;
  for (i = 0; i < PRIME_MAX_IDX; i++)
    if (primes[i] > _capacity)
      break;
  if (_capacity >= primes[i])
    {
      *M = 0;
      return NULL;
    }
  *M = primes[i];
  void **data = alloc_func (sizeof (void *) * primes[i]);
  memset (data, 0, sizeof (void *) * primes[i]);
  return data;
}

extern hash_table *
hash_table_new_with_capacity (size_t (*hash_func) (const void *, size_t),
                              int (*equal_func) (const void *, const void *),
                              void *(*copy_func) (const void *),
                              void (*free_func) (void *),
                              size_t capacity)
{
  hash_table *ht = alloc_func (sizeof (hash_table));
  ht->N = 0;
  ht->data = data_array_new (capacity, &ht->M);
  ht->lazy_removal = bit_array_new (ht->M);
  ht->hash_func = hash_func;
  ht->equal_func = equal_func;
  ht->copy_func = copy_func;
  ht->free_func = free_func;
  return ht;
}

extern hash_table *
hash_table_new (size_t (*hash_func) (const void *, size_t),
                int (*equal_func) (const void *, const void *),
                void *(*copy_func) (const void *),
                void (*free_func) (void *))
{
  return hash_table_new_with_capacity (hash_func, equal_func,
                                       copy_func, free_func, 0);
}

extern void
hash_table_free (hash_table *ht)
{
  for (size_t i = 0; i < ht->M; i++)
    ht->free_func (ht->data[i]);
  free_func (ht->data);
  bit_array_free (ht->lazy_removal);
  free_func (ht);
}

static size_t
probe4hit (hash_table *ht, const void *data, size_t hash)
{
  while ((ht->data[hash] && !ht->equal_func (data, ht->data[hash]))
         || (!ht->data[hash] && bit_array_test (ht->lazy_removal, hash)))
    hash = (hash + 1) % ht->M;
  return hash;
}

static size_t
probe4free (hash_table *ht, size_t hash)
{
  while (ht->data[hash])
    hash = (hash + 1) % ht->M;
  return hash;
}

static void
rehash (hash_table *ht)
{
  void **old_data = ht->data;
  size_t old_M = ht->M;
  ht->data = data_array_new (2 * old_M, &ht->M);
  bit_array_free (ht->lazy_removal);
  ht->lazy_removal = bit_array_new (ht->M);
  for (size_t i = 0; i < old_M; i++)
    if (old_data[i])
      {
        size_t hash = probe4free (ht, ht->hash_func (old_data[i], ht->M));
        ht->data[hash] = old_data[i];
      }
  free_func (old_data);
}

extern int
hash_table_insert_with_hash (hash_table *ht, const void *data, size_t hash)
{
  if (ht->data[probe4hit (ht, data, hash)]) return 0;
  hash = probe4free (ht, hash);
  ht->data[hash] = ht->copy_func (data);
  ht->N++;
  if (2 * ht->N > ht->M) rehash (ht);
  return 1;
}

extern int
hash_table_insert (hash_table *ht, const void *data)
{
  return hash_table_insert_with_hash (ht, data, ht->hash_func (data, ht->M));
}

extern int
hash_table_remove (hash_table *ht, const void *data)
{
  size_t hash = probe4hit (ht, data, ht->hash_func (data, ht->M));
  if (!ht->data[hash]) return 0;
  ht->free_func (ht->data[hash]);
  ht->data[hash] = NULL;
  bit_array_set (ht->lazy_removal, hash);
  ht->N--;
  return 1;
}

extern void *
hash_table_find (hash_table *ht, const void *data)
{
  return ht->data[probe4hit (ht, data, ht->hash_func (data, ht->M))];
}
