#include "includes.h"


void *init_global_var(int size)
{
    return mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
}