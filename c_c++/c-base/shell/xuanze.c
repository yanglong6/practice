#include<stdio.h>
#define N 5
int main()
{
	int a[N]={0};
	int i,j;
	for(i=0;i<N;i++)
	{
		scanf("%d",&a[i]);
	}
	for(i=0;i<N-1;i++)
	{
		for(j=(i+1);j<N;j++)
		{
			if(a[i]>a[j])
			{
				a[i]=a[i]^a[j];
				a[j]=a[i]^a[j];
				a[i]=a[i]^a[j];
			}
		}
	}
	for(i=0;i<N;i++)
	{
		printf("%d ",a[i]);
	}
	printf("\n");
	return 0;
}
