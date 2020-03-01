#include<stdio.h>
int main()
{
	int a,n=0,m=0,s1=0,s2=0;
	double  a1=0,a2=0;
loop:	scanf("%d",&a);
	while(a)
	{
		if(a%2==0)
		{
			n++;
			s1=s1+a;
		}
		else
		{
			m++;
			s2=s2+a;
		}
		goto loop;
	}
	if(n==0)
	a1=s1/(n+1);
	else
	a1=s1/n;
	if(m==0)
	a2=s2/(m+1);
	else
	a2=s2/m;	
	printf("偶数和为：%d\n",s1);
	printf("奇数和为：%d\n",s2);
	printf("偶数个数为：%d\n",n);
	printf("奇数个数为：%d\n",m);
	printf("偶数平均值为：%f\n",a1);
	printf("奇数平均值为：%f\n",a2);
	return 0;
}

