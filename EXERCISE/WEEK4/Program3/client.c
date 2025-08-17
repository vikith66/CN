#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct msgbuf {
    long mtype;
    char text[100];
};

int main() {
    struct msgbuf buf;
    int len = sizeof(buf) - sizeof(long);

    int msqid = msgget(1234, IPC_CREAT | 0777);
    if(msqid < 0) {
        perror("msgget");
        exit(1);
    }

    buf.mtype = 1;
    printf("Enter text: ");
    fgets(buf.text, sizeof(buf.text), stdin);
    buf.text[strcspn(buf.text, "\n")] = '\0'; // remove newline

    if (msgsnd(msqid, &buf, len, IPC_NOWAIT) >= 0)
        printf("Message Sent to Server\n");

    // Receive encrypted text back
    msgrcv(msqid, &buf, len, 2, 0);
    printf("Ciphered Text: %s\n", buf.text);

    // Remove queue (optional, usually server does this)
    msgctl(msqid, IPC_RMID, 0);

    return 0;
}
