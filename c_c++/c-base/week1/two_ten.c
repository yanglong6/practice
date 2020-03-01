#include<stdio.h>
//#include<string.h>
#include<math.h>

int fun2()
{
	int in[8]={0};
	int i;
	for(i=0;i<8;i++)
	{
          scanf("%d",&in[i]);
	}

	double tep=0,sum=0;

	for(i=0;i<8;i++)
//	 printf("%d",*p++);
	{
	       tep=in[i]*pow(2,7-i);		     
		sum=sum+tep;
	}
	printf("%f\n",sum);
	return 0;

	}

int fun8()
{
	int in[8]={0};
	int i;
	for(i=0;i<8;i++)
	{
          scanf("%d",&in[i]);
	}

	double tep=0,sum=0;

	for(i=0;i<8;i++)
//	 printf("%d",*p++);
	{
	       tep=in[i]*pow(8,7-i);		     
		sum=sum+tep;
	}
	printf("%f\n",sum);
	return 0;
}

int fun16()
{
	char in[8];
	int i;
//	for(i=1;i<8;i++)
//	{
          scanf("%s",in);
//	}
     //   gets(in);
	puts(in);

	double tep=0,sum=0;

	for(i=0;i<8;i++)
//	 printf("%d",*p++);
	{
		if('0'<=in[i]&&'9'>=in[i])
	
	       tep=(in[i]-'0')*pow(16,7-i);
		else
		tep=(in[i]-'A'+10)*pow(16,7-i);
		sum=sum+tep;
	}
	printf("%f\n",sum);
	return 0;
}

int main()
{ 
	int z;
	puts("选择:");
          scanf("%d",&z);
	  switch(z)
	  {

case 1:	fun2();
	break;
case 2:	fun8();
	break;
case 3:	fun16();
	break;
	  }
	return 0;
}
