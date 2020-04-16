#include "imigrant_factory.h"

void create_imigrants(int PI)
{
    printf("factory\n");
    int pid_t = 0;
    for (size_t i = 0; i < PI; i++)
    {
        pid_t = fork();
        if (pid_t == 0)
        {
            imigrant();
        }
    }
    exit(0);
}