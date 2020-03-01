#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef int date_t;
//构造节点
typedef struct link_queue
{
	date_t date;
	struct link_queue *next;
}link_queue;

//构造队列
typedef struct
{
	link_queue *front,*rear;
}dui;

//建立空队列
dui *creat_link()
{
	dui *lq=(dui *)malloc(sizeof(dui));
	if(NULL==lq)
		return NULL;
	lq->front=(link_queue *)malloc((sizeof(link_queue)));
	if(lq->front==NULL)
		return NULL;
	lq->front->date=-1;
	lq->front->next=NULL;
	lq->rear=lq->front;

	return lq;
}

//判空
int epmty(dui *lq)
{
	if(NULL==lq)
		return -1;
	return ((lq->front==lq->rear)?1:0);
}

//入队
int in_queue(dui *lq,date_t date)
{
	if(NULL==lq)
		return -1;
	link_queue *new=(link_queue *)malloc(sizeof(link_queue));
	if(NULL==new)
		return -1;
	new->date=date;
	new->next=NULL;

	lq->rear->next=new;
	lq->rear=new;
	return 0;
}

//出队
int out_queue(dui *lq)
{
	if(NULL==lq)
		return -1;
	if(epmty(lq))
		return -1;
	link_queue *p=lq->front->next;
	int date=p->date;
	lq->front->next=p->next;
	free(p);
	p=NULL;

	if(lq->front->next==NULL)
		lq->rear=lq->front;
	return 0;
}

//打印
int printf_queue(dui *lq)
{
	if(lq==NULL)
		return -1;
	link_queue *q=lq->front->next;
	while(q!=lq->rear->next)
	{
		printf("%d ",q->date);
		q=q->next;
	}
	printf("\n");
	return 0;
}
int main()
{
	dui *lq=creat_link();
	if(NULL==lq)
		printf("malloc fial\n");
	int i=1;
	while(i<10)
	{
		in_queue(lq,i);
		i++;
	}
	printf_queue(lq);
	for(i=0;i<5;i++)
		out_queue(lq);
	printf_queue(lq);
	return 0;
}

