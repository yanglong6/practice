#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define N 32
typedef int date_t;

typedef struct linear
{
	date_t date[N];
	int last;
}list;

//创建表
list *creat_linear()
{
	list *seq=(list *)malloc(sizeof(list));
	if(seq==NULL)
		return NULL;
	memset(seq->date,0,sizeof(seq->date));
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
//有效元素的个数
int number(list *seq)
{
	if(seq==NULL)
		return -1;
	return (seq->last+1);
}

//按值查找，返回下标
int find_load(list *seq,date_t date)
{
	if(seq==NULL)
		return -1;
	if(empty(seq))
		return -1;
	int i=0;
	int n=number(seq);
	while(date!=seq->date[i])
	{
			i++;
			if(i==n)
			{
				return -1;
				break;
			}
	}
	return i;
}
//position插入
int sert_linear(list *seq,int pos,date_t date)
{
	if(seq==NULL)
		return -1;
	if(full(seq))
		return -1;
	int i=0;
	for(i=seq->last;i>=pos;i--)
		seq->date[i+1]=seq->date[i];
	seq->date[pos]=date;
	seq->last++;
	return 0;
}

//按位置删除
int delete_load(list *seq,int pos)
{
	if(seq==NULL)
		return -1;
	if(empty(seq))
		return -1;
	if(pos<0||pos>seq->last)
		return -1;
	int i;
	for(i=pos;i<=seq->last;i++)
		seq->date[i]=seq->date[i+1];
	seq->last--;
	return 0;
}
int main()
{
	list *seq=creat_linear();
	if(seq==NULL)
		return -1;
	int i=0;
	while(i<10)
	{
		sert_linear(seq,i,i);
		i++;
	}
	for(i=0;i<10;i++)
		printf("%d ",seq->date[i]);
	printf("\n");

	printf("number=%d\n",number(seq));
	int j=find_load(seq,6);
	printf("%d\n",seq->date[j]);

	delete_load(seq,5);
	for(i=0;i<9;i++)
		printf("%d ",seq->date[i]);
	printf("\n");
	return 0;
}
