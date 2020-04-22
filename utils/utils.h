#ifndef UTILS_H_
#define UTILS_H_

#include "../includes.h"
#include <time.h>
#include <sys/mman.h>

void *map_shared_variable(int size);
int millisleep(long int sleep_duration);
int random_millisleep(int upper_bound);
void write_to_file(char *text);

#endif