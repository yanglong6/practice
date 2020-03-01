#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <poll.h>


int main()
{
	int fd1=open("f1",O_RDWR);
	int fd2=open("f2",O_RDWR);
	int fd3=open("f3",O_RDWR);

	char buf[64];
	int ret;
	int nfd=3;

	//加入表中
	struct pollfd events[64];

	memset(events,0,sizeof(events));

	events[0].fd=fd1;
	events[0].events=POLLIN;
	events[1].fd=fd2;
	events[1].events=POLLIN;
	events[2].fd=fd3;
	events[2].events=POLLIN;

	while(1)
	{
		memset(buf,0,sizeof(buf));
		ret=poll(events,3,-1);
		if(ret==-1)
		{
			perror("poll");
			return -1;
		}
		//有管道可以读
		int i;
		for(i=0;i<3;i++)
		{
			if(events[i].revents&POLLIN)
			{
				read(events[i].fd,buf,sizeof(buf));
				printf("buf:%s\n",buf);
			}
		}
	}
	return 0;
}
