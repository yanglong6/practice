#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef int date_t ;

typedef struct double_node
{
	date_t date;
	struct double_node *pre,*next;
}node;

//创建链表
node *create()
{
	node *head=(node *)malloc(sizeof(node));
	if(head==NULL)
		return NULL;
	head->date=-1;
	head->pre=NULL;
	head->next=NULL;
	return head;
}
//判空
int empty(node *head)
{
	if(head==NULL)
		return -1;
	return ((head->next==NULL)?1:0);
}
//有效节点长度
int leng(node *head)
{
	node *q=head->next;
	int n=0;
	while(q!=NULL)
	{
		n++;
		q=q->next;
	}
	return n;
}
//按位置插入
int sert(node *head,int pos,date_t date)
{
	if(head==NULL)
		return -1;
	int n=leng(head);
	if(pos<0||pos>n)
		return -1;
	node *new=(node *)malloc(sizeof(node));
	if(new==NULL)
		return -1;
	new->date=date;
	new->pre=NULL;
	new->next=NULL;

	node *q=head;
	while(pos--)
		q=q->next;
	if(q->next!=NULL)
	{
		new->next=q->next;
		q->next->pre=new;
		q->next=new;
		new->pre=q;
	}
	else
	{
		q->next=new;
		new->pre=q;
	}
	return 0;
}
int printf_node(node *head)
{
	if(head==NULL)
		return -1;
	node *q=head->next;
	while(q!=NULL)
	{
		printf("%d ",q->date);
		q=q->next;
	}
	printf("\n");
}
int main()
{
	node *head=create();
	if(head==NULL)
		return -1;
	int i=0;
	while(i<10)
	{
		sert(head,i,i);
		i++;
	}
	printf_node(head);
	return 0;
}
