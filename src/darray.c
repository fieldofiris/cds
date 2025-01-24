#include "darray.h"

#include "string.h"
#include "assert.h"

void free_dynamic_array(DynamicArray* dynamic_array){
  assert(dynamic_array);
  free_arena(&dynamic_array->linear_allocator);
  dynamic_array->element_size = 0;
  dynamic_array->array_size = 0;
  dynamic_array->capacity = 0;
  dynamic_array = NULL;
}

DynamicArray darray_deepcopy(DynamicArray* dynamic_array){
  assert(dynamic_array);
  DynamicArray copy = {
    .linear_allocator = create_arena(dynamic_array->linear_allocator.size), 
    .element_size = dynamic_array->element_size,
    .array_size = dynamic_array->array_size,
    .capacity = dynamic_array->capacity
  };
  memcpy(copy.linear_allocator.start, dynamic_array->linear_allocator.start, copy.linear_allocator.size);
  copy.linear_allocator.current = (char*)copy.linear_allocator.start + ((char*)dynamic_array->linear_allocator.current - (char*)dynamic_array->linear_allocator.start);
  return copy;
}

void* darray_element_at(DynamicArray* dynamic_array, size_t index){
  assert(dynamic_array);
  assert(index < dynamic_array->array_size);
  return (char*)dynamic_array->linear_allocator.start + dynamic_array->element_size * index;
}

size_t darray_size(DynamicArray* dynamic_array){
  assert(dynamic_array);
  return dynamic_array->array_size;
}

size_t darray_capacity(DynamicArray* dynamic_array){
  assert(dynamic_array);
  return dynamic_array->capacity;
}

void darray_push(DynamicArray* dynamic_array, void* element_ptr){
  assert(dynamic_array);
  void* new_element_ptr = cds_lalloc(&dynamic_array->linear_allocator, dynamic_array->element_size);
  assert(new_element_ptr);
  memcpy(new_element_ptr, element_ptr, dynamic_array->element_size);
  dynamic_array->array_size += 1;
  dynamic_array->capacity = dynamic_array->linear_allocator.size/dynamic_array->element_size;
}

void darray_insert_at(DynamicArray* dynamic_array, void* element_ptr, size_t index){
  assert(dynamic_array);
  assert(index < dynamic_array->array_size);
  void* insert_pos = (char*)dynamic_array->linear_allocator.start + index * dynamic_array->element_size;
  memcpy(insert_pos, element_ptr, dynamic_array->element_size);
}

void darray_pop(DynamicArray* dynamic_array){
  assert(dynamic_array);
  assert(dynamic_array->array_size > 0);
  dynamic_array->linear_allocator.current = (char*)dynamic_array->linear_allocator.current - dynamic_array->element_size;
  dynamic_array->array_size -= 1;
}

void darray_delete_at(DynamicArray* dynamic_array, size_t index){
  assert(dynamic_array);
  assert(index < dynamic_array->array_size);
  void* delete_pos = (char*)dynamic_array->linear_allocator.start + index * dynamic_array->element_size;
  size_t tail_size = dynamic_array->array_size - index - 1;
  memmove(delete_pos, (char*)delete_pos + dynamic_array->element_size, dynamic_array->element_size * tail_size);
  dynamic_array->linear_allocator.current = (char*)dynamic_array->linear_allocator.current - dynamic_array->element_size;
  dynamic_array->array_size -= 1;
}

void darray_clear(DynamicArray* dynamic_array){
  assert(dynamic_array);
  memset(dynamic_array->linear_allocator.start, 0, dynamic_array->linear_allocator.size);
  dynamic_array->linear_allocator.current = dynamic_array->linear_allocator.start;
  dynamic_array->array_size = 0;
}