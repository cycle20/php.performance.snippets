#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ALIGNMENT8 8
#define ALIGNMENT16 16
#define YES "yes"
#define NO "no"

int main(void)
{
  void iterateWithNoAlignment();
  void printAddressInfo(void *ptr);

  unsigned int *i __attribute__((aligned(ALIGNMENT8)));
  unsigned int j __attribute__((aligned(ALIGNMENT8))) = 117;

  printf("int size: %ld, long double size: %ld;\n"
         "current alignment: %d, biggest alignment: %d\n",
         sizeof(unsigned int),
         sizeof(long double),
         ALIGNMENT8,
         __BIGGEST_ALIGNMENT__);

  i = &j;

  printf("address of i: %p\naddress of j: %p\n", &i, i);

  printAddressInfo(i);


  long double *number = aligned_alloc(ALIGNMENT16, sizeof(double));
  printAddressInfo(number);
  free(number);

  // some 'heavy' test
  iterateWithNoAlignment();

  return 0;
}

#define ITEM_COUNT 1000 * 1000 * 200

void iterateWithNoAlignment() {
  void printAddressInfo(void *ptr);

  printf("\n\n\n>>>> Iteration with no alignment\n");

  printf("MaxInt:\n%20d,\nItem count:\n%20d\n", __INT32_MAX__, ITEM_COUNT);

  // allocate with extra byte for shift
  long double *numbers = calloc(ITEM_COUNT + 1, sizeof(long double));
  long double *savedAddress = numbers;
  if (numbers == NULL) {
    perror("calloc failed");

    return;
  }

  // change the address
  numbers = (void *)numbers + 3;

  //printAddressInfo(&numbers);
  printAddressInfo(numbers);

  for (unsigned int i = 0; i < ITEM_COUNT; i++) {
    numbers[i] = i; //sqrtl(i) * 2.0 / 3.0;
  }

  free(savedAddress);
}


void printAddressInfo(void *ptr)
{
  unsigned long address = (unsigned long)ptr;
  unsigned int mask = 0;
  char *answer;

  printf("\n%p alignment details:\n", ptr);
  printf("---------------------------------\n");

  mask = 0x3;
  answer = !(address & mask) ? YES : NO;
  printf("%-20s %5s\n", "Is 4-byte aligned?", answer);

  mask = 0x7;
  answer = !(address & mask) ? YES : NO;
  printf("%-20s %5s\n", "Is 8-byte aligned?", answer);

  mask = 0xF;
  answer = !(address & mask) ? YES : NO;
  printf("%-20s %5s\n", "Is 16-byte aligned?", answer);

  mask = 0x1F;
  answer = !(address & mask) ? YES : NO;
  printf("%-20s %5s\n", "Is 32-byte aligned?", answer);
}
