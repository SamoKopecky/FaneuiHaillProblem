#include <sys/mman.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
   // printf() displays the string inside quotation
   printf("Hello, World!");
   printf("make works\n");
   fork();
   sleep(50000);
}
