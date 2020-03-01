#include<stdio.h>
int main()
{
	char in,out;
	puts("输入：");
       in= getchar();
       if(in>='0'&&in<='9')
       {	       putchar(in);
       putchar('\n');
       }
       else if(in>='a'&&in<='z')
       {
	       out=in-32;
       putchar(out);
       putchar('\n');
       }
       else if(in>='A'&&in<='Z')
       {
	       out=in+32;
       putchar(out);
       putchar('\n');
       }
       else
       {       puts("错误");
       }
       

	return 0;
}
