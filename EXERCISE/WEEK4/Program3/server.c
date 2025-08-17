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
    int msqid;
    struct msgbuf buf;
    int len = sizeof(buf) - sizeof(long);

    msqid = msgget(1234, 0666);
    if(msqid < 0) {
        perror("msgget");
        exit(1);
    }

    msgrcv(msqid, &buf, len, 1, 0);

    char temp[100];
    for(int i = 0; buf.text[i] != '\0'; i++) {
        char c = buf.text[i];
        if(c >= 'a' && c <= 'z')
            temp[i] = (c - 'a' + 1) % 26 + 'a';
        else if(c >= 'A' && c <= 'Z')
            temp[i] = (c - 'A' + 1) % 26 + 'A';
        else
            temp[i] = c; 
    }
    temp[strlen(buf.text)] = '\0';

    printf("Original: %s\nCiphered: %s\n", buf.text, temp);

    // Send back encrypted message
    strcpy(buf.text, temp);
    buf.mtype = 2;
    if (msgsnd(msqid, &buf, len, IPC_NOWAIT) >= 0)
        printf("Ciphered message sent back to Client\n");

    return 0;
}
