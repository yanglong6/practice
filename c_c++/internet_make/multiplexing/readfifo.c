#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
	int fd1=open("f1",O_RDWR);
	int fd2=open("f2",O_RDWR);
	int fd3=open("f3",O_RDWR);

	char buf[64];
	int ret;

	while(1)
	{
		memset(buf,0,sizeof(buf));
		ret=read(fd1,buf,64);
		printf("fd1=%s\n",buf);

		memset(buf,0,sizeof(buf));
		ret=read(fd2,buf,64);
		printf("fd2=%s\n",buf);

		memset(buf,0,sizeof(buf));
		ret=read(fd3,buf,64);
		printf("fd3=%s\n",buf);
	}
	return 0;
}
