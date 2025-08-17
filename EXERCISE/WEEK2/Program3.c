// 240970107: Vikith B Kotian
//Reads the array, extracts even numbers only

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int p1[2], p2[2];
    pid_t pid;

    if (pipe(p1) == -1 || pipe(p2) == -1) {
        perror("pipe failed");
        return 1;
    }

    pid = fork();
    if (pid < 0) {
        perror("fork failed");
        return 1;
    }

    if (pid > 0) {
        close(p1[0]);
        close(p2[1]); 

        int n, arr[100];
        printf("Enter number of elements: ");
        scanf("%d", &n);

        printf("Enter %d integers:\n", n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &arr[i]);
        }
      
        write(p1[1], &n, sizeof(n));
        write(p1[1], arr, n * sizeof(int));
      
        int evenCount;
        int evenArr[100];
        read(p2[0], &evenCount, sizeof(evenCount));
        read(p2[0], evenArr, evenCount * sizeof(int));

        printf("Even numbers received from child: ");
        for (int i = 0; i < evenCount; i++) {
            printf("%d ", evenArr[i]);
        }
        printf("\n");

        close(p1[1]);
        close(p2[0]);
    } else {
        close(p1[1]); 
        close(p2[0]);

        int n, arr[100];
        read(p1[0], &n, sizeof(n));
        read(p1[0], arr, n * sizeof(int));

        int evenArr[100], evenCount = 0;
        for (int i = 0; i < n; i++) {
            if (arr[i] % 2 == 0) {
                evenArr[evenCount++] = arr[i];
            }
        }

        write(p2[1], &evenCount, sizeof(evenCount));
        write(p2[1], evenArr, evenCount * sizeof(int));

        close(p1[0]);
        close(p2[1]);
    }

    return 0;
}
