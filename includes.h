#ifndef INCLUDES_H_
#define INCLUDES_H_

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>

typedef struct action_counter_sync action_counter_sync_t;
typedef struct semaphores semaphores_t;
typedef struct immigrant_info immigrant_info_t;

struct action_counter_sync
{
    int *value;
    sem_t *mutex;
};

struct immigrant_info
{
    int *NE;
    int *NC;
    int *NB;
    int name;
};

struct semaphores
{
    sem_t *judge_inside_mutex;
    sem_t *immigrants_registered_mutex;
};

void *init_global_var(int size);

#endif