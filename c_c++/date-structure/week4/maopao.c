/*===============================================================
*   Copyright (C) 2018 All rights reserved.
*   
*   文件名称：maopao.c
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
#include <math.h>
int fun(char *str);
int main()
{
	char a[]={"123456"};
	int b;
	b=fun(a);
	printf("%d\n",b);
	return 0;
}

int fun(char *str)
{
	int n,i, sum=0;
	n=strlen(str);
	int j;
	for(i=0;i<n;i++)
	{
		j=(str[i]-'0')*pow(10,n-i-1);
		sum=sum+j;
	}
	return sum;
}
