
#include<string.h>
#include<stdio.h>
int main()
{
	char a[100]={0};
	char b;
	int i,j,n=0;
	gets(a);
	printf("要删除的字符：");
	b=getchar();
//	puts(a);
        n=strlen(a)/sizeof(char);
	for(i=0;i<n;i++)
	{
		if(a[i]==b)
		{
			for(j=i;j<n;j++)
			{
			a[j]=a[j+1];
			}
			i--;
		}
	}
	//puts(a);
	printf("%s\n",a);
	return 0;
}
