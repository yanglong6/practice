/*===============================================================
*   Copyright (C) 2018 All rights reserved.
*   
*   文件名称：linear.c
*   创建人  ： yang long
*   创建日期：2018年07月31日
*   描    述：
*
*   更新日志：
*
================================================================*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <strings.h>
#include"linear.h"

//1.创建顺序表
list *creat_list()
{
	list *seq=(list *)(malloc(sizeof(list)));
	if(NULL==seq)
		return NULL;
	memset(seq->date,0,sizeof(seq->date));
	seq->last=-1;
	return seq;
}

//2.判断是否为满
int full(list *seq)
{
	if(NULL==seq)
		return -1;
	return ((seq->last==SIZE-1)?1:0);

}
//3.判断是否为空
int empty(list *seq)
{
	if(NULL==seq)
		return -1;
	return ((seq->last==-1)?1:0);
}
//4.求元素的个数
int leng(list *seq)
{
	if(NULL==seq)
		return -1;
	return (seq->last+1);
}
//5.插入元素
int insert(list *seq,int poe,int date)
{
	if(NULL==seq)
		return -1;
	if(poe<0||poe>seq->last+1)
		return -1;
	 if(full(seq))
		return -1;
	int i;
	for(i=seq->last;i>=poe;i--)
		seq->date[i+1]=seq->date[i];
		seq->date[poe]=date;
			seq->last++;
			return 0;
}
//6.打印
int printlist(list *seq)
{
	if(NULL==seq)
		return -1;
	int i;
	for(i=0;i<=seq->last;i++)
		printf("%d ",seq->date[i]);
	printf("\n");
	return 0;
}
//7.删除指定位置
int delet_load(list *seq,int poe)
{
	if(NULL==seq)
		return -1;
	if(poe<0||poe>seq->last)
		return -1;
	if(empty(seq))
		return -1;
	int i;
	for(i=poe;i<=seq->last;i++)
		seq->date[i]=seq->date[i+1];
	seq->last--;
	return 0;
}
//8.找到某值的下标
int find(list *seq,int date)
{
	if(NULL==seq)
		return -1;
	int i;
	for(i=0;i<=seq->last;i++)
	{
		if(seq->date[i]==date)
			return i;
	}
	return -1;
}
//9.按值删除
int delet_zhi(list *seq,int date)
{
	int load;
	if(NULL==seq)
		return -1;
	load=find(seq,date);
	if(load==-1)
		return -1;
	delet_load(seq,load);
	return 0;
}
//10.按位置修改
int chang_load(list *seq,int poe,int date)
{
	if(NULL==seq)
		return -1;
	if(poe<0||poe>seq->last)
		return -1;
	if(empty(seq))
		return -1;
	seq->date[poe]=date;
	return 0;
}
//11.按值修改
int chang_zhi(list *seq,int old,int new)
{
	if(NULL==seq)
		return -1;
	int i;
	i=find(seq,old);
	if(i==-1)
		return -1;
	seq->date[i]=new;
	return 0;
}
