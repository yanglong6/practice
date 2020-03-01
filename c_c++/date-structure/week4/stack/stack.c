#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define N  30
typedef int date_t;

typedef struct stack
{
	date_t date[N];
	int top;
}stack;

//创建栈
stack *creat_stack()
{
	stack *s=(stack *)malloc(sizeof(stack));
	if(s==NULL)
		return NULL;
	memset(s->date,0,sizeof(s->date));
	s->top=-1;
	return s;
}

//判空
int empty(stack *s)
{
	if(s==NULL)
		return -1;
	return ((s->top==-1)?1:0);
}

//判满
int full(stack *s)
{
	if(s==NULL)
		return -1;
	return ((s->top==N-1)?1:0);
}

//入栈
int push_stack(stack *s,date_t date)
{
	if(s==NULL)
		return -1;
	printf("date=%d\n",date);
	if(full(s))
		return -1;
	s->date[s->top+1]=date;
	s->top++;
	return 0;
}

//出栈
int pop_stack(stack *s) 
{
	if(NULL==s)
		return -1;
	int date=0;
	date=s->date[s->top];
	s->top--;
	return date;
}
//打印
int printf_stack(stack *s)
{
	if(s==NULL)
		return -1;
	int i;
	for(i=s->top;i>=0;i--)
		printf("%d ",s->date[i]);
	printf("\n");
	return 0;
}

int main()
{
	stack *s=creat_stack();
	if(s==NULL)
		printf("malloc fail\n");
	int i=1;
	while(i<=10)
	{
		push_stack(s,i);
		i++;
	}
	printf_stack(s);
	for(i=0;i<5;i++)
		printf("%d ",pop_stack(s));
	printf("\n");
	printf_stack(s);
	return 0;
}
