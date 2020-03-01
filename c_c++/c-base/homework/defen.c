#include<stdio.h>
int main()
{
	int a[10]={1,8,0,5,4,5,7,5,9,8};
	int i,j;
	int sum=0,avg=0;
	for(i=0;i<10;i++)
	{
		printf("%-4d",a[i]);
	}
	printf("\n");
	for(i=0;i<10;i++)
	{
		for(j=0;j<9-i;j++)
		{
			if(a[j+1]<a[j])
			{
				a[j+1]=a[j+1]^a[j];
				a[j]=a[j+1]^a[j];
				a[j+1]=a[j+1]^a[j];
			}
		}
	}
	for(i=1;i<9;i++)
	{
		sum=sum+a[i];
	}
	avg=sum/10;
	printf("平均分为%d",avg);
	printf("\n");
	return 0;
}
