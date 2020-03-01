
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>

int a=0;
pthread_mutex_t mutex;
sem_t sem;
void *fun(void *arg)
{
	int i=0;
	for(i=0;i<100000;i++)
	{	
	//	pthread_mutex_lock(&mutex);
		sem_wait(&sem);
		a++;
	//	pthread_mutex_unlock(&mutex);
//		sem_post(&sem);
	}

}

int main()
{
	pthread_t fth1;
	pthread_t fth2;
	pthread_t fth3;
	pthread_t fth4;
	int ret;
	pthread_mutex_init(&mutex,NULL);

	sem_init(&sem,0,1);

	ret=pthread_create(&fth1,NULL,fun,NULL);
	if(ret!=0)
	{
		fprintf(stderr,"create prt fail\n");
		return -1;
	}
	ret=pthread_create(&fth2,NULL,fun,NULL);
	if(ret!=0)
	{
		fprintf(stderr,"create prt fail\n");
		return -1;
	}
	ret=pthread_create(&fth3,NULL,fun,NULL);
	if(ret!=0)
	{
		fprintf(stderr,"create prt fail\n");
		return -1;
	}
	ret=pthread_create(&fth4,NULL,fun,NULL);
	if(ret!=0)
	{
		fprintf(stderr,"create prt fail\n");
		return -1;
	}
	pthread_join(fth1,NULL);
	pthread_join(fth2,NULL);
	pthread_join(fth3,NULL);
	pthread_join(fth4,NULL);
	printf("%d\n",a);
//	while(1);
	return 0;
}
