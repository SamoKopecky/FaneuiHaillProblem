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

struct action_counter_sync
{
    int *value;
    sem_t *mutex;
};

void *init_global_var(int size);

#endif