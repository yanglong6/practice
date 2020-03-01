#include<stdio.h>
#include<string.h>
char *chuan(char *p,int n);
int main()
{
	int n=0;
	char a[100]={0};
	char *q=NULL;
	gets(a);
	n=strlen(a);
	q=chuan(a,n);
	puts(q);
	printf("sum=%d\n",strlen(q));
	return 0;
}

char *chuan(char *p,int n)
{
	int i=0,b=2,k=0,j=1,sum;
	static char d[100]={0};
	while(p[i]!='\0')
	{
		sum=1;
		while(p[i+1]==p[i])
		{
			sum=sum+1;
			i++;
		}
		i++;
		if(sum>=b)
		{
			b=sum;
			j=i;
		}
	}
	for(i=j-1;i>=(j-b);i--)
	{
		d[k]=p[i];
		k++;
	}
	return d;
}
