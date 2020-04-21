#include "immigrant_factory.h"

void immigrant_factory(input_t input, action_counter_sync_t action_counter_sync, immigrant_info_t immigrant_info, semaphores_t semaphores)
{
    for (size_t i = 1; i <= input.PI; i++)
    {
        millisleep(input.timings[IG]);
        immigrant_info.name = i;
        if (fork() == 0)
        {
            immigrant(input, action_counter_sync, immigrant_info, semaphores);
        }
    }
    exit(0);
}