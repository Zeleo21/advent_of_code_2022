#define _POSIX_C_SOURCE 200809L
#include<stdio.h>
#include<string.h>

enum points
{
  Rock = 1,
  Paper = 2,
  Scissors = 3
};

enum points get_score_off_letter(char c)
{
  if(c == 'A')
    return Rock;
  if(c == 'B')
    return Paper;
  else
    return Scissors;
}
enum points get_according_value(char c, enum points op_play)
{
  if(c == 'X')
  {
    if(op_play == Rock)
      return Scissors;
    if(op_play == Paper)
      return Rock;
    else
      return Paper;
  }
  if(c == 'Y')
    return op_play;

  if(op_play == Rock)
    return Paper;
  if(op_play == Paper)
      return Scissors;
  else
    return Rock;
}
int check_for_winner_of_round(enum points op_play, enum points pl_play)
{
  if(op_play == pl_play)
    return 3;
  if(op_play == Rock && pl_play == Scissors)
    return 0;
  if(op_play == Scissors && pl_play == Paper)
    return 0;
  if(op_play == Paper && pl_play == Rock)
    return 0;
  return 6;
}
int calculate_score_of_round(char *line)
{
  enum points opponent_play = get_score_off_letter(line[0]);
  enum points player_play = get_according_value(line[2], opponent_play);
  int result_of_round = check_for_winner_of_round(opponent_play, player_play);
  return result_of_round + player_play;
}

int parse_input(FILE *stream, int total_score)
{
  char *line = NULL;
  size_t len = 0;
  ssize_t nbread = 0;
  while((nbread = getline(&line, &len, stream)) != -1)
  {
    total_score += calculate_score_of_round(line);
  }
  return total_score;
}
int main(int argc, char **argv)
{
  if(argc < 2)
    return -1;
  FILE *stream = fopen(argv[1],"r");
  int total_score = parse_input(stream,0);
  printf("The total score is : %d\n",total_score);
  return 0;
}
