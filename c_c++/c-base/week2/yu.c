#include<stdio.h>
int main()
{
	int in,out1,out2,tep1,tep2,m=4,n=0xfb;
	scanf("%d",&in);
	printf("in=%d\n",in);
	out1=(in|m);
	out2=(in&n);
	printf("out1=%d\n",out1);
	tep1=(in^out1)/2;
	printf("第%d位置1\n",tep1);
	printf("out=2%d\n",out2);
	tep2=(in^out2)/2;
	printf("第%d位置0\n",tep2);
	return 0;
}
