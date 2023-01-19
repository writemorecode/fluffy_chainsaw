#include <stdio.h>
#include "lntwo.h"

int main()
{
    for (int i = 1; i <= 10; i++)
    {
        int n = 2 << (i-1);
        int ln = lntwo(n);
        printf("ln2(%d) = \t%d\n", n, ln);
    }
}
