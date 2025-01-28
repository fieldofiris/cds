#ifndef CDS_DARRAY_H
#define CDS_DARRAY_H

#include "lallocator.h"

typedef struct {
  LinearAllocator linear_allocator;
  size_t element_size;
  size_t array_size;
  size_t capacity;
} DynamicArray;

#define create_dynamic_array(type, capacity) ((DynamicArray){.linear_allocator = create_arena(capacity * sizeof(type)), .element_size = sizeof(type), .array_size = 0, capacity})
void free_dynamic_array(DynamicArray* dynamic_array);

DynamicArray darray_deepcopy(DynamicArray* dynamic_array);
void* darray_element_at(DynamicArray* dynamic_array, size_t index);
size_t darray_size(DynamicArray* dynamic_array);
size_t darray_capacity(DynamicArray* dynamic_array);

void darray_push(DynamicArray* dynamic_array, void* element_ptr);
void darray_insert_at(DynamicArray* dynamic_array, void* element_ptr, size_t index);

void darray_pop(DynamicArray* dynamic_array);
void darray_delete_at(DynamicArray* dynamic_array, size_t index);
void darray_clear(DynamicArray* dynamic_array);

#endif