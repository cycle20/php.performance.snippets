#include <stdio.h>

extern int array[];
extern void update();

int main(void) {
  printf("Hello\n");
  update();
  for (int i = 0; i < 10; i++) {
    printf("%d, ", array[i]);
  }
  printf("\n");

  return 0;
}
