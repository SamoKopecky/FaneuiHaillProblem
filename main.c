#include "includes.h"
#include "utils/utils.h"
#include "immigrant_factory/immigrant_factory.h"
#include "judge/judge.h"
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

/* Counters in shared memory */
int *A;
int *NE;
int *NC;
int *NB;

/* Semaphores */
sem_t *A_mutex;
sem_t *judge_inside_mutex;
sem_t *immigrant_registered_mutex;
sem_t *immigrants_certified_mutex;

/* Custom structs for passing arguments to functions, defined in #includes.h */
action_counter_sync_t action_counter_sync;
semaphores_t semaphores;
immigrant_info_t immigrant_info;
input_t input;

/* Outputs fo the processes are written here */
FILE *output_file;

void map_shared_mem()
{
  A = map_shared_variable(sizeof A);
  A_mutex = map_shared_variable(sizeof A_mutex);
  action_counter_sync.value = A;
  action_counter_sync.mutex = A_mutex;

  immigrant_info.NE = map_shared_variable(sizeof NE);
  immigrant_info.NC = map_shared_variable(sizeof NC);
  immigrant_info.NB = map_shared_variable(sizeof NB);

  judge_inside_mutex = map_shared_variable(sizeof judge_inside_mutex);
  immigrant_registered_mutex = map_shared_variable(sizeof immigrant_registered_mutex);
  immigrants_certified_mutex = map_shared_variable(sizeof immigrants_certified_mutex);
  semaphores.immigrants_registered_mutex = immigrant_registered_mutex;
  semaphores.judge_inside_mutex = judge_inside_mutex;
  semaphores.immigrants_certified = immigrants_certified_mutex;
}

void init_shared_counters()
{
  *action_counter_sync.value = 0;
  *immigrant_info.NE = 0;
  *immigrant_info.NC = 0;
  *immigrant_info.NB = 0;
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
  munmap(NULL, sizeof immigrants_certified_mutex);
}

void init_semaphores()
{
  sem_init(A_mutex, 1, 1);
  sem_init(judge_inside_mutex, 1, 1);
  sem_init(immigrant_registered_mutex, 1, 1);
  sem_init(immigrants_certified_mutex, 1, 0);
}

void destroy_semaphores()
{
  sem_destroy(A_mutex);
  sem_destroy(judge_inside_mutex);
  sem_destroy(immigrant_registered_mutex);
  sem_destroy(immigrants_certified_mutex);
}

void create_children()
{
  int pid = 0;
  for (int i = 0; i < 2; i++)
  {
    {
      if ((pid = fork()) == 0 && i == 0)
      {
        immigrant_factory(input, action_counter_sync, immigrant_info, semaphores, output_file);
      }
      else if (pid == 0 && i == 1)
      {
        judge(input, action_counter_sync, immigrant_info, semaphores, output_file);
      }
      else if (pid == -1)
      {
        fprintf(stderr, "Fork failed.\n");
        exit(1);
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
  validate_input(argc, argv);
  map_shared_mem();
  init_shared_counters();
  init_semaphores();
  create_children();
  /* Waiting for immigrant_factory and judge to exit */
  for (size_t i = 0; i < 2; i++)
  {
    /* -1 means wait for any child that exists */
    waitpid(-1, NULL, 0);
  }
  destroy_semaphores();
  unmap_shared_mem();
  fclose(output_file);
  exit(0);
}

/*
TODO: update Makefile
*/