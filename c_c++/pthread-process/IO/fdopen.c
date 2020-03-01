#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
	FILE *fq=fopen("jilu.c","r+");
	if(fq==NULL)
	{
		perror("fdopen");
		return -1;
	}
	fprintf(fq,"hallo\n");
	fclose(fq);
}
