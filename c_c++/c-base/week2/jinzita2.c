#include<stdio.h>
int main()
{
	int i,j,m;
	for(i=1;i<=7;i++)
	{
		if(i<=4)
		{
			for(m=1;m<=(4-i);m++)
			{
				printf(" ");
			}
			for(j=1;j<=(2*i-1);j++)
			{
				printf("*");
			}
			printf("\n");
		}
		else
		{
			for(m=1;m<=(i-4);m++)
			{
				printf(" ");
			}
//	(2*(7-i)+1)
			switch(i)
			{
			
				case 5:printf("*****");break;
				case 6:printf("***");break;
				case 7:printf("*");break;
				default:printf("错误");
		}
			printf("\n");
		}
	}
		return 0;
}
