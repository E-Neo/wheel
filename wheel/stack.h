#ifndef _STACK_H
#define _STACK_H

#include <stddef.h>

#define STACK_DEFAULT_CAPACITY (64)

typedef struct stack stack;

struct stack
{
  void *data;
  size_t len;
  size_t _size, _capacity;
};

/* Using a dynamic array, the stack can grow as much as needed,
   while it will not shrink in consideration of efficiency.
   And we do not check stack underflow because we think it is user's
   responsibility. So be careful when using stack_top(), stack_pop()
   or stack_at().  */
extern stack *stack_new (size_t _size);
extern stack *stack_new_with_capacity (size_t _size, size_t _capacity);
extern stack *stack_copy (const stack *s);
extern void stack_free (stack *s);
extern void stack_push (stack *s, const void *x);
extern void stack_pop (stack *s);
extern void *stack_top (const stack *s);
extern void *stack_at (const stack *s, size_t n);

#endif
