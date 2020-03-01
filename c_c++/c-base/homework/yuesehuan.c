#include<stdio.h>
int main()
{
	int a[10]={1,2,3,4,5,6,7,8,9,10};
	int i=0,n=10,j=0;
	while(1)
	{
		for(i=0;i<2;i++)
		{
			j=(j+1)%n;
		}
	//	printf("%d\n",j);
		printf("%d\n",a[j]);
		for(i=j;i<9;i++)
		{
			a[i]=a[i+1];
		}
		n--;
		if(n==0)
			break;
	}
	return 0;
}
