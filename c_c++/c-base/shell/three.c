/*===============================================================
*   Copyright (C) 2018 All rights reserved.
*   
*   文件名称：three.c
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
int main()
{
	char a[N]={0};
	char *b;
	int i,j,chu=N,k=0,n;
	gets(a);
	n=strlen(a);
	b=a;
	for(i=0;i<n;i++)
	{
		k=0;
		for(j=0;j<n;j++)
		{
		if(a[i]==b[j])
		{
			k++;
			if(k==3)
			{
				if(chu>j)
				chu=j;	
				break;
			}
		}
		}
	}
	printf("%c\n",a[chu]);
	return 0;
}
