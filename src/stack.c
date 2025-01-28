#include "stack.h"

#include "assert.h"
#include "string.h"

void free_stack(Stack* stack) {
  assert(stack);
  free_arena(&stack->linear_allocator);
  stack->element_size = 0;
  stack->stack_size = 0;
  stack->capacity = 0;
  stack = NULL;
}

size_t stack_size(Stack* stack) {
  assert(stack);
  return stack->stack_size;
}

size_t stack_capacity(Stack* stack) {
  assert(stack);
  return stack->capacity;
}

void stack_push(Stack* stack, void* element_ptr) {
  assert(stack);
  assert(element_ptr);
  void* push_pos = cds_lalloc(&stack->linear_allocator, stack->element_size);
  assert(push_pos);
  memcpy(push_pos, element_ptr, stack->element_size);
  stack->stack_size += 1;
  stack->capacity = stack->linear_allocator.size / stack->element_size;
}

void stack_pop(Stack* stack) {
  assert(stack);
  assert(stack->stack_size > 0);
  stack->linear_allocator.current = (char*)stack->linear_allocator.current - stack->element_size;
  memset(stack->linear_allocator.current, 0, stack->element_size);
  stack->stack_size -= 1;
}

void stack_clear(Stack* stack) {
  assert(stack);
  memset(stack->linear_allocator.start, 0, stack->linear_allocator.size);
  stack->linear_allocator.current = stack->linear_allocator.start;
  stack->stack_size = 0;
}