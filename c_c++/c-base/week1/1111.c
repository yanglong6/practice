
#include<stdio.h>
#include<string.h>
#include<math.h>
int fun2(int tep)
{
	int i,j=0;
	int out[8]={0};
	for(i=0;i<8;i++)
	{
		//		c=(tep/2);
		if(tep)
		{
			out[i]=(tep%2);
			tep=(tep/2);
		}	
	}
	for(i=7;i>=0;i--)
	{
		printf("%d",out[i]);
		if(out[i]==1)
			j++;
	}
	printf("\n");
	printf("%d",j);
	printf("\n");
	return 0;
}


int main()
{

	int in;
	scanf("%d",&in);
	fun2(in);
	return 0;
}
