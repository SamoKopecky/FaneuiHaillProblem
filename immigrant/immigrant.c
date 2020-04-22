#include "immigrant.h"

char text[100];

void immigrant(input_t input, action_counter_sync_t action_counter_sync, immigrant_info_t immigrant_info, semaphores_t semaphores, FILE *output_file)
{

    sem_wait(action_counter_sync.mutex);
    *action_counter_sync.value += 1;
    printf("%d\t: IMM %d\t: starts\n", *action_counter_sync.value, immigrant_info.name);
    /* snprintf(text, 100, "%d\t: IMM %d\t: starts\n", *action_counter_sync.value, immigrant_info.name);
    write_to_file(text); */
    sem_post(action_counter_sync.mutex);

    sem_wait(semaphores.judge_inside_mutex);
    sem_wait(action_counter_sync.mutex);
    *action_counter_sync.value += 1;
    *immigrant_info.NE += 1;
    *immigrant_info.NB += 1;
    printf("%d\t: IMM %d\t: enters\t\t: %d\t: %d\t: %d\n", *action_counter_sync.value, immigrant_info.name, *immigrant_info.NE, *immigrant_info.NC, *immigrant_info.NB);
    /* snprintf("%d\t: IMM %d\t: enters\t\t: %d\t: %d\t: %d\n", *action_counter_sync.value, immigrant_info.name, *immigrant_info.NE, *immigrant_info.NC, *immigrant_info.NB);
    write_to_file(text); */
    sem_post(semaphores.judge_inside_mutex);
    sem_post(action_counter_sync.mutex);
    sem_wait(semaphores.immigrants_registered_mutex);

    sem_wait(action_counter_sync.mutex);
    *action_counter_sync.value += 1;
    *immigrant_info.NC += 1;
    printf("%d\t: IMM %d\t: checks\t\t: %d\t: %d\t: %d\n", *action_counter_sync.value, immigrant_info.name, *immigrant_info.NE, *immigrant_info.NC, *immigrant_info.NB);
    /* snprintf(text, 100, "%d\t: IMM %d\t: checks\t\t: %d\t: %d\t: %d\n", *action_counter_sync.value, immigrant_info.name, *immigrant_info.NE, *immigrant_info.NC, *immigrant_info.NB);
    write_to_file(text); */
    sem_post(semaphores.immigrants_registered_mutex);
    sem_post(action_counter_sync.mutex);
    sem_wait(semaphores.immigrants_certified);

    sem_wait(action_counter_sync.mutex);
    *action_counter_sync.value += 1;
    printf("%d\t: IMM %d\t: wants certificate\t: %d\t: %d\t: %d\n", *action_counter_sync.value, immigrant_info.name, *immigrant_info.NE, *immigrant_info.NC, *immigrant_info.NB);
    /* snprintf(text, 100, "%d\t: IMM %d\t: wants certificate\t: %d\t: %d\t: %d\n", *action_counter_sync.value, immigrant_info.name, *immigrant_info.NE, *immigrant_info.NC, *immigrant_info.NB);
    write_to_file(text); */
    sem_post(action_counter_sync.mutex);

    random_millisleep(input.timings[IT]);

    sem_wait(action_counter_sync.mutex);
    *action_counter_sync.value += 1;
    printf("%d\t: IMM %d\t: got certificate\t: %d\t: %d\t: %d\n", *action_counter_sync.value, immigrant_info.name, *immigrant_info.NE, *immigrant_info.NC, *immigrant_info.NB);
    /* snprintf(text, 100, "%d\t: IMM %d\t: got certificate\t: %d\t: %d\t: %d\n", *action_counter_sync.value, immigrant_info.name, *immigrant_info.NE, *immigrant_info.NC, *immigrant_info.NB);
    write_to_file(text); */
    sem_post(action_counter_sync.mutex);

    sem_wait(semaphores.judge_inside_mutex);
    sem_wait(action_counter_sync.mutex);
    *action_counter_sync.value += 1;
    *immigrant_info.NB -= 1;
    printf("%d\t: IMM %d\t: leaves\t\t: %d\t: %d\t: %d\n", *action_counter_sync.value, immigrant_info.name, *immigrant_info.NE, *immigrant_info.NC, *immigrant_info.NB);
    /* snprintf(text, 100, "%d\t: IMM %d\t: leaves\t\t: %d\t: %d\t: %d\n", *action_counter_sync.value, immigrant_info.name, *immigrant_info.NE, *immigrant_info.NC, *immigrant_info.NB);
    write_to_file(text); */
    sem_post(action_counter_sync.mutex);
    sem_post(semaphores.judge_inside_mutex);
    exit(0);
}
