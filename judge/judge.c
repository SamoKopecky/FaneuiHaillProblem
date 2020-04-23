#include "judge.h"
#include <unistd.h>

int certified_immigrants_count = 0;
char string[100];

void judge(input_t input, action_counter_sync_t action_counter_sync, immigrant_info_t immigrant_info, semaphores_t semaphores, FILE *output_file)
{
    while (certified_immigrants_count < input.PI)
    {
        millisleep(input.timings[JG]);

        sem_wait(action_counter_sync.mutex);
        *action_counter_sync.value += 1;
        snprintf(string, 100, "%d\t: JUDGE\t: wants to enter\t\n", *action_counter_sync.value);
        write_to_file(string, output_file);
        sem_post(action_counter_sync.mutex);

        sem_wait(semaphores.test);
        sem_wait(semaphores.judge_inside_mutex);
        sem_wait(action_counter_sync.mutex);
        *action_counter_sync.value += 1;
        snprintf(string, 100, "%d\t: JUDGE\t: enters\t\t: %d\t: %d\t: %d\n", *action_counter_sync.value, *immigrant_info.NE, *immigrant_info.NC, *immigrant_info.NB);
        write_to_file(string, output_file);
        sem_post(action_counter_sync.mutex);

        sem_wait(action_counter_sync.mutex);
        sem_trywait(semaphores.immigrants_registered_mutex);
        /* sem_trywait sets errno to EAGAIN if the semaphore is beeing used */
        if (errno == EAGAIN)
        {
            errno = 0;
            *action_counter_sync.value += 1;
            snprintf(string, 100, "%d\t: JUDGE\t: waits for imm\t\t: %d\t: %d\t: %d\n", *action_counter_sync.value, *immigrant_info.NE, *immigrant_info.NC, *immigrant_info.NB);
            write_to_file(string, output_file);
            sem_post(action_counter_sync.mutex);
            sem_wait(semaphores.immigrants_registered_mutex);
            sem_post(semaphores.immigrants_registered_mutex);
        }
        else
        {
            sem_post(semaphores.immigrants_registered_mutex);
            sem_post(action_counter_sync.mutex);
        }

        sem_wait(action_counter_sync.mutex);
        *action_counter_sync.value += 1;
        snprintf(string, 100, "%d\t: JUDGE\t: starts confirmation\t: %d\t: %d\t: %d\n", *action_counter_sync.value, *immigrant_info.NE, *immigrant_info.NC, *immigrant_info.NB);
        write_to_file(string, output_file);
        sem_post(action_counter_sync.mutex);
        random_millisleep(input.timings[JT]);

        sem_wait(action_counter_sync.mutex);
        *action_counter_sync.value += 1;
        *immigrant_info.certificates_made_count = *immigrant_info.NE;
        certified_immigrants_count += *immigrant_info.NE;
        if (*immigrant_info.NE == 0)
        {
            sem_post(semaphores.test);
        }
        *immigrant_info.NE = 0;
        *immigrant_info.NC = 0;
        snprintf(string, 100, "%d\t: JUDGE\t: ends confirmation\t: %d\t: %d\t: %d\n", *action_counter_sync.value, *immigrant_info.NE, *immigrant_info.NC, *immigrant_info.NB);
        write_to_file(string, output_file);
        for (int i = 0; i < *immigrant_info.certificates_made_count; i++)
        {
            sem_post(semaphores.immigrants_certified);
        }
        sem_post(action_counter_sync.mutex);

        random_millisleep(input.timings[JT]);
        sem_wait(action_counter_sync.mutex);
        *action_counter_sync.value += 1;
        snprintf(string, 100, "%d\t: JUDGE\t: leaves\t\t: %d\t: %d\t: %d\n", *action_counter_sync.value, *immigrant_info.NE, *immigrant_info.NC, *immigrant_info.NB);
        write_to_file(string, output_file);
        sem_post(action_counter_sync.mutex);
        sem_post(semaphores.judge_inside_mutex);
    }

    sem_wait(action_counter_sync.mutex);
    *action_counter_sync.value += 1;
    snprintf(string, 100, "%d\t: JUDGE\t: finishes\n", *action_counter_sync.value);
    write_to_file(string, output_file);
    sem_post(action_counter_sync.mutex);

    exit(0);
}
