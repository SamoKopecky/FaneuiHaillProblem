#include "includes.h"
#include "immigrant_factory.h"
#include "judge.h"
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>

int *counter;
sem_t *counter_mutex;

void map_shared_mem()
{
  counter = mmap(NULL, sizeof counter, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
  counter_mutex = mmap(NULL, sizeof counter_mutex, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
}

void unmap_shared_mem()
{
  munmap(NULL, sizeof counter);
  munmap(NULL, sizeof counter_mutex);
}

void init_semaphores()
{

  sem_init(counter_mutex, 1, 1);
}

void string_to_int(int *number, char *string)
{
  sscanf(string, "%d", number);
}

void create_children(int *PI)
{
  int pid_t = 0;
  for (int i = 0; i < 2; i++)
  {
    {
      if ((pid_t = fork()) == 0 && i == 0)
      {
        immigrant_factory(PI);
      }
      else if (pid_t == 0 && i == 1)
      {
        judge(counter, counter_mutex);
      }
    }
  }
}

int main(int argc, char **argv)
{

  map_shared_mem();
  init_semaphores();
  *counter = 2;

  int *PI;
  string_to_int(PI, argv[1]);
  int IG = 0;
  string_to_int(&IG, argv[2]);
  int JG = 0;
  string_to_int(&JG, argv[3]);
  int IT = 0;
  string_to_int(&IT, argv[4]);
  int JT = 0;
  string_to_int(&JT, argv[5]);

  create_children(PI);

  sleep(1);
  printf("counter : %d\n", *counter);
  unmap_shared_mem();
}

//TODO: make validation on command line parameters