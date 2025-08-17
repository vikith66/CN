#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>

struct msgbuf {
    long mtype;
    float num[3]; // [0] and [1] for input, [2] for result
    char op;
};

int main() {
    struct msgbuf buf;
    int len = sizeof(buf) - sizeof(long);
    int msqid = msgget(1234, IPC_CREAT | 0666);

    buf.mtype = 1;

    printf("Enter Two numbers: ");
    scanf("%f %f", &buf.num[0], &buf.num[1]);

    printf("Enter operator (+,-,*,/): ");
    scanf(" %c", &buf.op);

    if (msgsnd(msqid, &buf, len, 0) >= 0)
        printf("Message Sent to Server\n");

    // Receive answer
    msgrcv(msqid, &buf, len, 2, 0);
    printf("Result received from Server: %f\n", buf.num[2]);

    return 0;
}
