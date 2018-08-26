#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  if (argc != 2) exit(0);
  
  int lines = atoi(argv[1]);

  srand(time(NULL));
  int i;
  for (i = 0; i < lines; i++) {
    int charNum = rand() % 20 + 1;
    int j;
    for (j = 0; j < charNum; j++) {
      int r = rand() % 95 + 32;//32 to 126 are normal, easily recognizable characters
      putchar(r);
    }
    putchar('\n');
  }
}
