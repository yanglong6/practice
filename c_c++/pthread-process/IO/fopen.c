
#include<stdio.h>
#include<string.h>
int main(int argc,char *argv[])
{
	int c=0;
	int line=0;
	char buf[32];
	if(argc!=2)
		fprintf(stdout,"user:%s filename\n",argv[0]);
	FILE *fq=fopen(argv[1],"r+");
	if(fq==NULL)
	{
		perror("fopen");
		return -1;
	}
	c=fseek(fq,0,SEEK_END);
	if(c!=0)
	{
		perror("fseek");
		return -1;
	}
	c=ftell(fq);

	if(c==EOF)
	{
		perror("ftell");
		return -1;
	}
	printf("%s size is %d\n",argv[1],c);
	fclose(fq);
	return 0;
}
