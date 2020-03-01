

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc,char *argv[])
{
	int ret=0;
	char buf[50*640];
	if(argc!=3)
	{
		fprintf(stderr,"%s file\n",argv[0]);
		return -1;
	}
	FILE *fq1=fopen(argv[1],"r+");
	if(fq1==NULL)
	{
		perror("fdopen");
		return -1;
	}
	FILE *fq2=fopen(argv[2],"r+");
	if(fq2==NULL)
	{
		perror("fdopen");
		return -1;
	}

	fseek(fq1,50,SEEK_SET);
	fseek(fq2,50,SEEK_SET);
	
	while(1)
	{
		memset(buf,0,sizeof(buf));
		ret=fread(buf,1,sizeof(buf),fq1);
			if(ret<=0)
				return -1;
		fwrite(buf,1,ret,fq2);

		fseek(fq1,50*640,SEEK_CUR);
		fseek(fq2,50*640,SEEK_CUR);

	}
		
	
	fclose(fq1);
	fclose(fq2);
}
