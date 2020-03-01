#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define N 10
typedef int date_t;

typedef struct queue
{
	date_t date[N];
	int front,rear;
}queue;

//创建空队
queue *creat_queue()
{
	queue *dui=(queue *)malloc(sizeof(queue));
	if(NULL==dui)
		return NULL;
	memset(dui->date,0,sizeof(dui->date));
	dui->front=dui->rear=0;
	return dui;
}

//判空
int empty(queue *dui)
{
	if(dui==NULL)
		return -1;
	return ((dui->front==dui->rear)?1:0);
}

//判满
int full(queue *dui)
{
	if(dui==NULL)
		return -1;
	if(dui->rear>dui->front)
		return ((dui->rear-dui->front==N-1)?1:0);
	if(dui->rear<dui->front)
		return ((dui->front-dui->rear==1)?1:0);
}

//入队
int in_queue(queue *dui,date_t date)
{
	if(dui==NULL)
		return -1;
	if(full(dui))
		return -1;
	dui->date[dui->rear]=date;
	dui->rear=(dui->rear+1)%N;
	return 0;
	
}

//出队
int out_queue(queue *dui)
{
	if(NULL==dui)
		return -1;
	if(empty(dui))
		return -1;
	int date=0;
		date=dui->date[dui->front];
		dui->front=(dui->front+1)%N;
	return date;
}
//打印
int frintf_squeue(queue *dui)
{
	if(NULL==dui)
		return -1;
	int tep=dui->front;
	while(tep!=dui->rear)
	{
		printf("%d ",dui->date[tep]);
		tep=(tep+1)%N;
	}
	printf("\n");
	return 0;
}

int main()
{
	queue *dui=creat_queue();
	if(NULL==dui)
		printf("malloc fail\n");
	int i=1;
	while(i<11)
	{
	in_queue(dui,i);
	i++;
	}
	frintf_squeue(dui);

	for(i=0;i<5;i++)
	out_queue(dui);
	frintf_squeue(dui);

	return 0;
}
