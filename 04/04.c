/*
 Count the number of pairs where one range is fully contained in the other

  1. read line
  2. parse line into two ranges
    4-90,1-4 -> one: [4, 90], two: [1, 4]
  3. if one[0] <= two[0] && one[1] >= two[1] or vice versa one range is contained in the other

*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_LEN 12

int parse(char str[MAX_LEN])
{
  puts(str);
  int i = 0;
  char *token = strtok(str, ",");
  char *array[2];

  while (token != NULL)
  {
    array[i++] = token;
    token = strtok(NULL, ",");
  }

  char *array2[4];
  int k = 0;
  for (int j = 0; j < 2; j++) {
    char *token2 = strtok(array[j], "-");
    while (token2 != NULL)
    {
      array2[k++] = token2;
      token2 = strtok(NULL, "-");
    }
  }
  printf("%d %d %d %d\n", atoi(array2[0]), atoi(array2[1]), atoi(array2[2]), atoi(array2[3]));
  
  if (atoi(array2[0]) == 0) {
    return 0;
  }
  if (atoi(array2[0]) <= atoi(array2[2]) && atoi(array2[1]) >= atoi(array2[3])) {
    return 1;
  }
  if (atoi(array2[2]) <= atoi(array2[0]) && atoi(array2[3]) >= atoi(array2[1])) {
    return 1;
  }
  return 0;
}

int readLines(FILE *fp)
{
  int cal = 0; // keeps track of total
  char str[MAX_LEN];

  // feof returns true if EOF
  while (!feof(fp) && !ferror(fp))
  {
    if (fgets(str, MAX_LEN, fp) != NULL)
    {
      cal += parse(str);
    }
  }

  return cal;
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
  int answer = readLines(fp);

  // print max elf and exit
  printf("%d\n", answer);
  fclose(fp);
  exit(1);

error_read_file:
  perror("fopen ");
  return 1;

error_open_file:
  perror("getline ");
  return 2;
}