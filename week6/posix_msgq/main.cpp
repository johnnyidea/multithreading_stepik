#include <iostream>

#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>

#define PMODE 0666
#define MAX_SIZE 512

int main(int argc,char** argv)
{
    mqd_t mq;
    struct mq_attr attr;
    char buffer[MAX_SIZE];
    int must_stop = 0;

    /* initialize the queue attributes */
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = MAX_SIZE;
    attr.mq_curmsgs = 0;

    /* create the message queue */
    mq = mq_open("/home/rene/education/multithreading_stepik/week6/posix_msgq/test", O_CREAT | O_RDONLY, 0644, &attr);

    if (mq == -1)
    {
        perror("mq_open failure from main");
        exit(0);
    };

    auto bytes_read = mq_receive(mq, buffer, MAX_SIZE, NULL);

    if (mq_close(mq) == -1)
        perror("mq_close failure on mqfd");

    FILE * fp;
    fp = fopen("/home/box/message.txt", "w");
    fwrite(buffer, bytes_read, 1, fp);
    fclose(fp);

    return 0;
}


/*
struct mq_attr attr;
attr.mq_maxmsg = 10;
attr.mq_msgsize = 512;
attr.mq_flags   = 0;
attr.mq_curmsgs = 0;


int open_flags = O_CREAT | O_RDONLY;
auto mqfd = mq_open("/home/rene/education/multithreading_stepik/week6/posix_msgq/test.mq", open_flags, PMODE, &attr);

if (mqfd == -1)
{
    perror("mq_open failure from main");
    exit(0);
};

char* msg;
auto sz_recv = mq_receive(mqfd, msg, 512, NULL);


if (mq_close(mqfd) == -1)
    perror("mq_close failure on mqfd");

FILE * fp;
fp = fopen("/home/box/message.txt", "w");
fwrite(msg, sz_recv, 1, fp);
fclose(fp);
*/