#include<stdio.h>
int main()
{
	int i,j,m;
	for(i=1;i<=4;i++)
	{
		for(m=1;m<=(4-i);m++)
		{
			printf(" ");
		}
		for(j=1;j<=(2*i-1);j++)
		{
			printf("*");
		}
		printf("\n");
	}
	return 0;
}
