#ifndef JUDGE_H_
#define JUDGE_H_

#include "../includes.h"
#include "../immigrant/immigrant.h"
#include "../utils/utils.h"
#include <errno.h>

void judge(input_t input, action_counter_sync_t action_counter_sync, immigrant_info_t immigrant_info, semaphores_t semaphores, FILE *output_file);

#endif