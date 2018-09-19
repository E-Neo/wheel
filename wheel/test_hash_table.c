#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hash_table.h"

typedef struct entry entry;

struct entry
{
  char province[16];
  char capital[16];
};

static size_t
hash_func (const void *e, size_t M)
{
  size_t key = 0;
  for (const char *p = ((const entry *) e)->province; *p; p++)
    key = *p + 256 * key;
  return (31 * key + 2) % M;
}

static int
equal_func (const void *e1, const void *e2)
{
  return !strcmp (((const entry *) e1)->province,
                  ((const entry *) e2)->province);
}

static void *
copy_func (const void *e)
{
  entry *ne = malloc (sizeof (entry));
  memcpy (ne, e, sizeof (entry));
  return ne;
}

static void
print_entry (const entry *e)
{
  if (e)
    printf ("province: %s\ncapital: %s\n", e->province, e->capital);
  else
    printf ("Nothing\n");
}

int
main ()
{
  hash_table *ht = hash_table_new (hash_func, equal_func, copy_func, free);
  entry e[] = { {"Jilin", "Changchun"},
                {"Jiangxi", "Nanchang"},
                {"Taiwan", "Taipei"} };
  for (size_t i = 0; i < sizeof (e) / sizeof (entry); i++)
    hash_table_insert (ht, e + i);
  e[0].capital[0] = 0;
  entry e1 = { "Jilin", "" };
  print_entry (hash_table_find (ht, &e1));
  hash_table_remove (ht, &e1);
  print_entry (hash_table_find (ht, &e1));
  hash_table_free (ht);
  return 0;
}
