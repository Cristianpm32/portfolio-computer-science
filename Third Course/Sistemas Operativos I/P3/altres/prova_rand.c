#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N 10

int main()
{

    for (int i = 0; i < N; i++)
    {
        generateRandom();
    }
}
int generateRandom()
{

    int fill1 = fork();
    if (fill1 == 0)
    {
        int fill2 = fork();
        if (fill2 == 0)
        {
            // fill2
            srand(fill2);
            printf("%d\n", rand());
            exit(0);
        }
        else
        {
            // fill1
            printf("%d\n", rand());
            srand(fill1);
            exit(0);
        }
    }
}
