#include<stdio.h>
#include<string.h>
int main()
{
	int i;
	char m='*';
	char a[20]="        VeryGood";
	for(i=0;i<24;i++)
	{
		putchar(m);
	}
	puts("");
	puts(a);
//	puts("");
	for(i=0;i<24;i++)
	{
		putchar(m);
	}
	puts("");
	return 0;
}
