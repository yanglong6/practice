#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<wait.h>

int main()
{
	int status;
	pid_t pid1,pid2;
	pid1=fork();
	if(pid1==-1)
	{
		perror("fork1");
		return -1;
	}
	else if(pid1==0)
	{
		sleep(4);
		printf("childen1 prosess PID=%d PPID=%d\n",getpid(),getppid());
		exit(1);
	}

	pid2=fork();
	if(pid2==-1)
	{
		perror("fork2");
		return -1;
	}
	else if(pid2==0)
	{
		sleep(7);
		printf("childen2 pid=%d,ppid=%d\n",getpid(),getppid());
		exit(2);
	}
	while(1)
	{
	status=0;
	pid1=waitpid(-1,&status,WNOHANG);
	printf("pid1=%d,status=%d\n",pid1,status);
	sleep(1);
	if(pid1>0)
		exit(0);
	}
	return 0;
}
