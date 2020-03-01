#include<stdio.h>
int main()
{
	int i,j,m=1,s=0;
	for(i=1;i<=5;i++)
	{

			m=m*i;
			s=s+m;
	}
	printf("%d\n",s);
	return 0;
}
