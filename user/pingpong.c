#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    int p[2];
    char s[4];
    pipe(p);
    if (fork() != 0)
    {
        write(p[1], "ping", 4);
        close(p[1]);
        wait(0);
        read(p[0], s, 4);
        close(p[0]);
        fprintf(1, "%d: received %s\n", getpid(), s);
    }
    else
    {
        read(p[0], s, 4);
        close(p[0]);
        fprintf(1, "%d: received %s\n", getpid(), s);
        write(p[1], "pong", 4);
        close(p[1]);
    }
    exit(0);
}
