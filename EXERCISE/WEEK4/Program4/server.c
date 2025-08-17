#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

#define KEY 1234
int tickets[5] = {20,20,20,20,20}; // available seats per category

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
    int qid = msgget(KEY, IPC_CREAT | 0666);
    if (qid == -1) {
        perror("msgget");
        exit(1);
    }

    struct request r; 
    struct response s;
    printf("Server started...\n");

    while (1) {
        if (msgrcv(qid, &r, sizeof(r) - sizeof(long), 1, 0) == -1) {
            perror("msgrcv");
            exit(1);
        }

        s.mtype = r.pid;

        if (r.num_tickets == -1) {  // Exit condition
            sprintf(s.text, "Server shutting down...");
            msgsnd(qid, &s, sizeof(s) - sizeof(long), 0);
            break;
        }

        if (r.category < 1 || r.category > 5) {
            sprintf(s.text, "Invalid category! Choose 1-5.");
        }
        else if (tickets[r.category - 1] >= r.num_tickets) {
            tickets[r.category - 1] -= r.num_tickets;
            sprintf(s.text, "Booking confirmed for %s: %d ticket(s) in Category %d. Remaining: %d",
                    r.name, r.num_tickets, r.category, tickets[r.category - 1]);
        }
        else {
            sprintf(s.text, "Not enough tickets! Only %d left in Category %d.",
                    tickets[r.category - 1], r.category);
        }

        if (msgsnd(qid, &s, sizeof(s) - sizeof(long), 0) == -1) {
            perror("msgsnd");
            exit(1);
        }
    }

    msgctl(qid, IPC_RMID, NULL);  // Clean up queue
    printf("Server stopped.\n");
    return 0;
}
