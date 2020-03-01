#include<stdio.h>
#include<string.h>
#include <sys/types.h>          
#include <sys/socket.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<time.h>
#include<signal.h>
#include<sys/wait.h>
void signal_fun(int sig)
{
	while(waitpid(-1,NULL,WNOHANG)>0);
}

int main(int argc,char *argv[])
{
	int servefd,connfd;
	char buf[64];
	time_t t;
	char *q=NULL;
	pid_t pid;

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
		signal(SIGCHLD,signal_fun);
		printf("wait...\n");
		connfd=accept(servefd,NULL,NULL);
		printf("connect a clian %d\n",connfd);
		if(connfd==-1)
		{
			perror("accept");
			exit(-1);
		}
		pid=fork();
		if(pid==-1)
		{
			perror("fork");
			return -1;
		}
		else if(pid==0)
		{
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
				{
					printf("clian quit\n");
					exit(0);
				}
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
		} // fork
	}
	close(connfd);
	close(servefd);
	return 0;
}
