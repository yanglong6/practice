#include<stdio.h>
#include<string.h>
int strcmp_fun(char *p,char *q);
int main()
{
	char s1[50]={0};
	char s2[50]={0};
	printf("s1=");
	gets(s1);
	printf("s2=");
	gets(s2);
	if(strcmp_fun(s1,s2)==0)
		printf("s1=s2\n");
	else if(strcmp_fun(s1,s2)>0)
			printf("s1>s2\n");
	else
		printf("s1<s2\n");
	
	return 0;
}

int strcmp_fun(char *p,char *q)
{
	int n,i,j;
	n=strlen(p);
//	printf("n=%d\n",n);
	for(i=0;i<=n;i++)
	{
		if(p[i]!=q[i])
		{
			if(p[i]>q[i])
				j=1;
			else
				j=-1;
			break;
		}
		else
			j=0;
	}
	return j;
}
