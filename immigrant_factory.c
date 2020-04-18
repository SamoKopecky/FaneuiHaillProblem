#include "immigrant_factory.h"

void immigrant_factory(int *PI, action_counter_sync_t action_counter_sync, immigrant_info_t immigrant_info, sem_t *judge_inside_mutex, sem_t *immigrants_registered_mutex, sem_t *judge_waiting)
{
    for (size_t i = 1; i <= *PI; i++)
    {
        immigrant_info.name = i;
        if (fork() == 0)
        {
            immigrant(action_counter_sync, immigrant_info, judge_inside_mutex, immigrants_registered_mutex, judge_waiting);
        }
    }
    exit(0);
}

void create_immigrants()
{
}