#include "immigrant_factory.h"

void immigrant_factory(input_t input, action_counter_sync_t action_counter_sync, immigrant_info_t immigrant_info, semaphores_t semaphores, FILE *output_file)
{
    int pid = 0;
    for (size_t i = 1; i <= input.PI; i++)
    {
        random_millisleep(input.timings[IG]);
        immigrant_info.name = i;
        if ((pid = fork()) == 0)
        {
            immigrant(input, action_counter_sync, immigrant_info, semaphores, output_file);
        }
        if (pid == -1)
        {
            fprintf(stderr, "Fork failed.\n");
            exit(1);
        }
    }
    for (size_t i = 0; i < input.PI; i++)
    {
        wait(NULL);
    }
    exit(0);
}