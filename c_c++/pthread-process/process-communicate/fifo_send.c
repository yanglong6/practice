#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<sys/types.h>

int main()
{
	int ret;
	int fd;
	char buf[64];
	ret=mkfifo("fifo",0777);
	if(ret==-1)
	{
		perror("mkfifo");
		return -1;
	}
	fd=open("fifo",O_RDWR);
	if(fd==-1)
	{
		perror("open");
		return -1;
	}
	while(1)
	{
		fgets(buf,sizeof(buf),stdin);
		ret=write(fd,buf,strlen(buf));
		printf("aa");
		if(ret==-1)
		{
			perror("write");
			return -1;
		}
	}
	close(fd);
	return 0;
}
