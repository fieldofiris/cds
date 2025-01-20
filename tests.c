#include "cds.h"
#include "stdio.h"

int* test_lalloc(LinearAllocator* la, int value) {
  int* p = cds_lalloc(la, sizeof(int));
  *p = value;
  return p;
}

int main() {
  printf("Hello, World!\n");
  LinearAllocator la = create_arena(1);
  int* p = test_lalloc(&la, 2);
  printf("%d\n", *p);
  printf("%d\n", la.size);
  free_arena(&la);
  return 0;
}