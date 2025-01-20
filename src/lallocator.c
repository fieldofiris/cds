#include "lallocator.h"

#include "string.h"

LinearAllocator create_arena(size_t size) {
  LinearAllocator linear_allocator;
  linear_allocator.start = calloc(size, 1);
  if (linear_allocator.start) {
    linear_allocator.current = linear_allocator.start;
    linear_allocator.size = size;
  }
  return linear_allocator;
}

void free_arena(LinearAllocator* linear_allocator) {
  if (!linear_allocator) {
    return;
  }
  free(linear_allocator->start);
  linear_allocator->start = NULL;
  linear_allocator->current = NULL;
  linear_allocator = NULL;
}

void* cds_lalloc(LinearAllocator* linear_allocator, size_t size) {
  if (!linear_allocator || !linear_allocator->start || !linear_allocator->current) {
    return NULL;
  }
  if (linear_allocator->size + size < size) {
    return NULL;
  }
  if ((unsigned char*)linear_allocator->current + size < (unsigned char*)linear_allocator->start + linear_allocator->size) {
    void* old_current = linear_allocator->current;
    linear_allocator->current = (unsigned char*)linear_allocator->current + size;
    return old_current;
  }
  size_t new_size = 2 * ((size > linear_allocator->size) ? size : linear_allocator->size);
  void* new_start = calloc(new_size, 1);
  if (!new_start) {
    return NULL;
  }
  memcpy(new_start, linear_allocator->start, linear_allocator->size);
  free(linear_allocator->start);
  linear_allocator->start = new_start;
  void* new_current = (unsigned char*)new_start + linear_allocator->size;
  linear_allocator->current = (unsigned char*)new_current + size;
  linear_allocator->size = new_size;
  return new_current;
}
