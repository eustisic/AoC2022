#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_LINES 3000
#define MAX_LEN 15

int compare( const void* a, const void* b)
{
  int int_a = * ( (int*) a );
  int int_b = * ( (int*) b );

  return int_b - int_a;
}

int maxElf(int data[MAX_LINES][MAX_LEN], int size)
{
  int max = 0, sum = 0;

  int summedElfs[size];

  for (int i = 0; i < size && data[i] != NULL; i++) {
    for (int j = 0; j < MAX_LEN && data[i][j] != 0; j++) {
      sum += data[i][j];
    }
    if (sum > max) {
      max = sum;
    }
    summedElfs[i] = sum;
    sum = 0;
  }

  qsort(summedElfs, size, sizeof(summedElfs[0]), compare);
  printf("top three %d\n", summedElfs[0] + summedElfs[1] + summedElfs[2]);

  return max;
}

int findElf(FILE *fp)
{
  int i = 0, j = 0, cal; // keeps track of current group
  char str[MAX_LEN];
  int data[MAX_LINES][MAX_LEN];

  // feof returns true if EOF
  while (!feof(fp) && !ferror(fp))
  {
    // gets each new line, forms integer from line and stores
    if (fgets(str, MAX_LEN, fp) != NULL)
    {
      if (str[0] == '\n')
      {
        j = 0;
        i++;
      }
      else
      {
        cal = atoi(str);
        data[i][j] = cal;
        j++;
      }
    }
  }

  i++;
  // int max = data[0][0];

  int max = maxElf(data, i);

  return max;
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

  // read data
  int max_elf = findElf(fp);

  // print max elf and exit
  printf("%d\n", max_elf);
  fclose(fp);
  exit(1);

error_read_file:
  perror("fopen ");
  return 1;

error_open_file:
  perror("getline ");
  return 2;
}