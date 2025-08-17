#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>

struct msgbuf {
    long mtype;
    float num[3];
    char op;
};

int main() {
    struct msgbuf buf;
    int len = sizeof(buf) - sizeof(long);

    int msqid = msgget(1234, IPC_CREAT | 0666);

    // Receive client request
    msgrcv(msqid, &buf, len, 1, 0);

    float a = buf.num[0], b = buf.num[1], ans = 0;
    char c = buf.op;

    switch (c) {
        case '+': ans = a + b; break;
        case '-': ans = a - b; break;
        case '*': ans = a * b; break;
        case '/': ans = (b != 0) ? a / b : 0; break;
        default: printf("Invalid operator!\n"); break;
    }

    buf.num[2] = ans;
    buf.mtype = 2;

    printf("Server Computed: %f %c %f = %f\n", a, c, b, ans);

    if (msgsnd(msqid, &buf, len, 0) >= 0)
        printf("Result sent back to Client\n");

    // Remove message queue
    msgctl(msqid, IPC_RMID, NULL);

    return 0;
}
