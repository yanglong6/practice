#include<stdio.h>
int main()
{
	int a,b,c=0,d;
	int n;
	printf("a=");
	scanf("%d",&a);
	printf("b=");
	scanf("%d",&b);
	c=a^b;
	if((a=a>>7)==(b=b>>7))
	{
	if(c==0)
	{
		printf("a=b\n");
	}
	else
	for(n=7;n>=0;n--)
	{
		d=c&(1<<n);
		if(d)
		{
			d=d&a;
			if(d)
			{
				printf("a>b\n");
			}
			else
					printf("a<b\n");
			break;	
		}
//		break;
	}}
	else
	{
            if(a)
		    printf("a<b\n");
	    else
		    printf("a>b\n");
	}
	
  return 0;
}
