#include "immigrant.h"
#include <unistd.h>

char string[100];

void immigrant(input_t input, action_counter_sync_t action_counter_sync, immigrant_info_t immigrant_info, semaphores_t semaphores, FILE *output_file)
{
    sem_wait(action_counter_sync.mutex);
    *action_counter_sync.value += 1;
    printf("%d\t: IMM %d\t: starts\n", *action_counter_sync.value, immigrant_info.name);
    snprintf(string, 100, "%d\t: IMM %d\t: starts\n", *action_counter_sync.value, immigrant_info.name);
    write_to_file(string, output_file);
    sem_post(action_counter_sync.mutex);

    sem_wait(semaphores.test);
    sem_post(semaphores.test);
    sem_wait(semaphores.judge_inside_mutex);
    sem_wait(action_counter_sync.mutex);
    *action_counter_sync.value += 1;
    *immigrant_info.NE += 1;
    *immigrant_info.NB += 1;
    printf("%d\t: IMM %d\t: enters\t\t: %d\t: %d\t: %d\n", *action_counter_sync.value, immigrant_info.name, *immigrant_info.NE, *immigrant_info.NC, *immigrant_info.NB);
    snprintf(string, 100, "%d\t: IMM %d\t: enters\t\t: %d\t: %d\t: %d\n", *action_counter_sync.value, immigrant_info.name, *immigrant_info.NE, *immigrant_info.NC, *immigrant_info.NB);
    write_to_file(string, output_file);
    sem_post(semaphores.judge_inside_mutex);
    sem_post(action_counter_sync.mutex);

    sem_wait(semaphores.immigrants_registered_mutex);
    sem_wait(action_counter_sync.mutex);
    *action_counter_sync.value += 1;
    *immigrant_info.NC += 1;
    sem_post(semaphores.immigrants_registered_mutex);
    printf("%d\t: IMM %d\t: checks\t\t: %d\t: %d\t: %d\n", *action_counter_sync.value, immigrant_info.name, *immigrant_info.NE, *immigrant_info.NC, *immigrant_info.NB);
    snprintf(string, 100, "%d\t: IMM %d\t: checks\t\t: %d\t: %d\t: %d\n", *action_counter_sync.value, immigrant_info.name, *immigrant_info.NE, *immigrant_info.NC, *immigrant_info.NB);
    write_to_file(string, output_file);
    sem_post(action_counter_sync.mutex);

    sem_wait(semaphores.immigrants_certified);
    sem_wait(action_counter_sync.mutex);
    *action_counter_sync.value += 1;
    printf("%d\t: IMM %d\t: wants certificate\t: %d\t: %d\t: %d\n", *action_counter_sync.value, immigrant_info.name, *immigrant_info.NE, *immigrant_info.NC, *immigrant_info.NB);
    snprintf(string, 100, "%d\t: IMM %d\t: wants certificate\t: %d\t: %d\t: %d\n", *action_counter_sync.value, immigrant_info.name, *immigrant_info.NE, *immigrant_info.NC, *immigrant_info.NB);
    write_to_file(string, output_file);
    sem_post(action_counter_sync.mutex);
    random_millisleep(input.timings[IT]);

    sem_wait(action_counter_sync.mutex);
    *action_counter_sync.value += 1;
    printf("%d\t: IMM %d\t: got certificate\t: %d\t: %d\t: %d\n", *action_counter_sync.value, immigrant_info.name, *immigrant_info.NE, *immigrant_info.NC, *immigrant_info.NB);
    snprintf(string, 100, "%d\t: IMM %d\t: got certificate\t: %d\t: %d\t: %d\n", *action_counter_sync.value, immigrant_info.name, *immigrant_info.NE, *immigrant_info.NC, *immigrant_info.NB);
    write_to_file(string, output_file);
    *immigrant_info.certificates_made -= 1;
    if (*immigrant_info.certificates_made == 0)
    {
        sem_post(semaphores.test);
    }
    sem_post(action_counter_sync.mutex);

    sem_wait(semaphores.judge_inside_mutex);
    sem_wait(action_counter_sync.mutex);
    *action_counter_sync.value += 1;
    *immigrant_info.NB -= 1;
    printf("%d\t: IMM %d\t: leaves\t\t: %d\t: %d\t: %d\n", *action_counter_sync.value, immigrant_info.name, *immigrant_info.NE, *immigrant_info.NC, *immigrant_info.NB);
    snprintf(string, 100, "%d\t: IMM %d\t: leaves\t\t: %d\t: %d\t: %d\n", *action_counter_sync.value, immigrant_info.name, *immigrant_info.NE, *immigrant_info.NC, *immigrant_info.NB);
    write_to_file(string, output_file);
    sem_post(action_counter_sync.mutex);
    sem_post(semaphores.judge_inside_mutex);

    exit(0);
}
