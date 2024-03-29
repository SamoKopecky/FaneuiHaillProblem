#ifndef IMMIGRANT_FACTORY_H_
#define IMMIGRANT_FACTORY_H_

#include "../immigrant/immigrant.h"
#include "../includes.h"
#include "../utils/utils.h"
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

void immigrant_factory(input_t input, action_counter_sync_t action_counter_sync, immigrant_info_t immigrant_info, semaphores_t semaphores, FILE *output_file);

#endif