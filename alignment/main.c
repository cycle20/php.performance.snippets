#include <stdio.h>

#define ALIGNMENT8 8
#define ALIGNMENT16 16
#define YES "yes"
#define NO "no"

int main(void)
{
  void printAddressInfo(void *ptr);

  unsigned int *i __attribute__((aligned(ALIGNMENT8)));
  unsigned int j __attribute__((aligned(ALIGNMENT8))) = 117;

  printf("int size: %ld; current alignment: %d, biggest alignment: %d\n",
         sizeof(unsigned int),
         ALIGNMENT8,
         __BIGGEST_ALIGNMENT__);

  i = &j;

  printf("address of i: %p\naddress of j: %p\n", &i, i);

  printAddressInfo(i);

  return 0;
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
