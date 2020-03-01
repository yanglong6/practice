#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<dirent.h>
#include<pwd.h>

int main(int argc,char *argv[])
{
	int ret=0;
	int i=0;
	struct passwd *pw;
	struct stat buf;
	if(argc!=2)
	{
		fprintf(stderr,"%s <file>\n",argv[0]);
		return -1;
	}
	ret=stat(argv[1],&buf);
	if(ret==-1)
	{
		perror("stat");
		return -1;
	}
//	printf("%o ",(int)buf.st_mode);
	for(i=8;i>=0;i--)
	{
		if((buf.st_mode)&(1<<i))
		{
			switch(i%3)
			{
				case 2:
					printf("r");
					break;
				case 1:
					printf("w");
					break;
				case 0:
					printf("x");
					break;
				default:
					break;
			}
		}
		else 
			printf("-");
	}
	pw=getpwuid(buf.st_uid);
	printf("%s ",pw->pw_name);
	printf("%s ",pw->pw_passwd);
	printf("%d ",buf.st_size);
	printf("\n");
	return 0;
}
