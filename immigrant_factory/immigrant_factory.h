#ifndef IMMIGRANT_FACTORY_H_
#define IMMIGRANT_FACTORY_H_

#include "immigrant.h"
#include "includes.h"
#include <time.h>

void immigrant_factory(int *PI_ptr, action_counter_sync_t action_counter_sync, immigrant_info_t immigrant_info, semaphores_t semaphores);

#endif