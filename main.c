#include "includes.h"
#include "immigrant_factory/immigrant_factory.h"
#include "judge/judge.h"
#include <string.h>

#define _GNU_SOURCE

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
input_t input;

FILE *output_file;

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

void create_children()
{
  int pid_t = 0;
  for (int i = 0; i < 2; i++)
  {
    {
      if ((pid_t = fork()) == 0 && i == 0)
      {
        immigrant_factory(input, action_counter_sync, immigrant_info, semaphores, output_file);
      }
      else if (pid_t == 0 && i == 1)
      {
        judge(input, action_counter_sync, immigrant_info, semaphores, output_file);
      }
    }
  }
}

void validate_input(int argc, char **argv)
{
  const int argument_offset = 2;
  const int max_value = 2000;
  const int min_value = 0;
  const int number_of_arguments = 6;

  if (argc != number_of_arguments)
  {
    fprintf(stderr, "Wrong number of arguments.\n");
    exit(1);
  }

  input.PI = (int)strtol(argv[1], NULL, 10);

  int value = 0;
  for (size_t i = IG; i <= JT; i++)
  {

    value = (int)strtol(argv[i + argument_offset], NULL, 10);
    if (value >= min_value && value <= max_value)
    {
      input.timings[i] = value;
    }
    else
    {
      fprintf(stderr, "Timings have to be bigger then 0 and lower then 2000.\n");
      exit(1);
    }
  }
}

int main(int argc, char **argv)
{
  output_file = fopen("proj2.out", "w+");
  fclose(output_file);
  validate_input(argc, argv);
  map_shared_mem();
  init_semaphores();
  create_children();
  for (size_t i = 0; i < 2; i++)
  {
    wait(NULL);
  }
  destroy_semaphores();
  unmap_shared_mem();
  exit(0);
}

/*
TODO: optimize file writing, test, comments, update Makefile, edit wait(NULL) to waitpid or waitid
*/