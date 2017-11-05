#include <string.h>
#include "digraph.h"
#include "memory.h"
#include "bit_array.h"
#include "queue.h"

typedef struct _node _node;

struct _node
{
  size_t id;  /* node id */
  void *data;  /* edge data */
  _node *next;
};

static _node *
_node_new (size_t id, const void *base, _node *next, size_t _size)
{
  _node *node = alloc_func (sizeof (_node));
  node->id = id;
  node->data = alloc_func (_size);
  memcpy (node->data, base, _size);
  node->next = next;
  return node;
}

static void
_node_free (_node *node)
{
  while (node)
    {
      _node *tmp = node->next;
      free_func (node->data);
      free_func (node);
      node = tmp;
    }
}

extern digraph *
digraph_new (size_t _size, size_t _node_size, size_t _edge_size)
{
  digraph *G = alloc_func (sizeof (digraph));
  G->data = alloc_func (_size);
  G->node = vector_new (_node_size);
  G->succ = vector_new (sizeof (_node));
  G->n = 0; G->e = 0;
  G->_size = _size; G->_node_size = _node_size; G->_edge_size = _edge_size;
  return G;
}

extern void
digraph_free (digraph *G)
{
  free_func (G->data);
  vector_free (G->node);
  for (size_t i = 0; i < G->n; i++)
    {
      _node *tmp = vector_at (G->succ, i);
      _node_free (tmp->next);
    }
  vector_free (G->succ);
  free_func (G);
}

/* O(1) */
extern void
digraph_insert_node (digraph *G, const void *base)
{
  vector_insert (G->node, G->n, base, 1);
  _node tmp = { .id = 0, .data = NULL, .next = NULL };
  vector_insert (G->succ, G->n, &tmp, 1);
  G->n++;
}

/* O(1) */
extern void
digraph_insert_edge (digraph *G, size_t u, size_t v, const void *base)
{
  _node *u_succ_head = vector_at (G->succ, u);
  _node *u_succ = _node_new (v, base, u_succ_head->next, G->_edge_size);
  u_succ_head->next = u_succ;
  G->e++;
}

/* O(e) */
extern void
digraph_remove_node (digraph *G, size_t n)
{
  vector_remove (G->node, n, 1);
  _node *p = vector_at (G->succ, n), *q = p->next;
  while (q)
    {
      p->next = q->next;
      free_func (q->data); free_func (q);
      q = p->next;
      G->e--;
    }
  vector_remove (G->succ, n, 1);
  G->n--;
  for (size_t i = 0; i < G->n; i++)
    {
      p = vector_at (G->succ, i); q = p->next;
      while (q)
        {
          if (q->id == n)
            {
              p->next = q->next;
              free_func (q->data); free_func (q);
              q = p->next;
              G->e--;
            }
          else
            {
              if (q->id > n) q->id--;
              p = p->next; q = q->next;
            }
        }
      while (q && q->id != n) { p = p->next; q = q->next; }
      if (q) { p->next = q->next; free_func (q->data); free_func (q); }
    }
}

/* O(e) */
extern void
digraph_remove_edge (digraph *G, size_t u, size_t v)
{
  _node *p = vector_at (G->succ, u), *q = p->next;
  while (q->id != v) { p = p->next, q = q->next; }
  p->next = q->next; free_func (q->data); free_func (q);
  G->e--;
}

/* O(1) */
extern void *
digraph_at_node (digraph *G, size_t n)
{
  return vector_at (G->node, n);
}

/* O(e) */
extern void *
digraph_at_edge (digraph *G, size_t u, size_t v)
{
  _node *p = vector_at (G->succ, u); p = p->next;
  while (p->id != v) p = p->next;
  return p->data;
}

/* O(n + e) */
extern void
digraph_bfs (digraph *G, size_t s, void (*visit) (void *, void *), void *arg)
{
  bit_array *discovered = bit_array_new_with_len (G->n);
  queue *q = queue_new (sizeof (size_t));
  queue_enqueue (q, &s); bit_array_set (discovered, s);
  while (q->len)
    {
      size_t *tmp = queue_front (q); s = *tmp; queue_dequeue (q);
      _node *ptr = vector_at (G->succ, s);
      while ((ptr = ptr->next))
        if (!bit_array_test (discovered, ptr->id))
          {
            queue_enqueue (q, &ptr->id);
            bit_array_set (discovered, ptr->id);
          }
      visit (vector_at (G->node, s), arg);
    }
  bit_array_free (discovered);
  queue_free (q);
}

/* O(n + e) */
extern void
digraph_dfs_preorder (digraph *G, size_t s,
                      void (*visit) (void *, void *), void *arg)
{
  bit_array *visited = bit_array_new_with_len (G->n);
  size_t *stack = alloc_func (G->n * sizeof (size_t)); size_t len = 0;
  stack[len++] = s; bit_array_set (visited, s);
  while (len)
    {
      s = stack[--len];
      visit (vector_at (G->node, s), arg);
      _node *ptr = vector_at (G->succ, s);
      while ((ptr = ptr->next))
        {
          size_t id = ptr->id;
          if (!bit_array_test (visited, id))
            {
              stack[len++] = id;
              bit_array_set (visited, id);
            }
        }
    }
  bit_array_free (visited);
  free_func (stack);
}
