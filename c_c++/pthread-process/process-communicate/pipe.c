#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

int main()
{
	int ret;
	pid_t pid;
	int fd[2];
	char buf[64];
	pid=fork();
	ret=pipe(fd);
	if(ret==-1)
	{
		perror("pipe");
		return -1;
	}

	if(pid==-1)
	{
		perror("fork");
		return -1;
	}
	else if(pid==0)
	{
		close(fd[0]);
		while(1)
		{
			fgets(buf,sizeof(buf),stdin);
			ret=write(fd[1],buf,sizeof(buf));
			if(ret==-1)
			{
				perror("write");
				return -1;
			}
		}
		exit(0);

	}
	else
	{
		while(1)
		{
			memset(buf,0,sizeof(buf));
			ret=read(fd[0],buf,sizeof(buf));
			if(ret==-1)
			{
				perror("read");
				return -1;
			}
			printf("buf=%s\n",buf);
		}
	}
	return 0;
}
