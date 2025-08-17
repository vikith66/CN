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

    mkfifo("fifo_client_to_server", 0666);
    mkfifo("fifo_server_to_client", 0666);

    printf("Enter Deposit Amount: ");
    scanf("%f", &dep.amount);

    printf("Enter Tenure in months: ");
    scanf("%d", &dep.tenure);

    fd1 = open("fifo_client_to_server", O_WRONLY);
    write(fd1, &dep, sizeof(dep));
    close(fd1);

    fd2 = open("fifo_server_to_client", O_RDONLY);
    read(fd2, &res, sizeof(res));
    close(fd2);

    printf("\n--- Bank Result ---\n");
    printf("Deposit Amount : %.2f\n", dep.amount);
    printf("Tenure (months): %d\n", dep.tenure);
    printf("Interest Earned: %.2f\n", res.interest);
    printf("Maturity Amount: %.2f\n", res.maturity);

    return 0;
}
