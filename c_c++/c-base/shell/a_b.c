#include<stdio.h>
int fun(int **m,int **n);
int main()
{
	int a=1,b=2;
	int *q=&a,*p=&b;
	fun(&q,&p);
	printf("a=%d--b=%d\n",*q,*p);
	return 0;
}

int fun(int **m,int **n)
{
	 int *t=NULL;
	t=*m;
	*m=*n;
	*n=t;
	return 0;
}
