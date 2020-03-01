#include<stdio.h>
#include<pthread.h>
#include<string.h>

void *fun(void *arg)
{
	while(1)
	{
		printf("fun =%s\n",(char *)arg);
		sleep(1);
	//	pthread_exit((void *)a);
	}
}
int main()
{
	int ret;
	int a=10;
	int *retval;
	pthread_t pth;
	pthread_t yy;
	ret=pthread_create(&pth,NULL,fun,"pth");
	if(ret!=0)
	{
		fprintf(stderr,"create pthread fail\n");
		return -1;
	}

	ret=pthread_create(&yy,NULL,fun,"yy");
	if(ret!=0)
	{
		fprintf(stderr,"create pthread fail\n");
		return -1;
	}
	sleep(3);
	pthread_cancel(pth);
	sleep(9);
	pthread_cancel(yy);

	pthread_join(pth,NULL);
	pthread_join(yy,NULL);
//	printf("retval=%d\n",retval);
//	printf("long\n");
	return 0;
}
