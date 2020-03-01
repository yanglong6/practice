#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<sys/types.h>

int main()
{
	int sd;
	sd=alarm(10);
	if(sd==-1)
	{
		perror("alarm");
		return -1;
	}
	printf("sd=%d\n",sd);

	sleep(3);
	sd=alarm(3);
	printf("sd=%d\n",sd);

	while(1)
	{
		printf("aaa\n");
		sleep(1);
		pause();
		alarm(3);
	}
	return 0;
}
