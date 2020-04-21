#include "includes.h"

void *init_global_var(int size)
{
    return mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
}

void millisleep(long int sleep_duration)
{

    if (sleep_duration == 0)
        return;
    const long int one_second = 1000000000;
    struct timespec tim, tim1;

    sleep_duration = sleep_duration * 1000000;
    const long int remainder = sleep_duration % one_second;
    tim.tv_sec = (sleep_duration - remainder) / one_second;
    tim.tv_nsec = remainder;
    nanosleep(&tim, &tim1);
}

void random_millisleep(int upper_bound)
{
    int random_value = random() % (upper_bound + 1);
    printf("%d\n", random_value);
    millisleep(random());
}

void write_to_file(char *text)
{
    FILE *file = fopen("proj2.out", "a");
    fputs(text, file);
    fclose(file);
}