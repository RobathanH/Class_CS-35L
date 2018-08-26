#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
  srand(time(NULL));
  int i = 0;
  for (; i < 5000000; i++) {
    int r = rand() % 96 + 32;
    putchar(r);
  }
}
