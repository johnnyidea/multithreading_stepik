
#include <iostream>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MSG_PERM 0600

struct message {
    long mtype;
    char mtext[80];
};

int main(int argc,char** argv)
{
    key_t key = ftok("/tmp/msg.temp", 1);
    auto msqid = msgget (key, 0666 | IPC_CREAT);//(MSG_PERM |IPC_CREAT) );

    message msg;

    auto sz = msgrcv(msqid, &msg, 80, 0, 0);

    FILE *fp;
    fp = fopen("/home/box/message.txt", "w");
    fwrite(msg.mtext, sz, 1, fp);
    fclose(fp);

    return 0;
}
