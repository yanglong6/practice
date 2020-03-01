#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int direct_sort(int *a,int n)
{
	int i=0,j=0,tep=0;
	for(i=1;i<n;i++)
	{
		tep=a[i];
		j=i-1;
		while(j>=0&&tep<a[j])
		{
			a[j+1]=a[j];
				j--;
		}
		a[j+1]=tep;
	}
}
int main()
{
	int a[]={2,34,9,23,66,8,55,1,0,33};
	int n=sizeof(a)/sizeof(a[0]);
	int i=0;
	for(i=0;i<n;i++)
		printf("%d ",a[i]);
	printf("\n");
	direct_sort(a,n);
	for(i=0;i<n;i++)
		printf("%d ",a[i]);
	printf("\n");
	return 0;
}

