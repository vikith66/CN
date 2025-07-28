//Vikith B Kotian
//240970107

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int n, key;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("Enter element to search: ");
    scanf("%d", &key);

    pid_t pid = fork(); 

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }
    else if (pid == 0) {
        printf("\nChild Process: Searching for %d...\n", key);
        int found = 0;
        for (int i = 0; i < n; i++) {
            if (arr[i] == key) {
                printf("Element %d found at index %d\n", key, i);
                found = 1;
                break;
            }
        }
        if (!found) {
            printf("Element %d not found in the array.\n", key);
        }
    }
    else {
        wait(NULL); 
        printf("Parent Process: Child process completed.\n");
    }

    return 0;
}
