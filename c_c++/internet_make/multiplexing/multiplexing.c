#include<stdio.h>
#include<string.h>
#include <sys/types.h>          
#include <sys/socket.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<unistd.h>
#include <sys/time.h>

int tcp_serve_init()
{
	int servefd;
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
	return servefd;
}

int main()
{
	int servefd,connfd;
	char buf[64];
	int ret;
	servefd=tcp_serve_init();

//建立表，加入文件描述符
	fd_set biao,tepbiao;
	FD_ZERO(&biao);
	FD_SET(servefd,&biao);

	int maxfd=servefd;
	while(1)
	{
		tepbiao=biao;
		ret=select(maxfd+1,&tepbiao,NULL,NULL,NULL);
		if(ret==-1)
		{
			perror("select");
				return -1;
		}
		int i;
		for(i=0;i<=maxfd;i++)
		{
			if(FD_ISSET(i,&tepbiao))
			{
				if(i==servefd)
				{
					connfd=accept(i,NULL,NULL);
						if(connfd==-1)
						{
							perror("accept");
							return -1;
						}
					printf("clian %d connect\n",connfd);
					FD_SET(connfd,&biao);
					if(maxfd<connfd)
						maxfd=connfd;
					else
						maxfd;
				}
				else
				{
					memset(buf,0,sizeof(buf));
					ret=recv(i,buf,sizeof(buf),0);
					if(ret==0)
					{
						printf("clian %d quit\n",i);
						FD_CLR(i,&biao);
						close(i);
					}
					printf("recv:%s\n",buf);
				}
			}
		}
	}
	return 0;
}
