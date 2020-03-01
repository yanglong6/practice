
#include<stdio.h>
#include<string.h>
#include <sys/types.h>          
#include <sys/socket.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<time.h>

int main(int argc,char *argv[])
{
	int servefd,connfd;
	char buf[64];
	time_t t;
	char *q=NULL;

	if(argc!=3)
	{
		printf("%s <id> <port>\n",argv[0]);
		return -1;
	}

	//建立socket
	servefd=socket(AF_INET,SOCK_STREAM,0);
	if(servefd==-1)
	{
		perror("socket");
		return -1;
	}

	struct sockaddr_in servaddr;

	servaddr.sin_port=htons(atoi(argv[2]));
	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=inet_addr(argv[1]);

	int ret=bind(servefd,(struct sockaddr *)&servaddr,sizeof(servaddr));
	if(ret==-1)
	{
		perror("bind");
		return -1;
	}

	ret=listen(servefd,5);
	if(ret==-1)
	{
		perror("listen");
		return -1;
	}
	while(1)
	{
	connfd=accept(servefd,NULL,NULL);
	if(connfd==-1)
	{
		perror("accept");
		return -1;
	}

	while(1)
	{
		memset(buf,0,sizeof(buf));
		ret=recv(connfd,buf,sizeof(buf),0);
		if(ret==-1)
		{
			perror("recv");
			return -1;
		}
		else if(ret==0)
			break;
		printf("len=%d,%s\n",ret,buf);
		time(&t);
		q=ctime(&t);
		if(strcmp(buf,"time")==0)
		{
			ret=send(connfd,q,strlen(q),0);
			if(ret==-1)
			{
				perror("senf");
				return -1;
			}
		}
	}
		close(connfd);
	}
		close(servefd);
	return 0;
}
