#include <string.h>
#include "binary_tree.h"
#include "memory.h"

extern binary_tree *
binary_tree_new (size_t _size)
{
  binary_tree *T = alloc_func (sizeof (binary_tree));
  T->root = NULL;
  T->n = 0;
  T->_size = _size;
  return T;
}

static size_t
bin_node_free (bin_node *node, size_t n)
{
  if (node == NULL) return 0;
  bin_node **stack = alloc_func (((n + 1) >> 1) * sizeof (bin_node *));
  size_t len = 0, count = 0;
  stack[len++] = node;
  while (len)
    {
      node = stack[--len];
      if (node->rc) stack[len++] = node->rc;
      if (node->lc) stack[len++] = node->lc;
      free_func (node->data);
      free_func (node);
      count++;
    }
  free_func (stack);
  return count;
}

/* Time: O(n)
   Space: O(n)  */
extern void
binary_tree_free (binary_tree *T)
{
  bin_node_free (T->root, T->n);
  free_func (T);
}

/* Time: O(n)
   Size: O(n)  */
extern size_t
binary_tree_height (const binary_tree *T)
{
  bin_node *node = T->root;
  if (node == NULL) return 0;
  bin_node **queue = alloc_func (T->n * sizeof (bin_node *));
  size_t front = 0, rear = 0;
  queue[rear++] = node;
  size_t new_level = 1, height = 0;
  while (front < rear)
    {
      node = queue[front++];
      if (node->lc) queue[rear++] = node->lc;
      if (node->rc) queue[rear++] = node->rc;
      if (front == new_level)
        {
          height++;
          new_level = rear;
        }
    }
  free_func (queue);
  return height;
}

/* Time: O(n)
   Space: O(n)  */
extern size_t
binary_tree_width (const binary_tree *T)
{
  bin_node *node = T->root;
  if (node == NULL) return 0;
  bin_node **queue = alloc_func (T->n * sizeof (bin_node *));
  size_t front = 0, rear = 0;
  queue[rear++] = node;
  size_t new_level = 1, width = 0;
  while (front < rear)
    {
      node = queue[front++];
      if (node->lc) queue[rear++] = node->lc;
      if (node->rc) queue[rear++] = node->rc;
      if (front == new_level)
        {
          size_t tmp = rear - front;
          if (tmp > width) width = tmp;
          new_level = rear;
        }
    }
  free_func (queue);
  return width;
}

/* Time: O(n)
   Space: O(n)  */
extern int
binary_tree_complete_p (const binary_tree *T)
{
  bin_node *node = T->root;
  bin_node **queue = alloc_func ((2 * T->n + 1) * sizeof (bin_node *));
  size_t front = 0, rear = 0;
  queue[rear++] = node;
  while (front < rear)
    {
      node = queue[front++];
      if (node)
        {
          queue[rear++] = node->lc;
          queue[rear++] = node->rc;
        }
      else  /* node == NULL */
        while (front < rear)
          if (queue[front++])
            {
              free_func (queue);
              return 0;
            }
    }
  free_func (queue);
  return 1;
}

/* Time: O(1)
   Space: O(1)  */
extern void
binary_tree_insert (binary_tree *T, bin_node *parent, int rc, const void *data)
{
  bin_node *node = alloc_func (sizeof (bin_node));
  node->data = alloc_func (T->_size);
  memcpy (node->data, data, T->_size);
  node->parent = parent; node->lc = NULL; node->rc = NULL;
  T->n++;
  if (parent == NULL) { T->root = node; return; }
  if (rc) parent->rc = node;
  else parent->lc = node;
}

/* Time: O(n)
   Space: O(n) */
extern void
binary_tree_remove (binary_tree *T, bin_node *posi)
{
  if (posi == T->root)
    {
      T->n -= bin_node_free (posi, T->n);
      T->root = NULL;
    }
  else
    {
      bin_node *parent = posi->parent;
      if (parent->lc == posi)
        parent->lc = NULL;
      else
        parent->rc = NULL;
      T->n -= bin_node_free (posi, T->n);
    }
}

/* Time: O(n)
   Space: O(n)  */
static void
bin_node_bfs (bin_node *node, size_t n,
              void (*visit) (void *, void *),
              void *arg)
{
  if (node == NULL) return;
  bin_node **queue = alloc_func (n * sizeof (bin_node *));
  size_t front = 0, rear = 0;
  queue[rear++] = node;
  while (front < rear)
    {
      node = queue[front++];
      visit (node->data, arg);
      if (node->lc) queue[rear++] = node->lc;
      if (node->rc) queue[rear++] = node->rc;
    }
  free_func (queue);
}

extern void
binary_tree_bfs (binary_tree *T,
                 void (*visit) (void *, void *),
                 void *arg)
{
  bin_node_bfs (T->root, T->n, visit, arg);
}

/* Time: O(n)
   Space: O(n)  */
static void
bin_node_dfs_preorder (bin_node *node, size_t n,
                       void (*visit) (void *, void *),
                       void *arg)
{
  if (node == NULL) return;
  bin_node **stack = alloc_func (((n + 1) >> 1) * sizeof (bin_node *));
  size_t len = 0;
  stack[len++] = node;
  while (len)
    {
      node = stack[--len];
      visit (node->data, arg);
      if (node->rc) stack[len++] = node->rc;
      if (node->lc) stack[len++] = node->lc;
    }
  free_func (stack);
}

extern void
binary_tree_dfs_preorder (binary_tree *T,
                          void (*visit) (void *, void *),
                          void *arg)
{
  bin_node_dfs_preorder (T->root, T->n, visit, arg);
}

/* Time: O(n)
   Space: O(n)  */
static void
bin_node_dfs_inorder (bin_node *node, size_t n,
                      void (*visit) (void *, void *),
                      void *arg)
{
  bin_node **stack = alloc_func (n * sizeof (bin_node *));
  size_t len = 0;
  while (1)
    {
      if (node)
        {
          stack[len++] = node;
          node = node->lc;
        }
      else if (len)
        {
          node = stack[--len];
          visit (node->data, arg);
          node = node->rc;
        }
      else
        break;
    }
  free_func (stack);
}

extern void
binary_tree_dfs_inorder (binary_tree *T,
                         void (*visit) (void *, void *),
                         void *arg)
{
  bin_node_dfs_inorder (T->root, T->n, visit, arg);
}

/* Time: O(n)
   Space: O(n)  */
static void
bin_node_dfs_postorder (bin_node *node, size_t n,
                        void (*visit) (void *, void *),
                        void *arg)
{
  bin_node **stack = alloc_func (n * sizeof (bin_node *));
  size_t len = 0;
  bin_node *latest_visited = NULL;
  while (1)
    {
      if (node)
        {
          stack[len++] = node;
          node = node->lc;
        }
      else if (len)
        {
          node = stack[len - 1];
          if (node->rc && node->rc != latest_visited)
            {
              node = node->rc;
              stack[len++] = node;
              node = node->lc;
            }
          else
            {
              node = stack[--len];
              visit (node->data, arg);
              latest_visited = node;
              node = NULL;
            }
        }
      else
        break;
    }
  free_func (stack);
}

extern void
binary_tree_dfs_postorder (binary_tree *T,
                           void (*visit) (void *, void *),
                           void *arg)
{
  bin_node_dfs_postorder (T->root, T->n, visit, arg);
}

/* Time: O(1)
   Space: O(1)  */
extern bin_node *
binary_tree_bfs_front (const binary_tree *T)
{
  return T->root;
}

/* Time: O(n)
   Space: O(n)  */
extern bin_node *
binary_tree_bfs_back (const binary_tree *T)
{
  if (T->root == NULL) return NULL;
  bin_node **queue = alloc_func (T->n * sizeof (bin_node *));
  size_t front = 0, rear = 0;
  bin_node *node = T->root;
  queue[rear++] = node;
  while (front < rear)
    {
      node = queue[front++];
      if (node->lc) queue[rear++] = node->lc;
      if (node->rc) queue[rear++] = node->rc;
    }
  free_func (queue);
  return node;
}

/* Time: O(n)
   Space: O(n)  */
extern bin_node *
binary_tree_bfs_next (const binary_tree *T, const bin_node *posi)
{
  bin_node *node = T->root;
  if (node == NULL) return NULL;
  bin_node **queue = alloc_func (T->n * sizeof (bin_node *));
  size_t front = 0, rear = 0;
  bin_node *latest_visited = NULL;
  queue[rear++] = node;
  while (front < rear)
    {
      node = queue[front++];
      if (latest_visited == posi)
        {
          free_func (queue);
          return node;
        }
      if (node->lc) queue[rear++] = node->lc;
      if (node->rc) queue[rear++] = node->rc;
      latest_visited = node;
    }
  free_func (queue);
  return NULL;
}

/* Time: O(n)
   Space: O(n)  */
extern bin_node *
binary_tree_bfs_prev (const binary_tree *T, const bin_node *posi)
{
  bin_node *node = T->root;
  if (node == NULL) return NULL;
  bin_node **queue = alloc_func (T->n * sizeof (bin_node *));
  size_t front = 0, rear = 0;
  bin_node *latest_visited = NULL;
  queue[rear++] = node;
  while (front < rear)
    {
      bin_node *node = queue[front++];
      if (node == posi)
        {
          free_func (queue);
          return latest_visited;
        }
      if (node->lc) queue[rear++] = node->lc;
      if (node->rc) queue[rear++] = node->rc;
      latest_visited = node;
    }
  free_func (queue);
  return latest_visited;
}

/* Time: O(1)
   Space: O(1)  */
extern bin_node *
binary_tree_dfs_preorder_front (const binary_tree *T)
{
  return T->root;
}

/* Time: O(n)
   Space: O(1)  */
extern bin_node *
binary_tree_dfs_preorder_back (const binary_tree *T)
{
  bin_node *node = T->root;
  if (node == NULL) return NULL;
  while (1)
    {
      if (node->rc)
        node = node->rc;
      else if (node->lc)
        node = node->lc;
      else
        return node;
    }
}

/* Time: O(n)
   Space: O(1)  */
extern bin_node *
binary_tree_dfs_preorder_next (const binary_tree *T, const bin_node *posi)
{
  if (posi == NULL) return NULL;
  if (posi->lc) return posi->lc;
  if (posi->rc) return posi->rc;
  while (1)
    {
      bin_node *parent = posi->parent;
      if (parent == NULL)
        return NULL;
      else if (parent->rc == NULL || parent->rc == posi)
        posi = parent;
      else
        return parent->rc;
    }
}

/* Time: O(n)
   Space: O(1)  */
extern bin_node *
binary_tree_dfs_preorder_prev (const binary_tree *T, const bin_node *posi)
{
  if (posi == NULL) return NULL;
  bin_node *parent = posi->parent;
  if (parent == NULL || parent->lc == NULL || parent->lc == posi)
    return parent;
  posi = parent->lc;
  while (1)
    {
      if (posi->rc)
        posi = posi->rc;
      else if (posi->lc)
        posi = posi->lc;
      else
        return (bin_node *) posi;
    }
}

/* Time: O(n)
   Space: O(1)  */
extern bin_node *
binary_tree_dfs_inorder_front (const binary_tree *T)
{
  bin_node *node = T->root;
  if (node == NULL) return NULL;
  while (node->lc) node = node->lc;
  return node;
}

/* Time: O(n)
   Space: O(1)  */
extern bin_node *
binary_tree_dfs_inorder_back (const binary_tree *T)
{
  bin_node *node = T->root;
  if (node == NULL) return NULL;
  while (node->rc) node = node->rc;
  return node;
}

/* Time: O(n)
   Space: O(1)  */
extern bin_node *
binary_tree_dfs_inorder_next (const binary_tree *T, const bin_node *posi)
{
  if (posi == NULL) return NULL;
  if (posi->rc)
    {
      posi = posi->rc;
      while (posi->lc) posi = posi->lc;
    }
  else
    {
      bin_node *parent;
      while ((parent = posi->parent) && parent->rc == posi)
        posi = parent;
      posi = posi->parent;
    }
  return (bin_node *) posi;
}

/* Time: O(n)
   Space: O(1)  */
extern bin_node *
binary_tree_dfs_inorder_prev (const binary_tree *T, const bin_node *posi)
{
  if (posi == NULL) return NULL;
  if (posi->lc)
    {
      posi = posi->lc;
      while (posi->rc) posi = posi->rc;
    }
  else
    {
      bin_node *parent;
      while ((parent = posi->parent) && parent->lc == posi)
        posi = parent;
      posi = posi->parent;
    }
  return (bin_node *) posi;
}

/* Time: O(n)
   Space: O(1)  */
extern bin_node *
binary_tree_dfs_postorder_front (const binary_tree *T)
{
  bin_node *node = T->root;
  if (node == NULL) return NULL;
  while (1)
    {
      if (node->lc)
        node = node->lc;
      else if (node->rc)
        node = node->rc;
      else
        return node;
    }
}

/* Time: O(1)
   Space: O(1)  */
extern bin_node *
binary_tree_dfs_postorder_back (const binary_tree *T)
{
  return T->root;
}

/* Time: O(n)
   Space: O(1)  */
extern bin_node *
binary_tree_dfs_postorder_next (const binary_tree *T, const bin_node *posi)
{
  if (posi == NULL) return NULL;
  bin_node *parent = posi->parent;
  if (parent == NULL || parent->rc == NULL || parent->rc == posi)
    return parent;
  posi = parent->rc;
  while (1)
    {
      if (posi->lc)
        posi = posi->lc;
      else if (posi->rc)
        posi = posi->rc;
      else
        return (bin_node *) posi;
    }
}

/* Time: O(n)
   Space: O(1)  */
extern bin_node *
binary_tree_dfs_postorder_prev (const binary_tree *T, const bin_node *posi)
{
  if (posi == NULL) return NULL;
  if (posi->rc) return posi->rc;
  if (posi->lc) return posi->lc;
  while (1)
    {
      bin_node *parent = posi->parent;
      if (parent == NULL)
        return NULL;
      else if (parent->lc == NULL || parent->lc == posi)
        posi = parent;
      else
        return parent->lc;
    }
}
