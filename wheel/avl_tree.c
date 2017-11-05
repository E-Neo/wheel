#include <string.h>
#include "avl_tree.h"
#include "memory.h"

typedef struct avl_node avl_node;

struct avl_node
{
  void *data;
  avl_node *parent, *lc, *rc;
  char balance_factor;
};

static avl_node *
avl_node_new (const void *data, size_t _size,
              avl_node *parent, avl_node *lc, avl_node *rc)
{
  avl_node *node = alloc_func (sizeof (avl_node));
  node->data = alloc_func (_size);
  memcpy (node->data, data, _size);
  node->parent = parent; node->lc = parent; node->rc = parent;
  node->balance_factor = 0;
  return node;
}

extern avl_tree *
avl_tree_new (size_t _size, int (*compar) (const void *, const void *))
{
  avl_tree *T = alloc_func (sizeof (avl_tree));
  T->null = avl_node_new (NULL, 0, NULL, NULL, NULL);
  T->root = T->null;
  T->n = 0;
  T->_size = _size;
  T->compar = compar;
  return T;
}

extern void
avl_tree_free (avl_tree *T)
{
  if (T->root == T->null) { free_func (T->null); free_func (T); return; }
  avl_node **stack = alloc_func (((T->n + 1) >> 1) * sizeof (avl_node *));
  size_t len = 0;
  stack[len++] = T->root;
  while (len)
    {
      avl_node *node = stack[--len];
      if (node->rc != T->null) stack[len++] = node->rc;
      if (node->lc != T->null) stack[len++] = node->lc;
      free_func (node->data); free_func (node);
    }
  free_func (stack);
  free_func (T->null);
  free_func (T);
}

extern void *
avl_tree_search (const avl_tree *T, const void *key)
{
  avl_node *node = T->root;
  while (1)
    {
      if (node == T->null) return NULL;
      int result = T->compar (key, node->data);
      if (result == 0) return node->data;
      node = result < 0 ? node->lc : node->rc;
    }
}

/*     |                    |   */
/*     u  rotate_right(u)   v   */
/*    / \ -------------->  / \  */
/*   v  Z <-------------- X  u  */
/*  / \   rotate_left(v)    / \ */
/* X  Y                    Y  Z */
static void
avl_node_rotate_right (avl_node *u)
{
  avl_node *p = u->parent, *v = u->lc;
  if (u == p->lc) p->lc = v;
  else p->rc = v;
  u->lc = v->rc;
  u->lc->parent = u;
  u->parent = v;
  v->rc = u;
  v->parent = p;
}

static void
avl_node_rotate_left (avl_node *v)
{
  avl_node *p = v->parent, *u = v->rc;
  if (v == p->lc) p->lc = u;
  else p->rc = u;
  v->rc = u->lc;
  u->rc->parent = v;
  v->parent = u;
  u->lc = v;
  u->parent = p;
}

/* g -> p -> v -> (x) */
static void
avl_node_rotate_at (avl_node *v)
{
  avl_node *p = v->parent, *g = p->parent;
  if (p == g->lc)
    {
      /* LL  */
      if (v == p->lc)
        avl_node_rotate_right (g);
      /* LR */
      else /* v == p->rc */
        {
          avl_node_rotate_left (p);
          avl_node_rotate_right (g);
        }
    }
  else /* p == g->rc */
    {
      /* RL */
      if (v == p->lc)
        {
          avl_node_rotate_right (p);
          avl_node_rotate_left (g);
        }
      /* RR */
      else /* v == p->rc */
        avl_node_rotate_right (g);
    }
}

static avl_node *
taller_child (const avl_node *x)
{
  if (x->balance_factor > 0)
    return x->lc;
  else if (x->balance_factor < 0)
    return x->rc;
  else /* x->balance_factor == 0 */
    return x == x->parent->lc ? x->lc : x->rc;
}
