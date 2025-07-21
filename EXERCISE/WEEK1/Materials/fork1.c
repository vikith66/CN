#include <stdio.h>
main(int argc, char *argv[])
 {
    int pid;
    int i;
    /* print out the arguments */
    printf("There are %d arguments:\n",argc);
    
   if ((pid = fork()) < 0) 
	{
         printf("Fork error\n");
         //exit(1);
    	}
    else if (pid == 0) 
	{
         /* child process */
         printf("\nIn Child Process now");
	 for (i = 1; i < argc; i++)
          printf("%s\t",argv[i]);}
	/*for (i = 1; i < argc; i++)
	{
		if(argv[i]=="+" || argv[i]=="-" || argv[i]=="/" ||argv[i]=="*" )
		{
			opp=argv[i];
		}
		/*if(opp!=NULL)
		{
			sum=argv[
       }*/
    else 
	{
         /* parent */
	printf("\nIn Parent Now\n");
	wait();
	printf("\nParent ends\n");
         
    }
}

