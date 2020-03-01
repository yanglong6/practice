
#include<string.h>
#include<stdio.h>
int main()
{
	int a[]={1,2,3,4,5,6,7,8,9,10};
	int *p;
	int i,n=0;
	p=a;
        n=sizeof(a)/sizeof(int);
	for(i=0;i<n;i++)
	{
		printf("%-3d",*(p+i));
	}
	putchar('\n');
	for(i=0;i<n/2;i++)
	{
		*(p+i)=*(p+i)^*(p+n-1-i);
		*(p+n-1-i)=*(p+i)^*(p+n-1-i);
		*(p+i)=*(p+i)^*(p+n-1-i);
	}
	for(i=0;i<n;i++)
	{
		printf("%-3d",*(p+i));
	}
	puts("");
	return 0;
}
