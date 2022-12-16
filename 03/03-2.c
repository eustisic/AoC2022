/*
  each line is a string of ascii characters
  divide each line into two separate equal length arrays
  sort each resulting line
  iterate through the lines with pointers and find the common character
  add the common character to a sum where the sum is char - 'a' or 'A' 
    + 1 for lowercase
    + 27 for uppercase
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 100
#define UP_SCORE 27
#define LOW_SCORE 1

struct lineStruct
{
  int fllen;
  char* fl;
  int sllen;
  char* sl;
  int tllen;
  char* tl;
} triple;


int compare_asc( const void* a, const void* b)
{
  char char_a = * ( (char*) a );
  char char_b = * ( (char*) b );

  return char_a - char_b;
}

int calcCharValue(char c) {
  if (isupper(c)) {
    return c - 'A' + UP_SCORE;
  }

  return c - 'a' + LOW_SCORE;
}

int calcLineValue() {
  // cal lengths of lines
  int res = 0;

  // user pointers to find matching element
  // two pointers 
  int i = 0, j = 0, k = 0;
  printf("%c %c %c\n", triple.fl[triple.fllen], triple.sl[triple.sllen], triple.tl[triple.tllen]);

  while (i < triple.fllen && j < triple.sllen && k < triple.tllen) {
    // advance i and j until they are equal
    while (triple.fl[i] != triple.sl[j]) {
      if (triple.fl[i] < triple.sl[j]) {
        i++;
      }
      j++;
    }
    printf("%c %c\n", triple.sl[j], triple.fl[i]);

    // scan k until for match 
    while (k < triple.tllen) {
      if (triple.tl[k] == triple.fl[i]) {
        return calcCharValue(triple.fl[i]);
      }
      k++;
    }

    k = 0;
    i++, j++;
  }

  return 0;
}

void freeAll() 
{
  free(triple.fl);
  free(triple.sl);
  free(triple.tl);
}

void writeString(char* fl, char line[MAX_LEN], int len) {
  for (int i = 0; i < len; i++) {
    fl[i] = line[i];
  }
  qsort(fl, len, sizeof(char), compare_asc);
}

int sumLines(FILE *fp)
{
  char fullLine[MAX_LEN];
  int sum = 0, line = 0;

  // keep track of which line we are on
  // allocate string arrays for each line

  // every third line calc the value of the common element between the lines

  while (!feof(fp) && !ferror(fp))
  {
    if (fgets(fullLine, MAX_LEN, fp) != NULL)
    {
      int i;
      for (i = 0; fullLine[i] != '\0' && fullLine[i] != '\n'; i++);

      switch (line)
      {
      case 0:
        triple.fl = (char*) malloc(i);
        triple.fllen = i;
        writeString(triple.fl, fullLine, i);
        line++;
        break;
      case 1:
        triple.sl = (char*) malloc(i);
        triple.sllen = i;
        writeString(triple.sl, fullLine, i);
        line++;
        break;
      case 2:
        triple.tl = (char*) malloc(i);
        triple.tllen = i;
        writeString(triple.tl, fullLine, i);
        sum += calcLineValue();
        line = 0;
        freeAll();
        break;
      }
    }
  }

  return sum;
}

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    printf("no file given \n");
    goto error_read_file;
  }
  // open file
  FILE *fp = fopen(argv[1], "r"); // opens file in reading mode

  if (!fp)
    goto error_open_file;
  printf("Opened file: %s\n", argv[1]);

  // read and parse data

  int sum = sumLines(fp);
  printf("%d\n", sum);

  fclose(fp);
  exit(1);

error_read_file:
  perror("fopen ");
  exit(2);

error_open_file:
  perror("getline ");
  exit(2);
}
