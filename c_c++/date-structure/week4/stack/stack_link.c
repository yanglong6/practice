#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef int date_t;

typedef struct stack_link
{
	date_t date;
	struct stack_link *next;
}lstack;

//创建空栈
lstack *creat_stack()
{
	lstack *top=(lstack *)malloc(sizeof(lstack));
	if(top==NULL)
		return NULL;
	top->next=NULL;
	top->date=-1;
	return top;
}

//判空
int empty(lstack *top)
{
	if(NULL==top)
		return -1;
	return ((top->next==NULL)?1:0);
}

//入栈
int in_stack(lstack *top,date_t date)
{
	if(NULL==top)
		return -1;
	lstack *new=(lstack *)malloc(sizeof(lstack));
	new->date=date;
	new->next=NULL;

	new->next=top->next;
	top->next=new;
	return 0;
}

//出栈
int out_stack(lstack *top)
{
	if(top==NULL)
		return 0;
	lstack *q=top->next;
	date_t date=q->date;
	top->next=q->next;
	free(q);
	q=NULL;
	return 0;
}
//打印
int printf_stack(lstack *top)
{
	if(NULL==top)
		return -1;
	lstack *q=top;
	while(q->next!=NULL)
	{
		q=q->next;
		printf("%d ",q->date);
	}
	printf("\n");
	return 0;
}
int main()
{
	lstack *top=creat_stack();
	if(top==NULL)
		return -1;
	int i=1;
	while(i<=10)
	{
		in_stack(top,i);
		i++;
	}
	printf_stack(top);
	for(i=0;i<5;i++)
		out_stack(top);
	printf_stack(top);
	return 0;
}
