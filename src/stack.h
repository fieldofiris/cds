#ifndef CDS_STACK_H
#define CDS_STACK_H

#include "lallocator.h"

typedef struct {
  LinearAllocator linear_allocator;
  size_t element_size;
  size_t stack_size;
  size_t capacity;
} Stack;

#define create_stack(type, capacity) ((Stack){.linear_allocator = create_arena(capacity * sizeof(type)), .element_size = sizeof(type), .stack_size = 0, capacity})
void free_stack(Stack* stack);

size_t stack_size(Stack* stack);
size_t stack_capacity(Stack* stack);

void stack_push(Stack* stack, void* element_ptr);

void stack_pop(Stack* stack);
void stack_clear(Stack* stack);

#endif