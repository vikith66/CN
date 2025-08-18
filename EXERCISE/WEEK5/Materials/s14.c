#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>
// To refrieve IP and Port details of client which 
// is connected
//When accept() is executed, client IP and port is received 
//in 2nd argument of accept() i.e. &client in this program
int main()
{	int sfd,sd,len,ak, len1;
	int buf1;
	char buf2[20];
	struct sockaddr_in server,client, cli_addr;
	sfd=socket(AF_INET,SOCK_STREAM,0);
	if(sfd==-1)
	{	printf("creation error");
		exit(0);
	}
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=inet_addr("127.0.0.1");
	server.sin_port=htons(3001);
// server.sin_port = 0;  // Let the OS choose the port number
	bind(sfd,(struct sockaddr*)&server,sizeof(server));
	len=sizeof(client);
	listen(sfd,5);
	ak=accept(sfd,(struct sockaddr*)&client,&len);
	//ak is the socket corresponding to Client
	if(ak==-1)
	{	printf("error in accepting");
		exit(0);
	}
	
	printf(" CLIENT : ");
	printf("Client process is using port number: %d\n", ntohs(client.sin_port));
	   
	close(ak);
	close(sfd);
	return 0;
}