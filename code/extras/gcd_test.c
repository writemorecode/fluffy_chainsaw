#include <stdio.h>
#include <stdlib.h>
#include "gcd.h"

int gcd_(int a, int b)
{
    while(a != b)
    {
        if (a > b)
        {
            a = a-b;
        }
        else
        {
            b = b-a;
        }
    }
    return a;
}

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        return 1;
    } 

    int a = atoi(argv[1]);
    int b = atoi(argv[2]);

    int d = gcd(a, b);
    int d_ = gcd_(a, b);
    printf("GCD %d %d = %d (%d)\n", a,b,d,d_);
}


