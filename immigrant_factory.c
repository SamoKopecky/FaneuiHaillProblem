#include "immigrant_factory.h"

void immigrant_factory(int *PI)
{
    create_immigrants(PI);
}

void create_immigrants(int *PI)
{
    printf("factory\n");
    for (size_t i = 0; i < *PI; i++)
    {
        if (fork() == 0)
        {
            immigrant();
        }
    }
    exit(0);
}