#include<stdio.h>
int main()
{
int a,b,c;
printf("a b c\n");
scanf("%d %d %d",&a,&b,&c);
if(a>b)
{
	if(a>c)
		printf("a最大\n");
	else
		printf("c最大\n");
}
else
{
	if(b>c)
		printf("b最大\n");
	else
		printf("c最大\n");

}
return 0;
}
