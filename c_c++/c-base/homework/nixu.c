#include<string.h>
#include<stdio.h>
int main()
{
	char a[100]={0};
	int i,n=0;
	gets(a);
//	puts(a);
        n=strlen(a)/sizeof(char);
	for(i=0;i<n/2;i++)
	{
		a[i]=a[i]^a[n-1-i];
		a[n-1-i]=a[i]^a[n-1-i];
		a[i]=a[i]^a[n-1-i];
	}
	puts(a);
	return 0;
}
