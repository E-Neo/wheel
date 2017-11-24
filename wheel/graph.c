#include <string.h>
#include "graph.h"
#include "memory.h"
#include "vector.h"
#include "list.h"

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
  G->_size = 0; G->_node_size = 0; G->_edge_size = 0;
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
          G->_internal->_node_posi++;
          if (!((struct node_vector_element *) elem)->valid) break;
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
          G->_internal->_edge_posi++;
          if (!((struct edge_vector_element *) elem)->valid) break;
        }
    }
  struct node_vector_element *u_eve = vector_at (G->_internal->nodes, u);
  struct node_nbr_element nne;
  nne.edge = edge;
  nne.node = v;
  list_insert (u_eve->nbr, u_eve->nbr->head->next, &nne, 1);
  struct node_vector_element *v_eve = vector_at (G->_internal->nodes, v);
  nne.node = u;
  list_insert (v_eve->nbr, v_eve->nbr->head->next, &nne, 1);
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
