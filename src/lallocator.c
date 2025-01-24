#include "lallocator.h"

#include "assert.h"
#include "string.h"

LinearAllocator create_arena(size_t size) {
  LinearAllocator linear_allocator;
  linear_allocator.start = calloc(size, 1);
  assert(linear_allocator.start);
  linear_allocator.current = linear_allocator.start;
  linear_allocator.size = size;
  return linear_allocator;
}

void free_arena(LinearAllocator* linear_allocator) {
  assert(linear_allocator);
  free(linear_allocator->start);
  linear_allocator->start = NULL;
  linear_allocator->current = NULL;
  linear_allocator->size = 0;
  linear_allocator = NULL;
}

void* cds_lalloc(LinearAllocator* linear_allocator, size_t size) {
  assert(linear_allocator && linear_allocator->start && linear_allocator->current);
  assert(linear_allocator->size + size >= size);
  if ((char*)linear_allocator->current + size < (char*)linear_allocator->start + linear_allocator->size) {
    void* alloc_pos = linear_allocator->current;
    linear_allocator->current = (char*)linear_allocator->current + size;
    return alloc_pos;
  }
  // size is too small, double it
  size_t new_size = 2 * ((size > linear_allocator->size) ? size : linear_allocator->size);
  void* new_start = calloc(new_size, 1);
  assert(new_start);
  memcpy(new_start, linear_allocator->start, linear_allocator->size);
  free(linear_allocator->start);
  size_t current_offset = (char*)linear_allocator->current - (char*)linear_allocator->start;
  linear_allocator->start = new_start;
  void* alloc_pos = (char*)new_start + current_offset;
  linear_allocator->current = (char*)alloc_pos + size;
  linear_allocator->size = new_size;
  return alloc_pos;
}
