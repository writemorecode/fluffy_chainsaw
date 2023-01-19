#include <stdio.h>
#include <stdlib.h>
#include "factorial.h"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        return 1;
    } 

    int n = atoi(argv[1]);
    int f = factorial(n);
    printf("%d! = %d\n", n, f);
}


