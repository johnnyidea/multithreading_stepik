#include <iostream>
#include <signal.h>

int main()
{
    signal(SIGALRM, SIG_IGN);

    signal(SIGTERM, SIG_IGN);
    signal(SIGINT, SIG_IGN);
    alarm(10);
    pause();
    return 0;
}
