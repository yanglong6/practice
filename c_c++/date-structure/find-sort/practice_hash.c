#include<stdio.h>
#include<stdlib.h>
typedef int date_t;
typedef struct hash
{
	date_t date;
	struct hash *next;
}hash;

int insert_hash(hash *biao[],int a[],int size,int len)
{
	int pos=0,i=0;
	for(i=0;i<len;i++)
	{
		pos=a[i]%size;
		hash *new=(hash *)malloc(sizeof(hash));
		new->date=a[i];
		new->next=NULL;

		if(biao[pos]==NULL)
			biao[pos]=new;
		else
		{
			new->next=biao[pos];
			biao[pos]=new;
		}
	}
	return 0;
}

//查找
hash *find(hash *biao[],int size,date_t key)
{
	int pos=key%size;
	if(biao[pos]==NULL)
		return NULL;
	else
	{
		hash *p=biao[pos];
		while(p)
		{
			if(p->date==key)
				return p;
			else
				p=p->next;
		}
		return NULL;
	}
}
//打印
void print_biao(hash *biao[],int size)
{
	hash *p=NULL;
	int i;
	for(i=0;i<size;i++)
	{
		p=biao[i];
		while(p)
		{
			printf("%d ",p->date);
			p=p->next;
		}
	}
	printf("\n");
}
int main()
{
	int a[]={23,14,45,44,9,18,67,39,57,28,37};
	hash *biao[11]={NULL};
	insert_hash(biao,a,11,11);
	print_biao(biao,11);
	hash *q=find(biao,11,28);
	printf("%d",q->date);
	printf("\n");
	return 0;
}
