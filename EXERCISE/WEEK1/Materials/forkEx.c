#include <unistd.h>
#include<stdio.h>
#include<sys/wait.h>
int main(){
	int a=10;
	int pid=fork();
	if(pid<0){
		printf(" Child Not Created \n");
	}
	else if (pid>0){
		printf(" PARENT id %d and pid returned by fork() %d \n",getpid(),pid);
		wait(0);
	}
	else{
		printf(" CHILD pid: %d -- PARENT id %d ",getpid(),getppid());
		printf(" CHILD -pid returned by fork() %d \n",pid);
	}
}
