#include "includes.h"
#include "imigrant_factory.h"
#include "judge.h"

void string_to_int(int *number, char *string)
{
  sscanf(string, "%d", number);
}

void create_children(int PI)
{
  int pid_t = 0;
  for (int i = 0; i < 2; i++)
  {
    pid_t = fork();
    if (pid_t == 0 && i == 0)
    {
      create_imigrants(PI);
    }
    if (pid_t == 0 && i == 1)
    {
      start_judge();
    }
  }
}

int main(int argc, char **argv)
{
  //TODO: make validation
  int PI = 0;
  string_to_int(&PI, argv[1]);
  int IG = 0;
  string_to_int(&IG, argv[2]);
  int JG = 0;
  string_to_int(&JG, argv[3]);
  int IT = 0;
  string_to_int(&IT, argv[4]);
  int JT = 0;
  string_to_int(&JT, argv[5]);

  create_children(PI);
}
