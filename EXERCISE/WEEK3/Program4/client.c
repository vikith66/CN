#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    mkfifo("e_bill", 0777); 

    long int id;
    int units;
    double bill_amt;

    printf("Enter Customer Number: ");
    scanf("%ld", &id);

    printf("Enter units consumed: ");
    scanf("%d", &units);

    int fd = open("e_bill", O_WRONLY);
    write(fd, &id, sizeof(id));
    write(fd, &units, sizeof(units));
    close(fd);

    fd = open("e_bill", O_RDONLY);
    read(fd, &bill_amt, sizeof(bill_amt));
    close(fd);

    printf("\n----- Electricity Bill -----\n");
    printf("Customer Number: %ld\n", id);
    printf("Units Consumed: %d\n", units);
    printf("Total Bill: %.2f\n", bill_amt);
    printf("----------------------------\n");

    return 0;
}

