#include<stdio.h>
#include<string.h>
#include <sys/types.h>          
#include <sys/socket.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<errno.h>
#include<signal.h>

void sig_fun(int sig)
{
	printf("timeout\n");
	alarm(2);
}

int main()
{
	signal(SIGALRM,sig_fun);
	int servefd,connfd;
	char buf[64];

	//建立socket
	servefd=socket(AF_INET,SOCK_STREAM,0);
	if(servefd==-1)
	{
		perror("socket");
		return -1;
	}

	struct sockaddr_in servaddr;

	servaddr.sin_port=htons(6666);
	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=inet_addr("192.168.2.176");

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
			alarm(2);
			memset(buf,0,sizeof(buf));
			ret=recv(connfd,buf,sizeof(buf),0);
			if(ret==-1)
			{
				if(errno==EAGAIN || errno ==EWOULDBLOCK)
				{
					printf("timeout\n");
					continue;
				}
				else
				{
				perror("recv");
				return -1;
				}
			}
			else if(ret==0)
			{
				printf("clian quit\n");
				break;
			}
			send(connfd,buf,ret,0);
			printf("len=%d,%s\n",ret,buf);
		}
		close(connfd);
	}
	close(servefd);
	return 0;
}
