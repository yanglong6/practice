#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int quick_sort(int *a,int l,int n)
{
	if(l<n)
	{
		int i=l,j=n-1,x=a[i];
		while(i<j)
	{
		while(i<j&&a[j]>x)
		j--;
		if(i<j)
		{
			a[i]=a[j];
			i++;
		}
		while(i<j&&a[i]<x)
			i++;
		if(i<j)
		{
			a[j]=a[i];
			j--;
		}
	}
		a[i]=x;
		quick_sort(a,0,i-1);
		quick_sort(a,i+1,n);
	}
}
int main()
{
	int a[]={34,3,56,33,8,9,45,23,8,77};
	int i;
	int n=sizeof(a)/sizeof(a[0]);
	quick_sort(a,0,n);
	for(i=0;i<n;i++)
	printf("%d ",a[i]);
	printf("\n");
	return 0;
}
