#include <stdio.h>

#define ALIGNMENT8 8

int main(void) {
  unsigned int *i __attribute__((aligned (ALIGNMENT8)));
  unsigned int j __attribute__((aligned (ALIGNMENT8))) = 117;

  printf("int size: %ld; current alignment: %d, biggest alignment: %d\n",
    sizeof(unsigned int),
    ALIGNMENT8,
    __BIGGEST_ALIGNMENT__);

  i = &j;

  printf("address of i: %p\naddress of j: %p\n", &i, i);


  return 0;
}
