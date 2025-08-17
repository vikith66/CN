#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

struct Deposit {
    float amount;
    int tenure;
};

struct Result {
    float maturity;
    float interest;
};

int main() {
    int fd1, fd2;
    struct Deposit dep;
    struct Result res;
    float rate;

    mkfifo("fifo_client_to_server", 0666);
    mkfifo("fifo_server_to_client", 0666);

    printf("Server running... Waiting for client input.\n");

    while (1) {
        fd1 = open("fifo_client_to_server", O_RDONLY);
        read(fd1, &dep, sizeof(dep));
        close(fd1);

        printf("Server received -> Amount: %.2f, Tenure: %d months\n", dep.amount, dep.tenure);
        if (dep.tenure <= 12)
            rate = 5.0;
        else if (dep.tenure <= 24)
            rate = 6.0;
        else if (dep.tenure <= 36)
            rate = 7.0;
        else
            rate = 8.0;

        res.interest = dep.amount * rate * dep.tenure / (100 * 12);
        res.maturity = dep.amount + res.interest;

        fd2 = open("fifo_server_to_client", O_WRONLY);
        write(fd2, &res, sizeof(res));
        close(fd2);

        printf("Server sent -> Interest: %.2f, Maturity: %.2f\n", res.interest, res.maturity);
    }

    return 0;
}
