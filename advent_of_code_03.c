#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct group
{
  char *line1;
  char *line2;
  char *line3;
};
char get_item_in_common(struct group *g)
{
  char result = '0';
  for(size_t i = 0; g->line1[i] != '\0' ; i++)
  {
    for(size_t j = 0; g->line2[j] != '\0' ; j++)
    {
      for(size_t k = 0; g->line3[k] != '\0'; k++)
      {
        if(g->line1[i] == g->line2[j] && g->line1[i] == g->line3[k])
        {
          result = g->line1[i];
          break;
        }
      }
    }
  }
  return result;
}
int get_priority(char c)
{
  if(c >= 'A' && c <= 'Z')
    return c - 'A' + 27;
  else
    return c - 'a' + 1;
}


void free_group(struct group *g)
{
  g->line1 = NULL;
  g->line2 = NULL;
  g->line3 = NULL;
  free(g->line1);
  free(g->line2);
  free(g->line3);
  free(g);
}
struct group *add_line(struct group *g, int is_full,int nbread, char *line)
{
  if(is_full == 1)
  {
    g->line1 = malloc(nbread);
    memmove(g->line1, line,nbread - 1);
  }
  if(is_full == 2)
  {
    g->line2 = malloc(nbread);
    memmove(g->line2, line, nbread - 1);
  }
  if(is_full == 3)
  {
    g->line3 = malloc(nbread);
    memmove(g->line3, line, nbread - 1);
  }
  return g;
}

void print_group(struct group *g)
{
  printf("%s\n", g->line1);
  printf("%s\n", g->line2);
  printf("%s\n", g->line3);
}
int parse_input(FILE *stream, int total_priority)
{
  char *line = NULL;
  size_t len = 0;
  ssize_t nbread = 0;
  size_t size = 0;
  int is_full = 0;
  struct group *g = malloc(sizeof(struct group));
  while((nbread = getline(&line, &len, stream)) != -1)
  {
    if(is_full == 3)
    {
      print_group(g);
      is_full = 0;
      char c = get_item_in_common(g);
      total_priority += get_priority(c);
      printf("total priority is : %d\n",total_priority);
      free_group(g);
      g = malloc(sizeof(struct group));
      g = add_line(g, is_full + 1, nbread, line);
      is_full +=1;
    }
    else
    {
      is_full+=1;
      g = add_line(g, is_full, nbread, line);
    }
  }
  if(is_full == 3)
  {
    print_group(g);
    char c = get_item_in_common(g);
    if(c == '\n')
      printf("caca\n");
    printf("character is : %c\n",c);
    total_priority += get_priority(c);
    free_group(g);
  }
  free(line);
  return total_priority;
}
int main(int argc, char **argv)
{
  if(argc < 2)
    return -1;
  FILE *stream = fopen(argv[1],"r");
  int total_priority = parse_input(stream,0);
  printf("The priority sum is : %d\n",total_priority);
  fclose(stream);
  return 0;
}
