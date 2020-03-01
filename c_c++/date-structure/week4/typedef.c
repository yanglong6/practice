/*===============================================================
*   Copyright (C) 2018 All rights reserved.
*   
*   文件名称：typedef.c
*   创建人  ： yang long
*   创建日期：2018年07月30日
*   描    述：
*
*   更新日志：
*
================================================================*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <strings.h>
typedef struct yy
{
	char name[10];
	int id;
	int score;
}s;

int main()
{
	s *q=malloc(sizeof(s));
	strcpy(q->name,"yanglong");
	q->id=1;
	q->score=100;
	printf("%s\n",q->name);
	printf("%d\n",q->id);
	return 0;
}
