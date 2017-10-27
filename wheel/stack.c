#include <string.h>
#include "stack.h"
#include "memory.h"

extern stack *
stack_new_with_capacity (size_t _size, size_t _capacity)
{
  stack *s = alloc_func (sizeof (stack));
  s->data = alloc_func (_size * _capacity);
  s->len = 0; s->_size = _size; s->_capacity = _capacity;
  return s;
}

extern stack *
stack_new (size_t _size)
{
  return stack_new_with_capacity (_size, STACK_DEFAULT_CAPACITY);
}

extern void
stack_free (stack *s)
{
  free_func (s->data);
  free_func (s);
}

extern void
stack_push (stack *s, const void *x)
{
  if (s->len == s->_capacity - 1)
    {
      size_t capacity = s->_capacity << 1;
      s->data = realloc_func (s->data, capacity * s->_size);
      s->_capacity = capacity;
    }
  memcpy ((char *) s->data + s->len++ * s->_size, x, s->_size);
}

extern void *
stack_top (const stack *s)
{
  return (char *) s->data + (s->len - 1) * s->_size;
}

extern void
stack_pop (stack *s)
{
  s->len--;
}

extern void *
stack_at (const stack *s, size_t n)
{
  return (char *) s->data + n * s->_size;
}
