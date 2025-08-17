#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

#define KEY 1234

struct request {
    long mtype;
    char name[50], phone[15];
    int category, num_tickets;
    pid_t pid;
};

struct response {
    long mtype;
    char text[200];
};

int main() {
    int qid = msgget(KEY, 0666);
    if (qid == -1) {
        perror("msgget");
        exit(1);
    }

    struct request r; 
    struct response s;

    r.mtype = 1;
    r.pid = getpid();

    printf("Enter Name: ");
    fgets(r.name, 50, stdin);
    r.name[strcspn(r.name, "\n")] = 0;

    printf("Enter Phone: ");
    fgets(r.phone, 15, stdin);
    r.phone[strcspn(r.phone, "\n")] = 0;

    printf("Enter Category (1-5): ");
    scanf("%d", &r.category);

    printf("Enter Number of tickets (-1 to exit): ");
    scanf("%d", &r.num_tickets);

    if (msgsnd(qid, &r, sizeof(r) - sizeof(long), 0) == -1) {
        perror("msgsnd");
        exit(1);
    }

    if (msgrcv(qid, &s, sizeof(s) - sizeof(long), r.pid, 0) == -1) {
        perror("msgrcv");
        exit(1);
    }

    printf("\n%s\n", s.text);
    return 0;
}
