#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

int main(int argc,char *argv[])
{
	if(argc!=2)
	{
		fprintf(stderr,"%s <file>\n",argv[0]);
		return -1;
	}
	int fd=open(argv[1],O_WRONLY|O_CREAT|O_TRUNC,0644);
	if(fd==-1)
	{
		perror("open");
		return -1;
	}
	return 0;
}
