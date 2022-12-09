#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
            [J]             [B] [W]
            [T]     [W] [F] [R] [Z]
        [Q] [M]     [J] [R] [W] [H]
    [F] [L] [P]     [R] [N] [Z] [G]
[F] [M] [S] [Q]     [M] [P] [S] [C]
[L] [V] [R] [V] [W] [P] [C] [P] [J]
[M] [Z] [V] [S] [S] [V] [Q] [H] [M]
[W] [B] [H] [F] [L] [F] [J] [V] [B]
 1   2   3   4   5   6   7   8   9 
*/

char *startBoard[] = {
  "", "WMLF", "BZVMF", "HVRSLQ", "FSVQPMTJ",
  "LSW", "FVPMRJW", "JQCPNRF", "VHPSZWRB",
  "BMJCGHZW",
};

#define MAX_LEN 200
#define CHARS 56

char *containers[10];

void printBoard() {
  for (int i = 0; i < 10; i++) {
    if (i == 0) continue;
    printf("%d - %s\n", i, containers[i]);
  }
  puts("\n ");
}

void slice(char *str, char *result, size_t start, size_t end)
{
  strncpy(result, str + start, end - start);
  for (int i = start; i < end; i++) {
    str[i] = '\0';
  }
}

void execute(char *commands[3])
{
  int amt = atoi(commands[0]);
  int from = atoi(commands[1]);
  int to = atoi(commands[2]);

  // copy amt chars from from
  char *temp = (char *)malloc(amt * sizeof(char));
  int end = strlen(containers[from]);
  int start = end - amt;

  slice(containers[from], temp, start, end);

  // add temp to to
  strcat(containers[to], temp);

  free(temp);
}

int parse(char *str)
{

  char *parsed[3];
  int i = 1;
  char *token = malloc(MAX_LEN * sizeof(char));
  token = strtok(str, " ");

  while (token != NULL)
  {
    if (i++ % 2 == 0)
    {
      parsed[i / 2 - 1] = token;
    }
    token = strtok(NULL, " ");
  }

  execute(parsed);

  free(token);

  return 0;
}

void initialize()
{
  for (int i = 0; i < 10; i++)
  {
    if (i == 0) continue;
    containers[i] = (char *)calloc(MAX_LEN, sizeof(char));
    int len = strlen(startBoard[i]);
    strncpy(containers[i], startBoard[i], len);
  }
}

int readLines(FILE *fp)
{
  initialize();
  printBoard();
  char str[MAX_LEN];

  // feof returns true if EOF
  while (!feof(fp) && !ferror(fp))
  {
    if (fgets(str, MAX_LEN, fp) != NULL)
    {
      parse(str);
    }
  }

  return 0;
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
  printBoard();

  fclose(fp);
  exit(1);

error_read_file:
  perror("fopen ");
  return 1;

error_open_file:
  perror("getline ");
  return 2;
}