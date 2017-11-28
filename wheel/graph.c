#include <string.h>
#include "graph.h"
#include "memory.h"
#include "vector.h"
#include "list.h"
#include "bit_array.h"

struct _internal
{
  vector *nodes;
  vector *edges;
  size_t _node_posi, _edge_posi;
};

struct node_vector_element
{
  void *data;
  char valid;
  list *nbr;
};

struct edge_vector_element
{
  void *data;
  char valid;
};

struct node_nbr_element
{
  graph_node node;
  size_t edge;
};

extern graph *
graph_new (size_t _size, size_t _node_size, size_t _edge_size)
{
  graph *G = alloc_func (sizeof (graph));
  G->data = alloc_func (_size);
  G->n = 0; G->e = 0;
  G->_internal = alloc_func (sizeof (struct _internal));
  G->_internal->nodes = vector_new (sizeof (struct node_vector_element));
  G->_internal->edges = vector_new (sizeof (struct edge_vector_element));
  G->_internal->_node_posi = 0; G->_internal->_edge_posi = 0;
  G->_size = _size; G->_node_size = _node_size; G->_edge_size = _edge_size;
  return G;
}

extern void
graph_free (graph *G)
{
  free_func (G->data);
  vector_foreach (G->_internal->nodes, elem, 0, G->_internal->nodes->len)
    if (((struct node_vector_element *) elem)->valid)
      {
        free_func (((struct node_vector_element *) elem)->data);
        list_free (((struct node_vector_element *) elem)->nbr);
      }
  vector_free (G->_internal->nodes);
  vector_foreach (G->_internal->edges, elem, 0, G->_internal->edges->len)
    if (((struct edge_vector_element *) elem)->valid)
      free_func (((struct edge_vector_element *) elem)->data);
  vector_free (G->_internal->edges);
  free_func (G->_internal);
  free_func (G);
}

extern int
graph_have_node_p (const graph *G, graph_node node)
{
  if (node >= G->_internal->nodes->len) return 0;
  struct node_vector_element *nve = vector_at (G->_internal->nodes, node);
  return nve->valid;
}

extern int
graph_have_edge_p (const graph *G, graph_node u, graph_node v)
{
  if (graph_have_node_p (G, u) && graph_have_node_p (G, v))
    {
      struct node_vector_element *nve = vector_at (G->_internal->nodes, u);
      list_foreach (nve->nbr, lst_node, nve->nbr->head->next, nve->nbr->tail)
        {
          struct node_nbr_element *nne = lst_node->data;
          if (nne->node == v) return 1;
        }
    }
  return 0;
}

extern void *
graph_at_node (const graph *G, graph_node node)
{
  struct node_vector_element *nve = vector_at (G->_internal->nodes, node);
  return nve->data;
}

extern void *
graph_at_edge (const graph *G, graph_node u, graph_node v)
{
  struct node_vector_element *nve = vector_at (G->_internal->nodes, u);
  list_foreach (nve->nbr, lst_node, nve->nbr->head->next, nve->nbr->tail)
    {
      struct node_nbr_element *nne = lst_node->data;
      if (nne->node == v)
        {
          struct edge_vector_element *eve
            = vector_at (G->_internal->edges, nne->edge);
          return eve->data;
        }
    }
  return NULL;
}

extern graph_node
graph_insert_node (graph *G, const void *data)
{
  graph_node node = G->_internal->_node_posi;
  if (node == G->_internal->nodes->len)
    {
      struct node_vector_element nve;
      nve.data = alloc_func (G->_node_size);
      memcpy (nve.data, data, G->_node_size);
      nve.nbr = list_new (sizeof (struct node_nbr_element));
      nve.valid = 1;
      vector_insert (G->_internal->nodes, node, &nve, 1);
      G->_internal->_node_posi++;
    }
  else
    {
      struct node_vector_element *nve = vector_at (G->_internal->nodes, node);
      nve->data = alloc_func (G->_node_size);
      memcpy (nve->data, data, G->_node_size);
      nve->nbr = list_new (sizeof (struct node_nbr_element));
      nve->valid = 1;
      vector_foreach (G->_internal->nodes, elem,
                      node, G->_internal->nodes->len)
        {
          if (!((struct node_vector_element *) elem)->valid) break;
          G->_internal->_node_posi++;
        }
    }
  G->n++;
  return node;
}

extern void
graph_insert_edge (graph *G, graph_node u, graph_node v, const void *data)
{
  size_t edge = G->_internal->_edge_posi;
  if (edge == G->_internal->edges->len)
    {
      struct edge_vector_element eve;
      eve.data = alloc_func (G->_edge_size);
      memcpy (eve.data, data, G->_edge_size);
      eve.valid = 1;
      vector_insert (G->_internal->edges, edge, &eve, 1);
      G->_internal->_edge_posi++;
    }
  else
    {
      struct edge_vector_element *eve = vector_at (G->_internal->edges, edge);
      eve->data = alloc_func (G->_edge_size);
      memcpy (eve->data, data, G->_edge_size);
      eve->valid = 1;
      vector_foreach (G->_internal->edges, elem,
                      edge, G->_internal->edges->len)
        {
          if (!((struct edge_vector_element *) elem)->valid) break;
          G->_internal->_edge_posi++;
        }
    }
  struct node_vector_element *u_eve = vector_at (G->_internal->nodes, u);
  struct node_nbr_element nne;
  nne.edge = edge;
  nne.node = v;
  list_insert (u_eve->nbr, u_eve->nbr->tail, &nne, 1);
  struct node_vector_element *v_eve = vector_at (G->_internal->nodes, v);
  nne.node = u;
  list_insert (v_eve->nbr, v_eve->nbr->tail, &nne, 1);
  G->e++;
}

extern void
graph_remove_node (graph *G, graph_node node)
{
  struct node_vector_element *nve = vector_at (G->_internal->nodes, node);
  list_foreach (nve->nbr, lst_node, nve->nbr->head->next, nve->nbr->tail)
    {
      struct node_nbr_element *nne = lst_node->data;
      struct node_vector_element *v_nve
        = vector_at (G->_internal->nodes, nne->node);
      list_foreach (v_nve->nbr, lst_node,
                    v_nve->nbr->head->next, v_nve->nbr->tail)
        {
          struct node_nbr_element *v_nne = lst_node->data;
          if (v_nne->node == node)
            {
              list_remove (v_nve->nbr, lst_node, 1);
              break;
            }
        }
      struct edge_vector_element *eve
        = vector_at (G->_internal->edges, nne->edge);
      free_func (eve->data);
      eve->valid = 0;
      if (nne->edge < G->_internal->_edge_posi)
        G->_internal->_edge_posi = nne->edge;
      G->e--;
    }
  list_free (nve->nbr);
  free_func (nve->data);
  nve->valid = 0;
  if (node < G->_internal->_node_posi)
    G->_internal->_node_posi = node;
  G->n--;
}

extern void
graph_remove_edge (graph *G, graph_node u, graph_node v)
{
  struct node_vector_element *nve = vector_at (G->_internal->nodes, u);
  list_foreach (nve->nbr, lst_node, nve->nbr->head->next, nve->nbr->tail)
    {
      struct node_nbr_element *nne = lst_node->data;
      if (nne->node == v)
        {
          list_remove (nve->nbr, lst_node, 1);
          break;
        }
    }
  nve = vector_at (G->_internal->nodes, v);
  list_foreach (nve->nbr, lst_node, nve->nbr->head->next, nve->nbr->tail)
    {
      struct node_nbr_element *nne = lst_node->data;
      if (nne->node == u)
        {
          G->_internal->_edge_posi = nne->edge;
          list_remove (nve->nbr, lst_node, 1);
          break;
        }
    }
  struct edge_vector_element *eve
    = vector_at (G->_internal->edges, G->_internal->_edge_posi);
  free_func (eve->data);
  eve->valid = 0;
  G->e--;
}

extern const void *
graph_node_next (const graph *G, const void *idx, graph_node *node)
{
  vector *node_vec = G->_internal->nodes;
  const void *begin = node_vec->data;
  const void *end = node_vec->data + node_vec->len * node_vec->_size;
  idx = idx ? (char *) idx + node_vec->_size : begin;
  while ((idx < end && !((struct node_vector_element *) idx)->valid))
    idx = (char *) idx + node_vec->_size;
  if (idx != end)
    {
      *node = (idx - begin) / node_vec->_size;
      return idx;
    }
  else
    return NULL;
}

extern const void *
graph_node_nbr_next (const graph *G, graph_node node,
                     const void *idx, graph_node *nbr)
{
  struct node_vector_element *nve = vector_at (G->_internal->nodes, node);
  list *adj_lst = nve->nbr;
  idx = idx ? ((list_node *) idx)->next : adj_lst->head->next;
  if ((list_node *) idx != adj_lst->tail)
    {
      *nbr = ((struct node_nbr_element *) ((list_node *)idx)->data)->node;
      return idx;
    }
  else
    return NULL;
}

typedef bit_array node_set;

static node_set *
node_set_new (const graph *G)
{
  bit_array *ns = bit_array_new (G->_internal->nodes->len);
  return ns;
}

static void
node_set_free (node_set *ns)
{
  bit_array_free (ns);
}

static void
node_set_insert (node_set *ns, graph_node node)
{
  bit_array_set (ns, node);
}

static int
node_set_in_p (const node_set *ns, graph_node node)
{
  return bit_array_test (ns, node);
}

extern void
graph_bfs (graph *G, graph_node s,
           void (*visit) (graph_node, void *, void *), void *arg)
{
  node_set *discovered = node_set_new (G);
  graph_node *queue = alloc_func (G->n * sizeof (graph_node));
  size_t front = 0, rear = 0;
  queue[rear++] = s;
  node_set_insert (discovered, s);
  while (front < rear)
    {
      s = queue[front++];
      graph_node_nbr_foreach (G, s, nbr)
        if (!node_set_in_p (discovered, nbr))
          {
            queue[rear++] = nbr;
            node_set_insert (discovered, nbr);
          }
      visit (s, graph_at_node (G, s), arg);
    }
  node_set_free (discovered);
  free_func (queue);
}

extern void
graph_dfs_preorder (graph *G, graph_node s,
                    void (*visit) (graph_node, void *, void *), void *arg)
{
  node_set *discovered = node_set_new (G);
  graph_node *stack = alloc_func (G->n * sizeof (graph_node));
  size_t top = 0;
  stack[top++] = s;
  node_set_insert (discovered, s);
  while (top)
    {
      s = stack[--top];
      visit (s, graph_at_node (G, s), arg);
      graph_node_nbr_foreach (G, s, nbr)
        if (!node_set_in_p (discovered, nbr))
          {
            stack[top++] = nbr;
            node_set_insert (discovered, nbr);
          }
    }
  node_set_free (discovered);
  free_func (stack);
}
