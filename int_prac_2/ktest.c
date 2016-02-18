#include <stdio.h>

#define M 9
#define N 5

int NUM[M];

void Perm(int n, int a)
{
    int i;
    static int c;
    if (n == N)
    {
        printf("%4d : ", ++c);
        for (i = 0; i < N; i++)
        {
            printf("%3d", NUM[i]);
        }
        printf("\n");
        return;
    }

    for (i = a+1; i <= M; i++)
    {
        NUM[n] = i;
        Perm(n+1, i);
    }
}

int main()
{
    Perm(0, 0);
    return 0;
}