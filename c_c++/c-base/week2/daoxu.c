#include<stdio.h>
int main()
{
	int a[10]={0};
	int i,j;
	for(i=2;i<10;i++)
	{
		a[0]=1;
		a[1]=1;
		a[i]=a[i-1]+a[i-2];
	}
	for(i=0;i<10;i++)
	{
		printf("%-4d",a[i]);
	}
	printf("\n");
	for(i=0;i<10;i++)
	{
		for(j=0;j<9-i;j++)
		{
			if(a[j+1]>a[j])
			{
				a[j+1]=a[j+1]^a[j];
				a[j]=a[j+1]^a[j];
				a[j+1]=a[j+1]^a[j];
			}
		}
	}
	for(i=0;i<10;i++)
	{
		printf("%-4d",a[i]);
	}
	printf("\n");
	return 0;
}
