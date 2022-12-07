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

#define MAX_LINE 300
#define MAX_LEN 100
#define UP_SCORE 27
#define LOW_SCORE 1

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

void slice(const char *str, char *result, size_t start, size_t end)
{
    strncpy(result, str + start, end - start);
}

int calcLineValue(char line[MAX_LEN]) {
  int res, half, i;

  for (i = 0; line[i] != '\0'; i++);

  half = i / 2;
  char* firstHalf; 
  char* secondHalf;

  firstHalf = (char*) malloc(half + 1);
  secondHalf = (char*) malloc(half + 1);

  // create halves of line
  slice(line, firstHalf, 0, half);
  slice(line, secondHalf, half, i);


  // sort halves by 
  qsort(firstHalf, half, sizeof(char), compare_asc);
  qsort(secondHalf, half, sizeof(char), compare_asc);

  // user pointers to find matching element
  // two pointers 
  int j = 0, k = 0; 
  while (j < half && k < half) {
    if (firstHalf[j] == secondHalf[k]) {
      res = calcCharValue(firstHalf[j]);
      break;
    } else if (firstHalf[j] < secondHalf[k]) {
      j++;
    } else {
      k++;
    }
  }

  free(firstHalf);
  free(secondHalf);

  return res;
}

int sumLines(FILE *fp)
{
  char fullLine[MAX_LEN];
  int sum = 0;

  while (!feof(fp) && !ferror(fp))
  {
    if (fgets(fullLine, MAX_LEN, fp) != NULL)
    {
      sum += calcLineValue(fullLine);
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
