#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define N 30
typedef int date_t;

typedef struct linear_list
{
	date_t date[N];
	int last;
}list;

//创建线性表
list *creat_list()
{
	list *seq=(list *)malloc(sizeof(list));
	if(seq==NULL)
		return NULL;
	memset(seq,0,sizeof(list));
	seq->last=-1;
	return seq;
}

//判空
int empty(list *seq)
{
	if(seq==NULL)
		return -1;
	return ((seq->last==-1)?1:0);
}

//判满
int full(list *seq)
{
	if(seq==NULL)
		return -1;
	return ((seq->last==N-1)?1:0);
}

//插入数据
int insert(list *seq,int pos,date_t date)
{
	if(seq==NULL)
		return -1;
	if(full(seq))
		return -1;
	if(pos<0||pos>seq->last+1)
		return -1;
	int i;
	for(i=seq->last;i>=pos;i--)
		seq->date[i+1]=seq->date[i];
	seq->date[pos]=date;
	seq->last++;
	return 0;
}

//打印
int printf_list(list *seq)
{
	if(seq==NULL)
		return 0;
	int i=0;
	while(i<=seq->last)
	{
		printf("%d ",seq->date[i]);
		i++;
	}
	printf("\n");
	return 0;
}
int main()
{
	list *seq=creat_list();
	if(seq==NULL)
	{
		printf("malloc fail");
	}
	int i=0;
	while(i<=10)
	{
	insert(seq,i,i);
	i++;
	}
	printf_list(seq);
	return 0;
}
