// 240970107: Vikith B Kotian
// Accept details of a student

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

struct Student {
    int regNo;
    int mark1, mark2, mark3;
};

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

        struct Student s;
        printf("Enter Student RegNo: ");
        scanf("%d", &s.regNo);
        printf("Enter 3 marks: ");
        scanf("%d %d %d", &s.mark1, &s.mark2, &s.mark3);

        write(p1[1], &s, sizeof(s));

        char grade[3];
        read(p2[0], grade, sizeof(grade));

        printf("\nStudent RegNo: %d\n", s.regNo);
        printf("Grade received from Child: %s\n", grade);

        close(p1[1]);
        close(p2[0]);
    } else {
        
        close(p1[1]); 
        close(p2[0]); 

        struct Student s;
        read(p1[0], &s, sizeof(s));

        float avg = (s.mark1 + s.mark2 + s.mark3) / 3.0;
        char *grade;

        if (avg >= 90) grade = "A+";
        else if (avg >= 80) grade = "A";
        else if (avg >= 70) grade = "B";
        else if (avg >= 60) grade = "C";
        else if (avg >= 50) grade = "D";
        else if (avg >= 40) grade = "E";
        else grade = "F";

        write(p2[1], grade, strlen(grade) + 1);

        close(p1[0]);
        close(p2[1]);
    }

    return 0;
}
