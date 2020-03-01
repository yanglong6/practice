#include<stdio.h>
int main()
{
	int i,j,k;
	int a[10][10]={{0}};
	for(i=0;i<10;i++)
	{
		for(j=0;j<=i;j++)
		{
			a[i][j]=1;
			if((i>=2))
				a[i][j]=a[i-1][j]+a[i-1][j-1];
		}
	}
	for(i=0;i<10;i++)
	{
		for(k=0;k<18-2*i;k++)
			printf(" ");
		for(j=0;j<=i;j++)
		{
			printf("%-4d",a[i][j]);
		}
		printf("\n");
	}
	return 0;
}
