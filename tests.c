#include "cds.h"
#include "stdio.h"

int main() {
  DynamicArray da = create_dynamic_array(int, 0);
  int x = 5;
  int y = 10;
  int z = 7;
  printf("cap0: %d\n", darray_capacity(&da));
  darray_push(&da, &x);
  printf("cap1: %d\n", darray_capacity(&da));
  darray_push(&da, &y);
  printf("cap2: %d\n", darray_capacity(&da));
  darray_push(&da, &z);
  printf("cap3: %d\n", darray_capacity(&da));
  int* da0 = darray_element_at(&da, 0);
  int* da1 = darray_element_at(&da, 1);
  int* da2 = darray_element_at(&da, 2);
  printf("elems: %d, %d, %d\n", *da0, *da1, *da2);
  printf("size0: %d\n", darray_size(&da));
  darray_pop(&da);
  printf("size1: %d\n", darray_size(&da));
  darray_delete_at(&da, 0);
  printf("size2: %d\n", darray_size(&da));
  DynamicArray dyno = darray_deepcopy(&da);
  int a = 88;
  darray_insert_at(&dyno, &a, 0);
  darray_clear(&da);
  free_dynamic_array(&da);
  free_dynamic_array(&dyno);
  return 0;
}