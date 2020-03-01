#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int bit_find(int *q,int n,int key);
int main()
{
	int a[10]={0,1,2,3,4,5,6,7,8,9};
	int len=sizeof(a)/sizeof(a[0]);
	int tet=bit_find(a,len,6);
	printf("%d\n",tet);
	return 0;
}

int bit_find(int *q,int n,int key)
{
	int low=0;
	int high=n-1;
	int mid=(low+high)/2;
	while(low<=high)
	{
		if(key<q[mid])
		{
			high=mid-1;
			mid=(low+high)/2;
		}
		else if(key>q[mid])
		{
			low=mid+1;
			mid=(low+high)/2;
		}
		else
			return mid;
	}
	return -1;
}

