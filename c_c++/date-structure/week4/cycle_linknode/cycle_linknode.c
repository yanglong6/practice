#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"linknode.h"

//建立链表
lnode *creat_list()
{
	lnode *head=(lnode *)malloc(sizeof(lnode));
	if(head==NULL)
		return NULL;
	head->date=-1;
	head->next=head;
	return head;
}
//判空
int empty(lnode *head)
{
	if(NULL==head)
		return 0;
	return((head->next==head)?1:0);
}
//有效长度
int len(lnode *head)
{
	if(NULL==head)
		return -1;
	int number=0;
	lnode *q=head->next;
	while(q!=head)
	{
		number++;
		q=q->next;
	}
	return number;
}
//按位置添加节点
int addnode_load(lnode *head,int pos,date_t date)
{
	if(head==NULL)
		return -1;
	if(pos<0)
		return -1;
	lnode *new=(lnode *)malloc(sizeof(lnode));
	if(new==NULL)
		return -1;
	new->date=date;
	new->next=NULL;
	lnode *p=head;
	while(pos--)
		p=p->next;
	new->next=p->next;
	p->next=new;

	return 0;
}
//按位置查找节点，返回地址
lnode *find_load(lnode *head,int pos)
{
	if(head==NULL)
		return NULL;
	lnode *q=head->next;
	while(pos--)
		q=q->next;
	return q;
}
//按值查找节点，返回地址
lnode *find_date(lnode *head,int date)
{
	if(head==NULL)
		return NULL;
	lnode *q=head->next;
	while(q!=head)
	{
		if(q->date==date)
		return q;
		else
		q=q->next;
	}
	return NULL;
}
//按位置删除节点
int delete_load(lnode *head,int pos)
{
	if(head==NULL)
		return 0;
	int leng;
	leng=len(head);
	if(pos<0||pos>leng-1)
		return -1;
	lnode *p=head;
	lnode *q=NULL;
	while(pos--)
	{
		p=p->next;
	}
	q=p->next;
	p->next=q->next;
	free(q);
	q=NULL;
	return 0;
}
//按值删除节点
int delete_date(lnode *head,date_t date)
{
	if(head==NULL)
		return -1;
	lnode *q=find_date(head,date);
	if(q==NULL)
		return -1;
	lnode *p=head;
	if(q==NULL)
		return -1;
	while(p->next!=q)
		p=p->next;
	q=p->next;
	p->next=q->next;
	free(q);
	q=NULL;
	return 0;
}

//按地址修改：
int change_load(lnode *head,int pos,date_t new)
{
	if(head==NULL)
		return -1;
	lnode *q=find_load(head,pos);
	if(q==NULL)
		return -1;
		q->date=new;
	return 0;
}

//按值修改
int change_date(lnode *head,date_t old,date_t new)
{
	if(head==NULL)
		return -1;
	lnode *q=find_date(head,old);
	if(q==NULL)
		return -1;
	q->date=new;
	return 0;
}

//清空链表
int clear(lnode *head)
{
	if(head==NULL)
		return -1;
#if 0
	int n=len(head)+1;
	while(n--)
	delete_load(head,0);
#endif
	lnode *q=head->next;
	lnode *p=NULL;
	while(q!=head)
	{
		p=q->next;
		free(q);
		q=NULL;
		q=p;
	}
	return 0;
}

//清除链表
int distroy(lnode **head)
{
	if(head==NULL)
		return -1;
	clear(*head);
		free(*head);
	*head=NULL;
	return 0;
}
//打印
void printf_node(lnode *head)
{
	lnode *q=head->next;
	while(q!=head)
	{
		printf("%d ",q->date);
		q=q->next;
	}
	printf("\n");
}

