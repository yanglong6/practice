
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc,char *argv[])
{
	int ret=0;
	char buf[400];
	if(argc!=3)
	{
		fprintf(stderr,"%s <file> <file>\n",argv[0]);
		return -1;
	}
	FILE *fq1=fopen(argv[1],"r+");
	if(fq1==NULL)
	{
		perror("f1dpen");
		return -1;
	}

	FILE *fq2=fopen(argv[2],"w+");
	if(fq2==NULL)
	{
		perror("f2dopen");
		return -1;
	}
	memset(buf,0,sizeof(buf));
	while(1)
	{
	ret=fread(buf,1,sizeof(buf),fq1);
	if(ret<0)
	{
		close(fq2);
		return -1;
	}
	if(ret==0)
		break;
	fwrite(buf,1,ret,fq2);
	
	}	
	
	fclose(fq1);
	fclose(fq2);
}
