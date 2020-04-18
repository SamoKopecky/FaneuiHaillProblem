#ifndef IMMIGRANT_H_
#define IMMIGRANT_H_

#include "includes.h"

typedef struct immigrant_info immigrant_info_t;

struct immigrant_info
{
    int *NE;
    //sem_t *NE_mutex;
    int *NC;
    //sem_t *NC_mutex;
    int *NB;
    //sem_t *NB_mutex;
    int name;
};

void immigrant(action_counter_sync_t action_counter_sync, immigrant_info_t immigrant_info, sem_t *judge_inside_mutex, sem_t *immigrants_registered_mutex, sem_t *judge_waiting);

#endif