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
	char buf1[20],buf2[20];
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
		memset(buf1, '\0',sizeof(buf1));
		printf("CLIENT :enter message -");
		scanf("%s",buf1);
		send(sfd,buf1,20,0);
		if(strcmp(buf1,"quit")==0)
		{	send(sfd,buf1,20,0);
			close(sfd);
			exit(0);
		}
		
		recv(sfd,buf2,20,0);
		printf("SERVER : %s\n",buf2);
	
	close(sfd);
	return 0;
}