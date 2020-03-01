#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef int date_t;

typedef struct dlinknode
{
	date_t date;
	struct dlinknode *pri,*next;
}dlist;

//创建双向链表
dlist *creat_list()
{
	dlist *head=(dlist *)malloc(sizeof(dlist));
	if(head==NULL)
		return NULL;
	head->date=-1;
	head->pri=head;
	head->next=head;
	return head;
}

//判空
int empty(dlist *head)
{
	if(head==NULL)
		return -1;
	return ((head->next==head)?1:0);
}

//有效节点个数
int list_number(dlist *head)
{
	if(head==NULL)
		return -1;
	int number=0;
	dlist *q=head->next;
	while(q!=head)
	{
		number++;
		q=q->next;
	}
	return number;
}

//按位置插入数据
int insert_list(dlist *head,int pos,date_t date)
{
	if(head==NULL)
		return -1;
	int leng=list_number(head);
	if(pos<0||pos>leng)
		return -1;
	dlist *new=(dlist *)malloc(sizeof(dlist));
	dlist *q=head;
	if(new==NULL)
		return -1;
	while(pos--)
		q=q->next;
//	if(q->next!=head)
//	{
		new->next=q->next;
		q->next->pri=new;
		q->next=new;
		new->pri=q;
//	}
#if 0
	else
	{
		q->next=new;
		new->pri=q;
	}
#endif
	new->date=date;
	return 0;
}

//按位置删除
int delete_list(dlist *head,int pos)
{
	if(head==NULL)
		return -1;
int leng=list_number(head);
	if(pos<0||pos>leng-1)
		return -1;
	dlist *p=head;
	dlist *q=NULL;
	while(pos--)
		p=p->next;
		q=p->next;
	//中间删
//	if(p->next->next!=NULL)
//	{
		p->next=q->next;
		q->next->pri=q->pri;
		free(q);
		q=NULL;
#if 0
	}
	else
	{
		p->next=q->next;
		free(q);
		q=NULL;
	}
#endif
	return 0;
}
//按值删除

//按位置查找
dlist *find_load(dlist *head,int pos)
{
	if(head==NULL)
		return NULL;
int leng=list_number(head);
	if(pos<0||pos>leng)
		return NULL;
	dlist *q=head->next;
	while(pos--)
	{
		q=q->next;
	}
	return q;
}

//按值查找
dlist *find_date(dlist *head,date_t date)
{
	if(head==NULL)
		return NULL;
	dlist *q=head->next;
	while(q->date!=date)
		q=q->next;
	return q;
}
//按位置修改
int change_load(dlist *head,int pos,date_t date)
{
	if(head==NULL)
		return -1;
	dlist *q=find_load(head,pos);
	if(q==NULL)
		return -1;
	q->date=date;
	return 0;
}
//按值修改
//打印
int printf_list(dlist *head)
{
	if(head==NULL)
		return -1;
	dlist *q=head->next;
	while(q!=head)
	{
		printf("%d ",q->date);
			q=q->next;
	}
	printf("\n");
}
int main()
{
	dlist *head=creat_list();
	if(head==NULL)
		return 0;
	int i;
	for(i=0;i<10;i++)
	{
		insert_list(head,i,i);
	}
	printf_list(head);
		insert_list(head,7,77);
	printf_list(head);

	delete_list(head,10);
	printf_list(head);

	dlist *q=find_load(head,7);
	printf("%d\n",q->date);
	change_load(head,2,222);
	printf_list(head);
	q=find_date(head,222);
	printf("%d\n",q->date);
	return 0;
}
