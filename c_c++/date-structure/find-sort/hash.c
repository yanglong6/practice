#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef int date_t;

typedef struct hash
{
	date_t date;
	struct hash *next;
}hash;

//哈系表的插入
int insert_hash(hash *biao[],int size,int a[],int len)
{
	if(NULL==biao||a==NULL)
		return -1;
	if(size<0||len<0)
		return -1;
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

//打印
printf_hash(hash *biao[],int size)
{
	if(biao==NULL||size<=0)
		return 0;
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

//查找
hash *find(hash *biao[],int size,date_t key)
{
	if(biao==NULL||size<0)
		return NULL;
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

int main()
{
	int a[11]={23,34,14,38,46,16,68,15,7,31,26};
	hash *biao[11]={NULL};
	int len=sizeof(a)/sizeof(a[0]);
	int size=sizeof(biao)/sizeof(biao[0]);
	insert_hash(biao,size,a,len);
	printf_hash(biao,size);
	hash *q=find(biao,size,68);
	printf("%d ",q->date);
	printf("\n");
	return 0;
}
