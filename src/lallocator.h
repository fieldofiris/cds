#ifndef LALLOCATOR_H
#define LALLOCATOR_H

#include "stdlib.h"
#include "stdbool.h"

typedef struct {
  void* start;
  void* current;
  size_t size;
} LinearAllocator;

LinearAllocator create_arena(size_t size);
void free_arena(LinearAllocator *linear_allocator);
void *cds_lalloc(LinearAllocator *linear_allocator, size_t size);

#endif