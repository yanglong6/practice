#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<wait.h>
#include<fcntl.h>

int main()
{
	int status;
	int ret;
	int i;
	pid_t pid;
	pid=fork();
	if(pid==-1)
	{
		perror("fork");
		return -1;
	}
	else if(pid>0)
		exit(0);
     
	if((pid_t)-1==setsid())
	{
		perror("setpid");
		return -1;
	}

	if(-1==chdir("/tmp"))
	{
		perror("chdir");
		return -1;
	}
	umask(0);
	for(i=0;i<getdtablesize();i++)
	{
		close(i);
	}
	printf("%d\n",pid);
	
	char *envp[]={"PATH=/home/farsight/huaqin/线程与进程/day3/time",NULL};
	ret=execle("home/farsight/huaqin/线程与进程/day3/time","./time","test.txt",NULL,envp);
		if (ret == -1) 
		{
			perror("execle");
			return -1;
		}
	return 0;
}
