#include<stdio.h>
int main()
{
	int a[3][4]={{2,4,340,12},{1,23,7,8},{44,56,7,90}};
	int i,j,max=a[0][0];
	int lei=0,hang=0;
	for(i=0;i<3;i++)
	{
		for(j=0;j<4;j++)
		{
			if(a[i][j]>max)
			{
				max=a[i][j];
				lei=j;
				hang=i;
			}
		}
	}
	printf("max=%d\n",max);
        printf("行=%d\n",hang);
	printf("列=%d\n",lei);
	return 0;
}
