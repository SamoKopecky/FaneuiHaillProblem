#ifndef INCLUDES_H_
#define INCLUDES_H_

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>

struct process_counter
{
    int *value;
    sem_t *mutex;
};

#endif