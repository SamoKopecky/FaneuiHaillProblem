#include "includes.h"
#include "immigrant_factory/immigrant_factory.h"
#include "judge/judge.h"

// Counters in shared memory
int *A;
int *NE;
int *NC;
int *NB;

// Semaphores
sem_t *A_mutex;
sem_t *judge_inside_mutex;
sem_t *immigrant_registered_mutex;
sem_t *immigrants_certified;

// Custom structs
action_counter_sync_t action_counter_sync;
semaphores_t semaphores;
immigrant_info_t immigrant_info;
timings_t timings;

void map_shared_mem()
{
  A = init_global_var(sizeof A);
  A_mutex = init_global_var(sizeof A_mutex);
  action_counter_sync.value = A;
  action_counter_sync.mutex = A_mutex;
  *action_counter_sync.value = 0;

  immigrant_info.NE = init_global_var(sizeof NE);
  immigrant_info.NC = init_global_var(sizeof NC);
  immigrant_info.NB = init_global_var(sizeof NB);
  *immigrant_info.NE = 0;
  *immigrant_info.NC = 0;
  *immigrant_info.NB = 0;

  judge_inside_mutex = init_global_var(sizeof judge_inside_mutex);
  immigrant_registered_mutex = init_global_var(sizeof immigrant_registered_mutex);
  immigrants_certified = init_global_var(sizeof immigrants_certified);
  semaphores.immigrants_registered_mutex = immigrant_registered_mutex;
  semaphores.judge_inside_mutex = judge_inside_mutex;
  semaphores.immigrants_certified = immigrants_certified;
}

void unmap_shared_mem()
{
  munmap(NULL, sizeof A);
  munmap(NULL, sizeof A_mutex);
  munmap(NULL, sizeof NE);
  munmap(NULL, sizeof NC);
  munmap(NULL, sizeof NB);
  munmap(NULL, sizeof judge_inside_mutex);
  munmap(NULL, sizeof immigrant_registered_mutex);
  munmap(NULL, sizeof immigrants_certified);
}

void init_semaphores()
{
  sem_init(A_mutex, 1, 1);
  sem_init(judge_inside_mutex, 1, 1);
  sem_init(immigrant_registered_mutex, 1, 1);
  sem_init(immigrants_certified, 1, 0);
}

void destroy_semaphores()
{
  sem_destroy(A_mutex);
  sem_destroy(judge_inside_mutex);
  sem_destroy(immigrant_registered_mutex);
  sem_destroy(immigrants_certified);
}

int string_to_int(char *string)
{

  return (int)strtol(string, NULL, 10);
}

void create_children()
{
  int pid_t = 0;
  for (int i = 0; i < 2; i++)
  {
    {
      if ((pid_t = fork()) == 0 && i == 0)
      {
        immigrant_factory(timings, action_counter_sync, immigrant_info, semaphores);
      }
      else if (pid_t == 0 && i == 1)
      {
        judge(timings, action_counter_sync, immigrant_info, semaphores);
      }
    }
  }
}

int main(int argc, char **argv)
{

  map_shared_mem();
  init_semaphores();

  timings.PI = string_to_int(argv[1]);
  timings.IG = string_to_int(argv[2]);
  timings.JG = string_to_int(argv[3]);
  timings.IT = string_to_int(argv[4]);
  timings.JT = string_to_int(argv[5]);

  create_children();
  sleep(20);
  destroy_semaphores();
  unmap_shared_mem();
}