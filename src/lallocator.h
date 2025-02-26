#ifndef CDS_LALLOCATOR_H
#define CDS_LALLOCATOR_H

#include "stdlib.h"

typedef struct {
  void* start;
  void* current;
  size_t size;
} LinearAllocator;

LinearAllocator create_arena(size_t size);
void free_arena(LinearAllocator* linear_allocator);
void* cds_lalloc(LinearAllocator* linear_allocator, size_t size);

#endif