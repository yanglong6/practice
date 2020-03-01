#include<stdio.h>
#include<string.h>
#include<math.h>
int fun2(int tep,int out[])
{
	int i;
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
	}
	printf("\n");
	return 0;
}

int fun8(int m,int out[])
{
	int i;
	for(i=0;i<8;i++)
	{
		//		c=(tep/2);
		if(m)
		{
			out[i]=(m%8);
			m=(m/8);
		}	
	}
	for(i=7;i>=0;i--)
	{
		printf("%d",out[i]);
	}
	printf("\n");
	return 0;
}

int fun16(int a,char out[])
{
	int i;
	char cun[16]={"0123456789ABCDEF"};
	for(i=0;i<8;i++)
	{
		if(a)
		{
			out[i]=cun[(a%16)];
			a=(a/16);
		}}
	for(i=0;i<8;i++)
	{
		printf("%c",out[i]);
	}
	printf("\n");
	return 0;
}

int main()
{

	int in;
	int out1[8]={0};
	int out2[8]={0};
	char out3[8]={0};
	scanf("%d",&in);
	fun2(in,out1);
	fun8(in,out2);
	fun16(in,out3);
	return 0;
}
