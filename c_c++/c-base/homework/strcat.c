#include<stdio.h>
#include<string.h>
int main()
{
	char a[100]={0};
	char b[100]={0};
	char *p=NULL,*q=NULL;
	int n,m,i;
	gets(a);
	gets(b);
	n=strlen(a);
	m=strlen(b);
	p=a+n;
	q=b;
	for(i=0;i<=m;i++)
	{
		*(p+i)=*(q+i);
		if(*(p+i)=='\0')
			break;
	}
	puts(a);
	return 0;
}
