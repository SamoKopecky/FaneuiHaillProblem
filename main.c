#include "includes.h"
#include "immigrant_factory.h"
#include "judge.h"

// Counters
int *NE;
int *NC;
int *NB;
int *action_counter;

// Semaphores
sem_t *action_mutex;
sem_t *judge_inside_mutex;
sem_t *immigrants_registered_mutex;

// Custom structs
action_counter_sync_t action_counter_sync;
semaphores_t semaphores;
immigrant_info_t immigrant_info;

void map_shared_mem()
{
  action_counter = init_global_var(sizeof action_counter);
  action_mutex = init_global_var(sizeof action_mutex);
  action_counter_sync.value = action_counter;
  action_counter_sync.mutex = action_mutex;
  *action_counter_sync.value = 0;

  immigrant_info.NE = init_global_var(sizeof NE);
  immigrant_info.NC = init_global_var(sizeof NC);
  immigrant_info.NB = init_global_var(sizeof NB);
  *immigrant_info.NE = 0;
  *immigrant_info.NC = 0;
  *immigrant_info.NB = 0;

  judge_inside_mutex = init_global_var(sizeof judge_inside_mutex);
  immigrants_registered_mutex = init_global_var(sizeof immigrants_registered_mutex);
  semaphores.immigrants_registered_mutex = immigrants_registered_mutex;
  semaphores.judge_inside_mutex = judge_inside_mutex;
}

void unmap_shared_mem()
{
  munmap(NULL, sizeof action_counter);
  munmap(NULL, sizeof action_mutex);
  munmap(NULL, sizeof NE);
  munmap(NULL, sizeof NC);
  munmap(NULL, sizeof NB);
  munmap(NULL, sizeof judge_inside_mutex);
  munmap(NULL, sizeof immigrants_registered_mutex);
}

void init_semaphores()
{
  sem_init(action_mutex, 1, 1);
  sem_init(judge_inside_mutex, 1, 1);
  sem_init(immigrants_registered_mutex, 1, 1);
}

void destroy_semaphores()
{
  sem_destroy(action_mutex);
  sem_destroy(judge_inside_mutex);
  sem_destroy(immigrants_registered_mutex);
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
        immigrant_factory(PI, action_counter_sync, immigrant_info, semaphores);
      }
      else if (pid_t == 0 && i == 1)
      {
        judge(action_counter_sync, immigrant_info, semaphores);
      }
    }
  }
}

int main(int argc, char **argv)
{

  map_shared_mem();
  init_semaphores();

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
  sleep(6);
  destroy_semaphores();
  unmap_shared_mem();
}

//TODO: make validation on command line parameters