#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>

int main(int argc,char *argv[])
{
	char buf[32];
	if(argc!=2)
	{
		fprintf(stderr,"%s <file>\n",argv[0]);
		return -1;
	}
	int fd=open(argv[1],O_RDWR|O_CREAT,0664);
	if(fd==-1)
	{
		perror("open");
		return -1;
	}
	strcpy(buf,"hallo");
	write(fd,buf,strlen(buf));
	lseek(fd,1024,SEEK_SET);
	
	memset(buf,0,sizeof(buf));
	strcpy(buf,"34");
	write(fd,buf,strlen(buf));
	return 0;
}
