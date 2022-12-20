#define _POSIX_C_SOURCE 200809L
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int parse_line_and_get_value(char *line, int *local_max)
{
  if(line[0] == '\n')
    return -1;
  *local_max += atoi(line);
  return 0;
}
void parse_input_and_get_max(FILE *stream)
{
  char *line = NULL;
  size_t len = 0;
  ssize_t nbread = 0;
  int local_max = 0;
  int max_value = 0;
  int second_max_value = 0;
  int third_max_value = 0;
  while((nbread = getline(&line, &len, stream)) != -1)
  {
    int res = parse_line_and_get_value(line, &local_max);
    if(res == -1)
    {
      //printf("local_max is : %d\n",local_max);
      if(local_max > max_value)
      {
        third_max_value = second_max_value;
        second_max_value = max_value;
        max_value = local_max;
      }
      else if(local_max > second_max_value)
      {
        third_max_value = second_max_value;
        second_max_value = local_max;
      }
      else if(local_max > third_max_value)
        third_max_value = local_max;
      local_max = 0;
    }
    //fwrite(line, nbread, 1, stdout);
  }
  printf("the max_value is : %d\n",max_value);
  printf("the second_max_value is : %d\n",second_max_value);
  printf("the third_max_value is : %d\n",third_max_value);
  printf("the total value is : %d\n",max_value + second_max_value + third_max_value);
}
int main(int argc, char **argv)
{
  if(argc < 2)
    return -1;
  FILE *stream = fopen(argv[1],"r");
  parse_input_and_get_max(stream);
  return 0;
}
