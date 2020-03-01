#include<stdio.h>
int main()
{
	char a[100]={0};
	int i,count=0;
	gets(a);
//	puts(a);
	for(i=0;i<=100;i++)
	{
		if(a[i]==' ')
			count++;
	}
	printf("空格总数为：%d\n",count);
	return 0;
}
