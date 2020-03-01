#include<stdio.h>
#include<string.h>
#include <sys/types.h>          
#include <sys/socket.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<pthread.h>
#include<time.h>
#include <fcntl.h>

void *fun1(void *arg)
{
	int ret;
	char buf[64];
	int connfd=(int )arg;
	while(1)
	{
		memset(buf,0,sizeof(buf));
		ret=recv(connfd,buf,sizeof(buf),0);
		if(ret==-1)
		{
			perror("recv");
			return ;
		}
		else if(ret==0)
		{
			printf("clian quit\n");
			close(connfd);
			pthread_detach(pthread_self());
			pthread_exit((void *)connfd);
		}
		printf("len=%d,%s\n",ret,buf);
			ret=send((connfd+1),buf,ret,0);
			if(ret==-1)
			{
				perror("send");
				return ;
			}
	}

}
void *fun2(void *arg)
{
	int ret;
	char buf[64];
	int connfd=(int )arg;
	while(1)
	{
		memset(buf,0,sizeof(buf));
		ret=recv(connfd,buf,sizeof(buf),0);
		if(ret==-1)
		{
			perror("recv");
			return ;
		}
		else if(ret==0)
		{
			printf("clian quit\n");
			close(connfd);
			pthread_detach(pthread_self());
			pthread_exit((void *)connfd);
		}
		printf("len=%d,%s\n",ret,buf);
			ret=send((connfd-1),buf,ret,0);
			if(ret==-1)
			{
				perror("send");
				return ;
			}
	}
}

int main(int argc,char *argv[])
{
	int servefd,connfd;
	//char buf[64];
	pid_t pid;

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
	int i=0;
	while(i<5)
	{
		connfd=accept(servefd,NULL,NULL);
		printf("connect a clian %d\n",connfd);
		if(connfd==-1)
		{
			perror("accept");
			exit(-1);
		}
		pthread_t pthread1,pthread2;
		if(i==0)
		ret=pthread_create(&pthread1,NULL,fun1,(void *)connfd);
		else if(i==1)
		ret=pthread_create(&pthread2,NULL,fun2,(void *)connfd);
		i++;

	}
	close(connfd);
	close(servefd);
	return 0;
}
