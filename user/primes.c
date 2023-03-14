#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void subprocess(int p[2])
{
    int prime, x, q[2];
    close(p[1]);
    if (read(p[0], &prime, 4) != 4)
        exit(0);
    fprintf(1, "prime %d\n", prime);
    pipe(q);
    if (fork())
    {
        close(q[0]);
        while (read(p[0], &x, 4) == 4)
            if (x % prime != 0)
                write(q[1], &x, 4);
        close(p[0]);
        close(q[1]);
        wait(0);
    }
    else
    {
        close(p[0]);
        subprocess(q);
    }
}
int main(int argc, char *argv[])
{
    int i, p[2];
    pipe(p);
    if (fork())
    {
        close(p[0]);
        for (i = 2; i <= 35; i++)
            write(p[1], &i, 4);
        close(p[1]);
        wait(0);
    }
    else
    {
        subprocess(p);
    }
    exit(0);
}
