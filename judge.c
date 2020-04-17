#include "judge.h"

void judge(int *counter, sem_t *counter_mutex)
{
    sem_wait(counter_mutex);
    *counter += 1;
    sem_post(counter_mutex);

    printf("judge\n");
    exit(0);
}