#ifndef IMMIGRANT_H_
#define IMMIGRANT_H_

#include "../includes.h"
#include <sched.h>

void immigrant(input_t input, action_counter_sync_t action_counter_sync, immigrant_info_t immigrant_info, semaphores_t semaphores);

#endif