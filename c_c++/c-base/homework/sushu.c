#include<stdio.h>
int main()
{
	int i ,j,tep=1,n=0;
	for(i=101;i<=500;i++)
	{
		for(j=2;j<=i/2;j++)
		{
			tep=i%j;
			if(j==(i/2))
			{
				printf("%d\n",i);
				n++;
			}
			if(tep!=0)
				continue;	
			else
				break;
		}
	}
	printf("总数为%d\n",n);
	return 0;
}
