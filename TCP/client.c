#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <stdlib.h>
#define PORT 8080
#define IPADDRESS "192.168.58.128"
int main(int argc,char *argv[])
{
	int sock=socket(AF_INET,SOCK_STREAM,0);
	if(sock<0)
	{
		printf("sock error\n");
		return 1;
		close(sock);
	}
	char buf[1024];
	memset(buf,'\0',sizeof(buf));
	struct sockaddr_in server;
	bzero(&server,sizeof(server));
	server.sin_family=AF_INET;
	server.sin_port=htons(PORT);
	inet_pton(AF_INET,IPADDRESS,&server.sin_addr);
	
	connect(sock,(struct sockaddr*)&server,sizeof(server));
	while(1)
	{
		char buf[1024];
		memset(buf,'\0',sizeof(buf));
		ssize_t size=read(0,buf,sizeof(buf));
	
		write(sock,buf,size);
		int n=read(sock,buf,sizeof(buf));
		write(STDOUT_FILENO,buf,n);
	}
	close(sock);
	return 0;
}
