#include <stdio.h>

int frobcmp(char const *a, char const *b)
{
  int i = 0;
  int result = 0;
  while (result == 0 && a[i] != ' ' && b[i] != ' ') {
    char a_ = a[i] ^ 0x2A;//0x2A = 00101010, which is what every byte is XORed with in frobnication
    char b_ = b[i] ^ 0x2A;

    if ((int) a_ > (int) b_)
      result = 1;
    else if ((int) a_ < (int) b_)
      result = -1;
    else
      result = 0;
    
    i++;
  }
  return result;
}

int frobcmpWrapper(void const *aIn, void const *bIn)
{
  char *a = *(char **)aIn;
  char *b = *(char **)bIn;

  return frobcmp(a, b);
}

int main() {
  int DEFAULT_ARR_SIZE = 10;

  //READ FROM INPUT
  int wordNum = DEFAULT_ARR_SIZE;
  int *wordSize = malloc(wordNum * sizeof(int));
  char **words = malloc(wordNum * sizeof(char*));
  if (wordSize == NULL || words == NULL) {
    fprintf(stderr, "Failed to allocate memory.");
    exit(0);
  }
  
  int count;
  for (count = 0; count < wordNum; count++) {
    wordSize[count] = DEFAULT_ARR_SIZE;
    words[count] = malloc(wordSize[count] * sizeof(char));
    if (words[count] == NULL) {
      fprintf(stderr, "Failed to allocate memory.");
      exit(0);
    }
  }
  
  int spaceFound = 1;

  int c;
  int wordIndex = 0;//index of word currently being added to
  int charIndex = 0;//index of char in word that will next be changed

  c = getchar();
  while (!feof(stdin) && !ferror(stdin)) {
    char ch = (char) c;
    
    //if there is a space, write it into the word, and move onto the next word. increment wordIndex, and set charIndex to 0
    if (ch == ' ' || ch == '\n') {
      if (!spaceFound) {
	words[wordIndex][charIndex] = ' ';
	spaceFound = 1;
	charIndex = 0;
	wordIndex += 1;
	if (wordIndex >= wordNum) {
//if we have reached the end of our word capacity, double the size of both words and wordSize, and fill both
	  wordNum *= 2;
	  words = realloc(words, wordNum * sizeof(char*));
	  wordSize = realloc(wordSize, wordNum * sizeof(int));
	  int i;
	  for (i = wordNum / 2; i < wordNum; i++) {
	    wordSize[i] = DEFAULT_ARR_SIZE;
	    words[i] = malloc(wordSize[i] * sizeof(char*));
	  }
	}
      }
    }

    //continue writing the same word:
    //increment charIndex, and double the current word's wordsize if it's too small
    else {
      words[wordIndex][charIndex] = ch;

      spaceFound = 0;
      charIndex += 1;
      if (charIndex >= wordSize[wordIndex]) {
	wordSize[wordIndex] *= 2;
	words[wordIndex] = realloc(words[wordIndex], wordSize[wordIndex] * sizeof(char));
      }

    }

    c = getchar();
  }

  if (ferror(stdin)) {
    fprintf(stderr, "Error reading input.");
    exit(0);
  }
  
  int wordNumActual = wordIndex;//The actual number of words that were written, not the number allocated for
  if (!spaceFound)
    wordNumActual += 1;
    words[wordIndex][charIndex] = ' ';

  //SORT
  qsort(words, wordNumActual, sizeof(char*), frobcmpWrapper);
  
  //PRINT (each char separately so it can stop after spaces)
  int i;
  for (i = 0; i < wordNumActual; i++) {
    int j = -1;
    do {
      j += 1;
      if (putchar(words[i][j]) == -1) {
	fprintf(stderr, "Error writing output.");
	exit(0);
      }
    } while (words[i][j] != ' ');
  }



  //FREE MEM
  for (i = 0; i < wordNum; i++)
    free(words[i]);
  free(words);
  free(wordSize);
}
