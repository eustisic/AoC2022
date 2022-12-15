#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct state {
  char *ring;
  int pos, sz;
  int counts[27]; // count map for letters
  int ndupes; // number of duplicate characters
  int ans;
};


static void step(struct state *s, char c)
{
	int i;
	char old_c;

	i = s->pos % s->sz;

	/* remove old character, decrement ndupes if needed */
	if ((old_c = s->ring[i])) {
    // if the character value in counts is 1 there is no longer a dup and ndubpes is decremented
		s->ndupes -= --s->counts[old_c - 'a'] == 1;
  }

	/* add the new character */
	s->ring[i] = c;
  // increment the count of the char and if it is equal to 2 increment ndupes b/c now there is a new dup
	s->ndupes += ++s->counts[c - 'a'] == 2;

	/* if no dupes, we have our answer */
	if (s->pos >= s->sz && !s->ndupes)
		s->ans = s->pos+1;

	s->pos++;
}

int main(int argc, char *argv[])
{
  int c;

  if (argc != 2)
  {
    printf("no file given \n");
    goto error_read_file;
  }
  // open file
  FILE *fp = fopen(argv[1], "r"); // opens int stdin stream

  // initialize state
  static struct state s1;
  static char buf1[4];
  static char buf2[14];
  static struct state s2;

  s1.ring = buf1; s1.sz = 4;
  s2.ring = buf2; s2.sz = 14;

  // read data

  while ((!s1.ans || !s2.ans) && !feof(fp) && !ferror(fp)) {
    c = fgetc(fp);
    if (!s1.ans) step(&s1, c);
    if (!s2.ans) step(&s2, c);
  }
  // print max elf and exit
  printf("ans: %d\n", s1.ans);
  printf("ans2: %d\n", s2.ans);
  fclose(fp);
  exit(1);

error_read_file:
  perror("fopen ");
  return 1;
}