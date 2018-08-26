#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
  if (argc != 3) {
    fprintf(stderr, "Incorrect argument count.\n");
    exit(0);
  }

  char *from = argv[1];
  char *to = argv[2];

  //check for duplicate bytes in from, then check for same size
  int i = 0;
  while (from[i] != '\0' && to[i] != '\0') {
    int j = 0;
    for (; j < i; j++) {
      if (from[i] == from[j]) {
	fprintf(stderr, "Duplicate bytes in 1st operand.\n");
	exit(0);
      }
    }

    i++;
  }
  if (from[i] != '\0' || to[i] != '\0') {
    fprintf(stderr, "Operands aren't the same size.\n");
    exit(0);
  }


  char c;
  char *buf = &c;

  while (read(0, buf, 1) == 1) {
    int i = 0;
    while (from[i] != '\0' && from[i] != c) i++;
    if (from[i] == c)
      c = to[i];

    write(1, buf, 1);
  }
}
