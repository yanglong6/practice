
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<wait.h>

int main()
{
	int status;
	pid_t pid;
	pid=fork();
	if(pid==-1)
	{
		perror("fork");
		return -1;
	}
	else if(pid==0)
	{
		sleep(2);
		printf("childen prosess PID=%d PPID=%d\n",getpid(),getppid());
		exit(1);
	}
	status=0;
	pid=wait(&status);
	printf("hallo\n");
	printf("childen pid=%d,status=%d\n",pid,status);
	return 0;
}
