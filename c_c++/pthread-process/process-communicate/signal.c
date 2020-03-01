#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<sys/types.h>
#include<signal.h>
void fun(int sig)
{
	if(sig==SIGINT)
	{
		printf("sig=%d\n",sig);
	}
	else if(sig==SIGTSTP)
}

int main()
{
	signal(SIGINT,fun);
	signal(SIGQUIT,fun);
	while(1)
	{
		printf("aa\n");
		sleep(1);
	};
	return 0;
}
