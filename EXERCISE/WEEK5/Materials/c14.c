#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>
// Client Socket is created and filled with IP and Port  
// which is given by Operating System
//When connect() request is sent, these information reach
//Server when server execute accept() command
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

		
	close(sfd);
	return 0;
}