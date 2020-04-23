#include "utils.h"

void *map_shared_variable(int size)
{
    return mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
}

int millisleep(long int sleep_duration)
{
    if (sleep_duration == 0)
        return 0;
    const long int one_second_in_nano = 1000000000;
    struct timespec tim, tim1;
    
    sleep_duration = sleep_duration * 1000000;                      /* convert from milli to nano */
    const long int remainder = sleep_duration % one_second_in_nano; /* get the decimal numbers etc. 4.2 -> remainder = 0.2 */
    tim.tv_sec = (sleep_duration - remainder) / one_second_in_nano;
    tim.tv_nsec = remainder;
    return nanosleep(&tim, &tim1);
}

int random_millisleep(int upper_bound)
{
    int random_value = random() % (upper_bound + 1);
    return millisleep(random_value);
}

void write_to_file(char *text, FILE *file)
{
    if (file == NULL)
    {
        fprintf(stderr, "Failed to open or create a file.\n");
        exit(1);
    }
    fputs(text, file);
    fflush(file);
}