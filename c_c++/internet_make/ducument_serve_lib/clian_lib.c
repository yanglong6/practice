#include<stdio.h>
#include<string.h>
#include <sys/types.h>          
#include <sys/socket.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<time.h>
#include <dirent.h>

//下载
int down(char *buf,int clianfd)
{
	int ret;
	send(clianfd,buf,128,0);

	char date[15000];
	FILE *fd=fopen(buf+4,"w");
	while(1)
	{
		memset(date,0,sizeof(date));
	ret=recv(clianfd,date,sizeof(date),0);
	printf("ret=%d\n",ret);
		if(strcmp(date,"over")==0)
			break;
	fwrite(date,1,ret,fd);
	fflush(fd);
	}
	printf("success\n");
	fclose(fd);
	return 0;
}

//上传
int put(char *buf,int clianfd)
{
	FILE *fq;
	int ret;
	char flag[]={"over"};
	send(clianfd,buf,128,0);
	fq=fopen(buf+4,"r");
	if(fq==NULL)
	{
		perror("fopen");
		return -1;
	}
	char date[1024];
	while(1)
	{
		ret=fread(date,1,sizeof(date),fq);
		if(ret<0)
		{
			perror("fread");
			return -1;
		}
		else if(ret==0)
		{
			sleep(1);
			send(clianfd,flag,sizeof(flag),0);
			break;
		}
		ret=send(clianfd,date,ret,0);
		if(ret==-1)
		{
			perror("send");
			return -1;
		}
	}
	printf("put success\n");
	fclose(fq);
	return 0;
}
//list
int list(char *buf,int clianfd)
{
	send(clianfd,buf,128,0);
	char date[256];
	int ret;
	while((recv(clianfd,date,256,0))!=0)
	{
		if(strcmp(date,"over")==0)
			break;
		printf("%s\n",date);
	}
	return 0;
}
int main()
{
	int clianfd;
	int ret;
	char buf[128];
	FILE *fq;
	//	char *q=NULL;

	//建立socket
	clianfd=socket(AF_INET,SOCK_STREAM,0);
	if(clianfd==-1)
	{
		perror("socket");
		return -1;
	}

	struct sockaddr_in cliaddr;

	cliaddr.sin_port=htons(6666);
	cliaddr.sin_family=AF_INET;
	cliaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
#if 0
	int ret=bind(clianfd,(struct sockaddr *)&cliaddr,sizeof(cliaddr));
	if(ret==-1)
	{
		perror("bind");
		return -1;
	}
#endif
	//建立链接
	ret=connect(clianfd,(struct sockaddr *)&cliaddr,sizeof(cliaddr));
	if(ret==-1)
	{
		perror("connect");
		return -1;
	}

	while(1)
	{
		printf("please put:\n");
		gets(buf);
		if(0==strcmp(buf,"help"))
		{
			printf("list:显示当前文件夹文件\n");
			printf("get <file>:下载文件\n");
			printf("put <file>:上传文件\n");
			printf("help:帮助\n");
		}
		else if(strcmp(buf,"list")==0)
		{
			list(buf,clianfd);
		//	system("ls");

		}
		else if(strncmp(buf,"get ",4)==0)
		{
			down(buf,clianfd);
		}
		else if(strncmp(buf,"put ",4)==0)
		{
			put(buf,clianfd);
		}
	}
	close(clianfd);
	return 0;
}
