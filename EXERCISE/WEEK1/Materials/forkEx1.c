#include <unistd.h>
#include<stdio.h>
#include<sys/wait.h>
int main(){
	int a=10,b=20;
	int pid=fork();
	if(pid<0){
		printf(" Child Not Created \n");
	}
	else if (pid>0){
		printf(" PARENT id %d and pid returned by fork() %d \n",getpid(),pid);
		//printf(" Addition of 10 and 20 is %d ",c);
		wait(0);
	}
	else{
		int c;
		c=a+b;
		printf(" CHILD pid: %d -- PARENT id %d \n ",getpid(),getppid());
		printf(" CHILD -pid returned by fork() %d \n",pid);
		printf(" Addition of 10 and 20 is %d \n",c);
	}
}
