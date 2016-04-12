#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>

#define PORT 8080
int main()
{
	int sock=socket(AF_INET,SOCK_DGRAM,0);
	if(sock<0)
	{
		printf("sock error\n");
		return 1;
	}
	struct sockaddr_in server;
	struct sockaddr_in client;
	bzero(&server,sizeof(server));
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=htonl(INADDR_ANY);
	server.sin_port=htons(PORT);
	if(bind(sock,(struct sockaddr*)&server,sizeof(server))<0)
	{
		printf("bind error\n");
		close(sock);
		return 2;
	}
	printf("bind sucess\n");
	//udp是无连接，不可靠协议，因此不用listen和accept
	//接下来开始接收信息
	socklen_t len=sizeof(client);
	char buf[1024];
	char buf_ip[16];
	memset(buf_ip,'\0',sizeof(buf_ip));
	memset(buf,'\0',sizeof(buf));
	while(1)
	{
		ssize_t ret=recvfrom(sock,buf,sizeof(buf),0,(struct sockaddr*)&client,&len);
		if(ret<0)
		{
			printf("recvfrom error\n");
			close(sock);
			return 3;
		}
		//printf("%d\n",ret);
		buf[ret-1]='\0';
		printf("you got message %s\nIt's ip is %s,port is %d\n",buf,\
				inet_ntop(AF_INET,&client.sin_addr,buf_ip,sizeof(buf_ip)),ntohs(client.sin_port));
		sendto(sock,"welcome to my server\n",22,0,(struct sockaddr*)&client,len);
		write(1,buf,ret);
		printf("\n");
		if(!strcmp(buf,"quit"))
		{
			printf("client close,");
			printf("It's ip is %s,port is %d\n",\
				inet_ntop(AF_INET,&client.sin_addr,buf_ip,sizeof(buf_ip)),ntohs(client.sin_port));
		}
	}
	close(sock);
	return 0;
}
