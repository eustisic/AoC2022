#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_LINES 2500
#define MAX_LEN 4

/*
A X - 1 rock
B Y - 2 paper
C Z - 3 scissors

Z Win 6
Y draw 3
X loose 0
*/

int scoreGame(char line[MAX_LEN])
{
  int score = 0;
  int you = line[0];
  int me = line[2];

  if (you == 'A')
  {
    // you rock
    if (me == 'X')
      score = 3 + 0;
    if (me == 'Y')
      score = 1 + 3;
    if (me == 'Z')
      score = 2 + 6;
  }
  else if (line[0] == 'B')
  {
    // you paper
    if (me == 'X')
      score = 1 + 0;
    if (me == 'Y')
      score = 2 + 3;
    if (me == 'Z')
      score = 3 + 6;
  }
  else if (line[0] == 'C')
  {
    // you scissors
    if (me == 'X')
      score = 2 + 0;
    if (me == 'Y')
      score = 3 + 3;
    if (me == 'Z')
      score = 1 + 6;
  }

  return score;
}

int sumGames(FILE *fp)
{
  char line[MAX_LEN];
  int sum = 0;

  while (!feof(fp) && !ferror(fp))
  {
    if (fgets(line, MAX_LEN, fp) != NULL)
    {
      sum += scoreGame(line);
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

  int sum = sumGames(fp);
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
