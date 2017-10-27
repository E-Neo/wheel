#include "binary_tree.h"
#include "queue.h"
#include "stack.h"
#include "memory.h"

extern bin_node *
bin_node_new (const void *data, const bin_node *parent,
              const bin_node *lc, const bin_node *rc)
{
  bin_node *node = alloc_func (sizeof (bin_node));
  node->data = (void *) data;
  node->parent = (void *) parent;
  node->lc = (void *) lc;
  node->rc = (void *) rc;
  return node;
}

/* Time: O(n)
   Space: O(n)  */
extern void
bin_node_free (bin_node *node)
{
  stack *s = stack_new(sizeof (bin_node *));
  stack_push (s, &node);
  while (s->len)
    {
      bin_node **t = stack_top (s); node = *t; stack_pop (s);
      if (node->rc) stack_push (s, &node->rc);
      if (node->lc) stack_push (s, &node->lc);
      free_func (node->data);
      free_func (node);
    }
  stack_free (s);
}

/* Time: O(n)
   Space: O(n)  */
extern bin_node *
bin_node_bfs (bin_node *node, int (*visit) (bin_node *))
{
  queue *q = queue_new (sizeof (bin_node *));
  queue_enqueue (q, &node);
  while (q->len)
    {
      bin_node **t = queue_front (q); node = *t; queue_dequeue (q);
      if (0 == visit (node))
        {
          queue_free (q);
          return node;
        }
      if (node->lc) queue_enqueue (q, &node->lc);
      if (node->rc) queue_enqueue (q, &node->rc);
    }
  queue_free (q);
  return NULL;
}

/* Time: O(n)
   Space: O(n)  */
extern bin_node *
bin_node_dfs_preorder (bin_node *node, int (*visit) (bin_node *))
{
  stack *s = stack_new (sizeof (bin_node *));
  stack_push (s, &node);
  while (s->len)
    {
      bin_node **t = stack_top (s); node = *t; stack_pop (s);
      if (0 == visit (node))
        {
          stack_free (s);
          return node;
        }
      if (node->rc) stack_push (s, &node->rc);
      if (node->lc) stack_push (s, &node->lc);
    }
  stack_free (s);
  return NULL;
}

/* Time: O(n)
   Space: O(n)  */
/* extern bin_node * */
/* bin_node_dfs_inorder (bin_node *node, int (*visit) (bin_node *)) */
/* { */
/*   if (NULL == node) return NULL; */
/*   bin_node *tmp = bin_node_dfs_inorder (node->lc, visit); */
/*   if (tmp) return tmp; */
/*   if (0 == visit (node)) return node; */
/*   return bin_node_dfs_inorder (node->rc, visit); */
/* } */
extern bin_node *
bin_node_dfs_inorder (bin_node *node, int (*visit) (bin_node *))
{
  stack *s = stack_new (sizeof (bin_node *));
  while (1)
    {
      while (node)
        {
          stack_push (s, &node);
          node = node->lc;
        }
      if (s->len == 0)
        {
          stack_free (s);
          return NULL;
        }
      bin_node **tmp = stack_top (s); node = *tmp; stack_pop (s);
      if (0 == visit (node))
        {
          stack_free (s);
          return node;
        }
      node = node->rc;
    }
}

/* Time: O(n)
   Space: O(n)  */
/* extern bin_node * */
/* bin_node_dfs_postorder (bin_node *node, int (*visit) (bin_node *)) */
/* { */
/*   if (NULL == node) return NULL; */
/*   bin_node *tmp; */
/*   if ((tmp = bin_node_dfs_postorder (node->lc, visit)) */
/*       || (tmp = bin_node_dfs_postorder (node->rc, visit))) */
/*     return tmp; */
/*   return 0 == visit (node) ? node : NULL; */
/* } */
extern bin_node *
bin_node_dfs_postorder (bin_node *node, int (*visit) (bin_node *))
{
  stack *s = stack_new (sizeof (bin_node *));
  stack_push (s, &node);
  while (s->len)
    {
      bin_node **tmp = stack_top (s);
      if (node->parent != *tmp)
        {
          while ((node = *tmp))
            {
              if (node->lc)
                {
                  if (node->rc) stack_push (s, &node->rc);
                  stack_push (s, &node->lc);
                }
              else
                stack_push (s, &node->rc);
              tmp = stack_top (s);
            }
          stack_pop (s);  /* pop NULL */
        }
      tmp = stack_top (s); node = *tmp; stack_pop (s);
      if (0 == visit (node))
        {
          stack_free (s);
          return node;
        }
    }
  stack_free (s);
  return NULL;
}

/* Time: O(1)
   Space: O(1)  */
extern bin_node *
bin_node_bfs_front (const bin_node *node)
{
  return (bin_node *) node;
}

/* Time: O(n)
   Space: O(n)  */
extern bin_node *
bin_node_bfs_back (const bin_node *node)
{
  queue *q = queue_new (sizeof (bin_node *));
  queue_enqueue (q, &node);
  while (q->len)
    {
      bin_node **t = queue_front (q); node = *t; queue_dequeue (q);
      if (node->lc) queue_enqueue (q, &node->lc);
      if (node->rc) queue_enqueue (q, &node->rc);
    }
  return (bin_node *) node;
}

/* Time: O(1)
   Space: O(1)  */
extern bin_node *
bin_node_dfs_preorder_front (const bin_node *node)
{
  return (bin_node *) node;
}

/* Time: O(n)
   Space: O(1)  */
extern bin_node *
bin_node_dfs_preorder_back (const bin_node *node)
{
  while (1)
    {
      if (node->rc)
        node = node->rc;
      else if (node->lc)
        node = node->lc;
      else
        return (bin_node *) node;
    }
}

/* Time: O(n)
   Space: O(1)  */
extern bin_node *
bin_node_dfs_preorder_next (const bin_node *node)
{
  if (node->lc) return node->lc;
  if (node->rc) return node->rc;
  bin_node *parent;
  while ((parent = node->parent)
         && (parent->rc == NULL ||  parent->rc == node))
    node = parent;
  return parent ? parent->rc : NULL;
}

/* Time: O(n)
   Space: O(1)  */
extern bin_node *
bin_node_dfs_preorder_prev (const bin_node *node)
{
  bin_node *parent;
  if ((parent = node->parent) == NULL) return NULL;
  if (node == parent->lc || parent->lc == NULL)
    return parent;
  else
    return bin_node_dfs_preorder_back (parent->lc);
}

/* Time: O(n)
   Space: O(1)  */
extern bin_node *
bin_node_dfs_inorder_front (const bin_node *node)
{
  while (node->lc) node = node->lc;
  return (bin_node *) node;
}

/* Time: O(n)
   Space: O(1)  */
extern bin_node *
bin_node_dfs_inorder_back (const bin_node *node)
{
  while (node->rc) node = node->rc;
  return (bin_node *) node;
}

/* Time: O(n)
   Space: O(1)  */
extern bin_node *
bin_node_dfs_inorder_next (const bin_node *node)
{
  if (node->rc)  /* then: node = bin_node_dfs_inorder_front (node->rc);  */
    {
      node = node->rc;
      while (node->lc) node = node->lc;
    }
  else
    {
      while (node->parent && node == node->parent->rc) node = node->parent;
      node = node->parent;
    }
  return (bin_node *) node;
}

/* Time: O(n)
   Space: O(1)  */
extern bin_node *
bin_node_dfs_inorder_prev (const bin_node *node)
{
  if (node->lc)  /* then: node = bin_node_dfs_inorder_back (node->lc);  */
    {
      node = node->lc;
      while (node->rc) node = node->rc;
    }
  else
    {
      while (node->parent && node == node->parent->lc) node = node->parent;
      node = node->parent;
    }
  return (bin_node *) node;
}

/* Time: O(n)
   Space: O(1)  */
extern bin_node *
bin_node_dfs_postorder_front (const bin_node *node)
{
  while (1)
    {
      if (node->lc)
        node = node->lc;
      else if (node->rc)
        node = node->rc;
      else
        return (bin_node *) node;
    }
}

/* Time: O(1)
   Space: O(1)  */
extern bin_node *
bin_node_dfs_postorder_back (const bin_node *node)
{
  return (bin_node *) node;
}

/* Time: O(n)
   Space: O(1)  */
extern bin_node *
bin_node_dfs_postorder_next (const bin_node *node)
{
  bin_node *parent;
  if ((parent = node->parent) == NULL) return NULL;
  if (node == parent->rc || parent->rc == NULL)
    return parent;
  else
    return bin_node_dfs_postorder_front (parent->rc);
}

/* Time: O(n)
   Space: O(1)  */
extern bin_node *
bin_node_dfs_postorder_prev (const bin_node *node)
{
  if (node->rc) return node->rc;
  if (node->lc) return node->lc;
  bin_node *parent;
  while ((parent = node->parent)
         && (parent->lc == NULL || node == parent->lc))
    node = parent;
  return parent ? parent->lc : NULL;
}
