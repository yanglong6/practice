#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<dirent.h>

int main(int argc,char *argv[])
{
	struct dirent *dir;
	if(argc!=2)
	{
		fprintf(stderr,"%s <file>\n",argv[0]);
		return -1;
	}
	DIR *fd=opendir(argv[1]);
	if(fd==NULL)
	{
		perror("open");
		return -1;
	}
	while((dir=readdir(fd))!=NULL)
	{
		printf("%s ",dir->d_name);
	}
	printf("\n");
	return 0;
}
