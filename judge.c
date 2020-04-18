#include "judge.h"

void judge(action_counter_sync_t action_counter_sync, immigrant_info_t immigrant_info, sem_t *judge_inside_mutex, sem_t *immigrants_registered_mutex, sem_t *judge_waiting)
{

    sleep(1);

    sem_wait(action_counter_sync.mutex);
    sem_wait(judge_inside_mutex);
    *action_counter_sync.value += 1;
    printf("%d\t: JUDGE\t: wants to enter\t\n", *action_counter_sync.value);
    sem_post(action_counter_sync.mutex);

    *action_counter_sync.value += 1;
    printf("%d\t: JUDGE\t: enters\t: %d\t: %d\t: %d\n", *action_counter_sync.value, *immigrant_info.NE, *immigrant_info.NC, *immigrant_info.NB);

    sem_trywait(immigrants_registered_mutex);
    if (errno == EAGAIN)
    {
        *action_counter_sync.value += 1;
        printf("%d\t: JUDGE\t: waiting for imm\t: %d\t: %d\t: %d\n", *action_counter_sync.value, *immigrant_info.NE, *immigrant_info.NC, *immigrant_info.NB);
        sem_wait(immigrants_registered_mutex);
        sem_post(immigrants_registered_mutex);
    }

    *action_counter_sync.value += 1;
    printf("%d\t: JUDGE\t: starts confirmation\t: %d\t: %d\t: %d\n", *action_counter_sync.value, *immigrant_info.NE, *immigrant_info.NC, *immigrant_info.NB);

    sem_post(judge_inside_mutex);

    exit(0);
}
