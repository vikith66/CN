#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>

struct Array {
    int arr[100];
    int n;
};

struct msg_Buffer {
    long msg_type;
    struct Array a;
} message;

int main() {
    key_t key;
    int msgid;

    key = 1001;
    msgid = msgget(key, 0666 | IPC_CREAT);

    msgrcv(msgid, &message, sizeof(message.a), 1, 0);

    printf("\nArray received: ");
    for (int i = 0; i < message.a.n; i++) {
        printf("%d ", message.a.arr[i]);
    }

    // Sorting
    for (int i = 0; i < message.a.n - 1; i++) {
        for (int j = i + 1; j < message.a.n; j++) {
            if (message.a.arr[i] > message.a.arr[j]) {
                int temp = message.a.arr[i];
                message.a.arr[i] = message.a.arr[j];
                message.a.arr[j] = temp;
            }
        }
    }

    printf("\nSorted Array: ");
    for (int i = 0; i < message.a.n; i++) {
        printf("%d ", message.a.arr[i]);
    }

    // Remove first queue
    msgctl(msgid, IPC_RMID, NULL);

    // Send sorted array back
    key = 1002;
    msgid = msgget(key, 0666 | IPC_CREAT);

    message.msg_type = 1;
    msgsnd(msgid, &message, sizeof(message.a), 0);

    printf("\nSorted Array sent back to client\n");

    // Remove second queue
    msgctl(msgid, IPC_RMID, NULL);

    return 0;
}
