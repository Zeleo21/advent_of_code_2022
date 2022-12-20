#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct range
{
  int first;
  int last;
};

int check_for_range(struct range *r1, struct range *r2)
{
  if(r1->first <= r2->first && r1->last >= r2->last)
    return 1;
  if(r2->first <= r1->first && r2->last >= r1->last)
    return 1;
  if(r1->first >= r2->first && r2->last >= r1->first)
    return 1;
  if(r2->first >= r1->first && r1->last >= r2->first)
    return 1;
  return 0;
}

struct range *parse_range(struct range *r, char *pair)
{
  char *token = strtok(pair,"-");
  r->first = atoi(token);
  token = strtok(NULL, "\n");
  r->last = atoi(token);
  return r;
}
int parse_pair(char *line)
{
  struct range *r1 = malloc(sizeof(struct range));
  struct range *r2 = malloc(sizeof(struct range));
  char *token = strtok(line, ",");
  char *token2 = strtok(NULL, "\n");
  r1 = parse_range(r1, token);
  r2 = parse_range(r2, token2);
  int is_range = check_for_range(r1,r2);
  free(r1);
  free(r2);
  return is_range;
}

int parse_input(FILE *stream, int sum_of_pairs)
{
  char *line = NULL;
  size_t len = 0;
  ssize_t nbread = 0;
  while((nbread = getline(&line, &len, stream)) != -1)
  {
    sum_of_pairs += parse_pair(line);
  }
  return sum_of_pairs;
}
int main(int argc, char **argv)
{
  if(argc < 2)
    return -1;
  FILE *stream = fopen(argv[1],"r");
  int sum_of_pairs = parse_input(stream,0);
  fclose(stream);
  return 0;
}
