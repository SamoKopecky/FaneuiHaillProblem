#include "judge.h"

void judge(action_counter_sync_t action_counter_sync, immigrant_info_t immigrant_info, semaphores_t semaphores)
{

    sleep(1);

    sem_wait(action_counter_sync.mutex);
    *action_counter_sync.value += 1;
    printf("%d\t: JUDGE\t: wants to enter\t\n", *action_counter_sync.value);
    sem_post(action_counter_sync.mutex);

    sem_wait(action_counter_sync.mutex);
    sem_wait(semaphores.judge_inside_mutex);
    *action_counter_sync.value += 1;
    printf("%d\t: JUDGE\t: enters\t\t: %d\t: %d\t: %d\n", *action_counter_sync.value, *immigrant_info.NE, *immigrant_info.NC, *immigrant_info.NB);
    sem_post(action_counter_sync.mutex);

    sem_trywait(semaphores.immigrants_registered_mutex);

    if (errno == EAGAIN)
    {
        sem_wait(action_counter_sync.mutex);
        *action_counter_sync.value += 1;
        printf("%d\t: JUDGE\t: waiting for imm\t: %d\t: %d\t: %d\n", *action_counter_sync.value, *immigrant_info.NE, *immigrant_info.NC, *immigrant_info.NB);
        sem_post(action_counter_sync.mutex);

        sem_wait(semaphores.immigrants_registered_mutex);
        sem_post(semaphores.immigrants_registered_mutex);
    }
    else
    {
        sem_post(semaphores.immigrants_registered_mutex);
    }

    sem_wait(action_counter_sync.mutex);
    *action_counter_sync.value += 1;
    printf("%d\t: JUDGE\t: starts confirmation\t: %d\t: %d\t: %d\n", *action_counter_sync.value, *immigrant_info.NE, *immigrant_info.NC, *immigrant_info.NB);
    sem_post(action_counter_sync.mutex);

    sem_wait(action_counter_sync.mutex);
    *action_counter_sync.value += 1;
    *immigrant_info.NE = 0;
    *immigrant_info.NC = 0;
    printf("%d\t: JUDGE\t: ends confirmation\t: %d\t: %d\t: %d\n", *action_counter_sync.value, *immigrant_info.NE, *immigrant_info.NC, *immigrant_info.NB);
    sem_post(action_counter_sync.mutex);
    sleep(2);

    sem_wait(action_counter_sync.mutex);
    *action_counter_sync.value += 1;
    printf("%d\t: JUDGE\t: leaves\t\t: %d\t: %d\t: %d\n", *action_counter_sync.value, *immigrant_info.NE, *immigrant_info.NC, *immigrant_info.NB);
    sem_post(action_counter_sync.mutex);
    sem_post(semaphores.judge_inside_mutex);

    exit(0);
}
