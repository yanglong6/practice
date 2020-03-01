/*===============================================================
 *   Copyright (C) 2018 All rights reserved.
 *   
 *   文件名称：struct.c
 *   创建人  ： yang long
 *   创建日期：2018年07月28日
 *   描    述：
 *
 *   更新日志：
 *
 ================================================================*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <strings.h>
#define N 100

struct student
{
	char name[30];
	int id;
	int score;
};

int main()
{
	struct student s[N];
	struct student *e;
	int i;
	printf("name id score\n");
	for(i=0;i<N;i++)
	{
	//	scanf("%s#%d#%d",s[i].name,&(s[i].id),&(s[i].score));
		printf("name:");
		if(gets(e->name)=="#")
			break;
		else
		s[i].name=e->name;
		printf("id:");
		scanf("%d",&(s[i].id));
		printf("score:");
		scanf("%d",&(s[i].score));
//		getchar();
		
	}
//	for(i=0;i<N;i++)
//	{
//		printf("%s ",s[i].name);
//		printf("%d ",s[i].id);
//		printf("%d\n",s[i].score);
//	}
	return 0;
}
