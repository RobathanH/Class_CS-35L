#include <stdio.h>

int main()
{
  int i;
  for (i = 0; i < 256; i++)
    printf("0x%x", i ^ 42);
}
