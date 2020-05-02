#ifndef INCLUDES_H_
#define INCLUDES_H_

#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

/* indices for timming array in input struct */
#define IG 0
#define JG 1
#define IT 2
#define JT 3

typedef struct action_counter_sync action_counter_sync_t;
typedef struct semaphores semaphores_t;
typedef struct immigrant_info immigrant_info_t;
typedef struct input input_t;

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
    int *certificates_made_count;
    int name;
};

struct input
{
    int PI;
    int timings[4];
};

struct semaphores
{
    sem_t *judge_inside_mutex;
    sem_t *immigrants_registered_mutex;
    sem_t *immigrants_certified_mutex;
    sem_t *certificates_taken_mutex;
};

#endif