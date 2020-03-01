#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>

typedef struct arr
{
	int *date;
	int size;
}ar;
sem_t sem;

void *prt(void *pt)
{
	int i;
	int *p=((ar *)pt)->date;
	int size=((ar *)pt)->size;
	while(1)
	{
		sleep(1);
		sem_wait(&sem);
	for(i=0;i<size;i++)
		printf("%d ",p[i]);
	printf("\n");
	}
}

void *dz(void *yy)
{
	int i,t;
	int *p=((ar *)yy)->date;
	int size=((ar *)yy)->size;

	while(1)
	{
		sleep(1);
		for(i=0;i<size/2;i++)
		{
			t=p[i];
			p[i]=p[size-1-i];
			p[size-1-i]=t;
		}
		sem_post(&sem);
	}
}

int main()
{
	pthread_t fth1;
	pthread_t fth2;
	int a[10]={0,1,2,3,4,5,6,7,8,9};
	int ret;
	ar yy={a,10};

	ret=sem_init(&sem,0,0);
	if(ret==-1)
	{
		perror("sem_init");
		return -1;
	}
	ret=pthread_create(&fth1,NULL,prt,(void *)&yy);
	if(ret!=0)
	{
		fprintf(stderr,"create prt fail\n");
		return -1;
	}
	ret=pthread_create(&fth2,NULL,dz,(void *)&yy);
	if(ret!=0)
	{
		fprintf(stderr,"create prt fail\n");
		return -1;
	}
	while(1);
	return 0;
}
