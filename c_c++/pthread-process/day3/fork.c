#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>

int main()
{
	pid_t pid;
	pid=fork();
	if(pid==-1)
	{
		perror("fork");
		return -1;
	}
	else if(pid==0)
	{
		printf("childen prosess PID=%d PPID=%d\n",getpid(),getppid());
	}
	else
		printf("father prosess PID=%d\n",getpid());

	printf("hallo\n");
	return 0;
}
