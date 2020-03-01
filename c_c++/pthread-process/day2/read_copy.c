#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>

int main(int argc,char *argv[])
{
	int ret=0;
	int tep=0;
	char buf[128];
	if(argc!=3)
	{
		fprintf(stderr,"%s <file> <file>\n",argv[0]);
		return -1;
	}
	int fd1=open(argv[1],O_RDONLY);
	if(fd1==-1)
	{
		perror("open");
		return -1;
	}

	int fd2=open(argv[2],O_RDWR|O_CREAT|O_TRUNC,0664);
	if(fd2==-1)
	{
		perror("open");
		return -1;
	}

	memset(buf,0,sizeof(buf));
	while((ret=read(fd1,buf,sizeof(buf)))>0)
	{
		tep=write(fd2,buf,ret);
		if(tep==-1)
		{
			perror("write");
			break;
		}
	}
	close(fd1);
	close(fd2);
	return 0;
}
