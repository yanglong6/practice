#include<stdio.h>
int main()
{
	int a[2][3]={{1,2,3},{4,5,6}};
	int hang;
	int i,j;
	int (*q)[3];
//	q[0]=a[0];
//	q[1]=a[1];
//	q[2]=a[2];
        q=a;	
	hang=sizeof(a)/sizeof(a[0]);
	printf("%d\n",hang);
	for(i=0;i<hang;i++)
	{
		for(j=0;j<3;j++)
		{
			printf("%d ",*(*(q+i)+j));

		}
		printf("\n");
	}
	return 0;
}
