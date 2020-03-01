#include<stdio.h>
char *int_char(int p);
int main()
{
	int a=123;
	printf("%s\n",int_char(a));
	return 0;
}

char *int_char(int p)
{
	int ge,shi,bai;
	static char q[3]={0};
	ge=p%10;
	shi=(p/10)%10;
	bai=p/100;
	q[0]=bai+'0';
	q[1]=shi+'0';
	q[2]=ge+'0';
	return q;
}
