#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int bitsert_sort(int *q,int n);
int main()
{
	int a[10]={0,10,2,33,4,58,6,7,80,9};
	int len=sizeof(a)/sizeof(a[0]);
	int i=0;
	for(i=0;i<len;i++)
	printf("%d ",a[i]);
	printf("\n");
	bitsert_sort(a,len);
	for(i=0;i<len;i++)
	printf("%d ",a[i]);
	printf("\n");
	return 0;
}

int bitsert_sort(int *q,int n)
{
	int low,high,mid;
	int i,j,tep;
	for(i=1;i<n;i++)
	{
		tep=q[i];
		low=0;
		high=i-1;
		while(low<=high)
		{
			mid=(low+high)/2;
			if(tep<q[mid])
				high=mid-1;
			else if(tep>q[mid])
				low=mid+1;
			else
				low=mid+1;
		}
		for(j=i;j>mid;j--)
		
			q[j]=q[j-1];
			q[low]=tep;
		

	}
}

