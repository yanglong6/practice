#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main(int argc,char *argv[])
{
	FILE *fq;
	fq=fopen("text.txt","r+");
	if(NULL==fq)
	{
		perror("fopen");
		return -1;
	}

	fq=freopen("text.txt","r+",stdout);
	if(fq==NULL)
	{
		perror("freopen");
		return -1;
	}
	printf("world\n");
	return 0;
}
