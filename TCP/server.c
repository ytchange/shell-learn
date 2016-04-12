#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#define PORT 8080

int main()
{
	//socket
	//bind
	//listen
	//accept
	int sock=socket(AF_INET,SOCK_STREAM,0);
	if(sock<0)
	{
		printf("creat sock error\n");
		return 1;
	}
	struct sockaddr_in server;
	struct sockaddr_in client;
	bzero(&server,sizeof(server));
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=htonl(INADDR_ANY);
	server.sin_port=htons(PORT);
    int ret=bind(sock,(struct sockaddr*)&server,sizeof(server));
	if(ret<0)
	{
		printf("bind error\n");
		return 2;
	}
	listen(sock,20);
	printf("bind and listen sucess\n");
	printf("accept waiting...\n");
	while(1)
	{
		char buf[1024];
		memset(buf,'\0',sizeof(buf));
		char buf_ip[16];
		socklen_t len=sizeof(server);
	
		int acc_client=accept(sock,(struct sockaddr*)&client,&len);
		printf("receive from %s at port %d\n",inet_ntop(AF_INET,&client.sin_addr,buf_ip,sizeof(buf_ip)),ntohs(client.sin_port));
		while(1)
		{
			int n=read(acc_client,buf,sizeof(buf));
			write(STDOUT_FILENO,buf,n);
			int i;
			for(i=0;i<n;i++)
			{
				buf[i]=toupper(buf[i]);
			}
			write(acc_client,buf,n);
		}
	}
	close(sock);
	return 0;
}
