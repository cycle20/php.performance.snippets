#include <stdio.h>

#define ALIGNMENT 8

int main(void) {
  unsigned int *i __attribute__((aligned (ALIGNMENT)));
  unsigned int j __attribute__((aligned (ALIGNMENT))) = 117;

  printf("int size: %ld; current alignment: %d, biggest alignment: %d\n",
    sizeof(unsigned int),
    ALIGNMENT,
    __BIGGEST_ALIGNMENT__);

  i = &j;

  printf("address of i: %p\naddress of j: %p\n", &i, i);


  return 0;
}
