#include<stdio.h>
#include<string.h>
int main()
{
	char a[100]={"ab cd ef"};
	char b[100]={"yang long"};
	int i,n;
	n=strlen(b);
	for(i=0;i<=n;i++)
	{
		a[i]=b[i];
	}
	puts(a);

	return 0;
}
