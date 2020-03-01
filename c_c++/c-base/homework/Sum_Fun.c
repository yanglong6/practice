#include<stdio.h>
int Sum_Fun(int (*p)[3],int h,int l);
int main()
{
	int a[2][3]={{1,2,3},{4,5,6}};
	int sum=0,hang=0,lei=0;
	hang=sizeof(a)/sizeof(a[0]);
	lei=sizeof(a[0])/sizeof(a[0][0]);
	sum=Sum_Fun(a,hang,lei);
	printf("sum=%d\n",sum);
	return 0;
}

int Sum_Fun(int (*p)[3],int h,int l)
{
	int sum=0;
	int i,j;
	for(i=0;i<h;i++)
	{
		for(j=0;j<l;j++)
		{
			sum=sum+*(*(p+i)+j);
		}
	}
	return sum;
}
