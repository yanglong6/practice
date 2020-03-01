#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/time.h>
#include <unistd.h>


int main()
{
	int fd1=open("f1",O_RDWR);
	int fd2=open("f2",O_RDWR);
	int fd3=open("f3",O_RDWR);

	char buf[64];
	int ret;

	while(1)
	{
	//创建一张表，把文件描述符加入表中
	fd_set rsfd;
	FD_ZERO(&rsfd);
	FD_SET(fd1,&rsfd);
	FD_SET(fd2,&rsfd);
	FD_SET(fd3,&rsfd);

	//监听表
	int maxfd=fd3+1;
	ret=select(maxfd,&rsfd,NULL,NULL,NULL);
	if(ret==-1)
	{
		perror("select");
		return -1;
	}

	int i;
	for(i=0;i<maxfd;i++)
	{
		if(FD_ISSET(i,&rsfd))
		{
			memset(buf,0,64);
			read(i,buf,64);
			printf("buf:%s\n",buf);
		}
	}
	}
	return 0;
}
