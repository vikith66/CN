#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>
int main()
{	int sfd,res;
	int buf1;
	char buf2[20];
	struct sockaddr_in server;
	sfd=socket(AF_INET,SOCK_STREAM,0);
	if(sfd==-1)
	{	printf("socket creation error");
		exit(0);
	}
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=inet_addr("127.0.0.1");
	server.sin_port=htons(3001);
	res=connect(sfd,(struct sockaddr*)&server,sizeof(server));
	if(res==-1)
	{	printf("connection error");
		exit(0);
	}
		printf(" ENTER 0 to exit \n");
		printf("CLIENT :enter message -");
		scanf("%d",&buf1);
		send(sfd,&buf1,20,0);
		if(buf1==0)
		{	send(sfd,&buf1,sizeof(int),0);
			close(sfd);
			exit(0);
		}
		memset(buf2,'\0',sizeof(buf2));
		recv(sfd,buf2,sizeof(buf2),0);
		printf("SERVER result : %s\n",buf2);
		
		
	close(sfd);
	return 0;
}