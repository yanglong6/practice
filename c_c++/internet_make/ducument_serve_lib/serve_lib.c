#include<stdio.h>
#include<string.h>
#include <sys/types.h>          
#include <sys/socket.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<time.h>
#include<dirent.h>

int main()
{
	int servefd,connfd;
	char buf[128];
	char date[1024];
	FILE *fq;
	FILE *fd;
	char flag[]={"over"};

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
	servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");

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
			printf("%s\n",buf);
			if(strncmp(buf,"get ",4)==0)
			{
				printf("%s\n",buf+4);
				fq=fopen(buf+4,"r");
				if(fq==NULL)
				{
					perror("fopen");
					return -1;
				}
				while(1)
				{
			
					ret=fread(date,1,sizeof(date),fq);
				//	printf("ret=%d\n",ret);
					if(ret==-1)
					{
						perror("fread");
						return -1;
					}
					else if(ret==0)
					{
						sleep(1);
						send(connfd,flag,sizeof(flag),0);
						break;
					}
					ret=send(connfd,date,ret,0);
					if(ret==-1)
					{
						perror("send");
						return -1;
					}
				}
				printf("get success\n");
			}
			else if(strncmp(buf,"put ",4)==0)
			{
				fd=fopen(buf+4,"w+");
				if(fd==NULL)
				{
					perror("fopen");
					return -1;
				}
				while(1)
				{
					memset(date,0,sizeof(date));
				ret=recv(connfd,date,sizeof(date),0);
				if(strcmp(date,"over")==0)
					break;
			//	printf("ret=%d\n",ret);
				fwrite(date,1,ret,fd);
				fflush(NULL);
				}
				printf("put success\n");
			}
			else if(strcmp(buf,"list")==0)
			{
				struct dirent *dirp;
				DIR *dir;
				dir=opendir(".");
				while((dirp=readdir(dir))!=NULL)
				{
					if(dirp->d_name[0]=='.')
						continue;
					send(connfd,dirp->d_name,sizeof(dirp->d_name),0);
				}
					send(connfd,flag,sizeof(buf),0);

			}
		}
	}
	fclose(fq);
	fclose(fd);
	close(connfd);
	close(servefd);
	return 0;
}
