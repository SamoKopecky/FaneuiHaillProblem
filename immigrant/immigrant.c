#include "immigrant.h"

void immigrant(action_counter_sync_t action_counter_sync, immigrant_info_t immigrant_info, semaphores_t semaphores)
{

    sem_wait(action_counter_sync.mutex);
    *action_counter_sync.value += 1;
    printf("%d\t: IMM %d\t: starts\n", *action_counter_sync.value, immigrant_info.name);
    sem_post(action_counter_sync.mutex);

    if (immigrant_info.name == 2)
    {
        sleep(3);
    }

    sem_wait(semaphores.judge_inside_mutex);
    sem_wait(action_counter_sync.mutex);
    *action_counter_sync.value += 1;
    *immigrant_info.NE += 1;
    *immigrant_info.NB += 1;
    printf("%d\t: IMM %d\t: enters\t\t: %d\t: %d\t: %d\n", *action_counter_sync.value, immigrant_info.name, *immigrant_info.NE, *immigrant_info.NC, *immigrant_info.NB);
    sem_post(semaphores.judge_inside_mutex);
    sem_post(action_counter_sync.mutex);
    sem_wait(semaphores.immigrants_registered_mutex);

    if (immigrant_info.name == 1)
    {
        sleep(3);
    }

    sem_wait(action_counter_sync.mutex);
    *action_counter_sync.value += 1;
    *immigrant_info.NC += 1;
    printf("%d\t: IMM %d\t: checks\t\t: %d\t: %d\t: %d\n", *action_counter_sync.value, immigrant_info.name, *immigrant_info.NE, *immigrant_info.NC, *immigrant_info.NB);
    sem_post(action_counter_sync.mutex);
    sem_post(semaphores.immigrants_registered_mutex);

    sem_wait(semaphores.judge_inside_mutex);
    sem_wait(action_counter_sync.mutex);
    *action_counter_sync.value += 1;

    printf("%d\t: IMM %d\t: leaves\t\t: %d\t: %d\t: %d\n", *action_counter_sync.value, immigrant_info.name, *immigrant_info.NE, *immigrant_info.NC, *immigrant_info.NB);
    sem_post(action_counter_sync.mutex);
    sem_post(semaphores.judge_inside_mutex);

    exit(0);
}
