
#include<stdio.h>
#include<string.h>
#include <sys/types.h>          
#include <sys/socket.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<unistd.h>

int main(int argc,char *argv[])
{
	int sendfd;
	char buf[64];

	if(argc!=3)
	{
		printf("%s <id> <port>\n",argv[0]);
		return -1;
	}
	//建立socket
	sendfd=socket(AF_INET,SOCK_STREAM,0);
	if(sendfd==-1)
	{
		perror("socket");
		return -1;
	}

	struct sockaddr_in sendaddr;

	sendaddr.sin_port=htons(atoi(argv[2]));
	sendaddr.sin_family=AF_INET;
	sendaddr.sin_addr.s_addr=inet_addr(argv[1]);

	int ret=connect(sendfd,(struct sockaddr *)&sendaddr,sizeof(sendaddr));
	if(ret==-1)
	{
		perror("connect");
		return -1;
	}

	while(1)
	{
		memset(buf,0,sizeof(buf));
		gets(buf);
		ret=send(sendfd,buf,strlen(buf),0);
		if(ret==-1)
		{
			perror("send");
			return -1;
		}
		if(0==strcmp(buf,"time"))
		{
			ret=recv(sendfd,buf,sizeof(buf),0);
		if(ret==-1)
		{
			perror("recv");
			return -1;
		}
		printf("%s\n",buf);
		}
	}
		close(sendfd);
	return 0;
}
