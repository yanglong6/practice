#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 64

typedef int data_t;

typedef struct seqlist{
	data_t data[SIZE];//抽象顺序表
	int last;//保存最后一个有效元素的下标
}seq;//给struct seqlist 取别名为 seq

//1.创建顺序表
seq *createSeqlist()
{
	seq *seqlist = (seq *)malloc(sizeof(seq));
	if(NULL == seqlist)
		return NULL;
	memset(seqlist->data, 0, sizeof(seqlist->data));//bzero
	seqlist->last = -1;//说明表中无有效元素

	return seqlist;

}
//2.判断表是否为满
int seqlist_is_full(seq *seqlist)
{
	if(NULL == seqlist)
		return -1;

	return((seqlist->last == SIZE-1)?1:0);
}
//3.判断表是否为空
int seqlist_is_empty(seq *seqlist)
{
	if(NULL == seqlist)
		return -1;

	return ((seqlist->last == -1)?1:0);

}
//4.求顺序表中的元素的个数
int getLengthSeqlist(seq *seqlist)
{
	if(NULL == seqlist)
		return -1;
	
	return (seqlist->last+1);
}

//向顺序表中插入元素
int insertSeqlistByPos(seq* seqlist,int pos, data_t data)
{
	if(seqlist == NULL)
		return -1;
	//判断pos位置是否有效
	if(pos < 0 || pos > seqlist->last+1)
		return -1;
	//判满
	if(seqlist_is_full(seqlist))
		return -1;
	int i;
	for(i=seqlist->last;i>=pos;i--)
		seqlist->data[i+1] = seqlist->data[i];
	seqlist->data[pos] = data;
	seqlist->last++;


	return 0;

}


void printSeqlist(seq *seqlist)
{
	if(NULL == seqlist)
		return ;
	int i;
	for(i=0;i<=seqlist->last;i++)
		printf("%d ",seqlist->data[i]);
	printf("\n");

}

int main()
{
	seq *seqlist = createSeqlist();
	if(NULL == seqlist)
	{
		printf("malloc failed\n");
		return -1;
	}
	int num = getLengthSeqlist(seqlist);
	printf("num=%d\n",num);
	int ret;
	int i = 0;
	while(i<=10)
	{
		ret = insertSeqlistByPos(seqlist,i, i);
		i++;
	}
	printSeqlist(seqlist);
	
	num = getLengthSeqlist(seqlist);
	printf("num=%d\n",num);

	return 0;
}
