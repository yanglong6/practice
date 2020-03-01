#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef int date_t;

typedef struct linknode
{
	date_t date;
	struct linknode *next;
}link;

//建立链表
link *create_linknode()
{
	link *seq=(link *)malloc(sizeof(link));
	if(seq==NULL)
		return NULL;
	seq->next=NULL;
	seq->date=-1;
	return seq;
}
//判空
int empty(link *seq)
{
	if(seq==NULL)
		return -1;
	return ((seq->next==NULL)?1:0);
}
//有效节点
int leng(link *seq)
{
	if(seq==NULL)
		return -1;
	link *q=seq;
	int i=0;
	while(q->next!=NULL)
	{
		i++;
		q=q->next;
	}
	return i;
}
//插入节点
int sert(link *seq,int pos,date_t date)
{
	if(seq==NULL)
		return -1;
	if(pos<0)
		return -1;
	link *new=(link *)malloc(sizeof(link));
	new->date=date;
	new->next=NULL;

	link *q=seq;
	while(pos--)
		q=q->next;
	new->next=q->next;
	q->next=new;
	return 0;
}
//按位置查找，返回地址
link *find_load(link *seq,int pos)
{
	int n=leng(seq);
	if(pos<0||pos>=n)
		return NULL;
	link *q=seq->next;
	while(pos--)
		q=q->next;
	return q;
}
//按位置删除
int delete_load(link *seq,int pos)
{
	if(seq==NULL)
		return -1;
	int n=leng(seq);
	if(pos<0||pos>=n)
		return -1;
	link *q=seq;
	link *p=NULL;
	while(pos--)
		q=q->next;
	p=q->next;
	q->next=p->next;
	free(p);
	p=NULL;
	return 0;
}
//打印
int printf_node(link *seq)
{
	link *q=seq->next;
	while(q!=NULL)
	{
		printf("%d ",q->date);
		q=q->next;
	}
	printf("\n");
	return 0;
}

int main()
{
	int i=0;
	link *seq=create_linknode();
	while(i<10)
	{

		sert(seq,i,i);
		i++;
	}
	printf_node(seq);

	link *q=find_load(seq,4);
	printf("q->date=%d\n",q->date);

	delete_load(seq,4);
	printf_node(seq);
	return 0;
}
