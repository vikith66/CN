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
        // -------- Parent --------
        close(p1[0]); 
        close(p2[1]); 

        int n;
        printf("Enter size of matrix (n x n): ");
        scanf("%d", &n);

        int matrix[50][50];
        printf("Enter matrix elements (%d x %d):\n", n, n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                scanf("%d", &matrix[i][j]);
            }
        }

        int multiplier;
        printf("Enter multiplier: ");
        scanf("%d", &multiplier);

        write(p1[1], &n, sizeof(n));
        write(p1[1], matrix, n * n * sizeof(int));
        write(p1[1], &multiplier, sizeof(multiplier));

        int result[50][50];
        read(p2[0], result, n * n * sizeof(int));

        printf("\nModified Matrix:\n");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                printf("%d ", result[i][j]);
            }
            printf("\n");
        }

        close(p1[1]);
        close(p2[0]);
    } else {
        // -------- Child --------
        close(p1[1]); 
        close(p2[0]); 

        int n, matrix[50][50], multiplier;
        read(p1[0], &n, sizeof(n));
        read(p1[0], matrix, n * n * sizeof(int));
        read(p1[0], &multiplier, sizeof(multiplier));

        int result[50][50];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                result[i][j] = matrix[i][j] * multiplier;
            }
        }

        write(p2[1], result, n * n * sizeof(int));

        close(p1[0]);
        close(p2[1]);
    }

    return 0;
}
