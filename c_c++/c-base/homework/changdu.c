
#include<string.h>
#include<stdio.h>
int main()
{
	char a[100]={0};
	int i,n=0;
	gets(a);
//	puts(a);
	for(i=0;i<100;i++)
	{
		if(a[i]!='\0')
		   n++;
		else
			break;
	}
	printf("%d\n",n);
	return 0;
}
