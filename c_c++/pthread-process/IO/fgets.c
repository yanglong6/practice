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
	//	fprintf(stdout,"open seccess");
	
	
	while(fgets(buf,32,fq)!=NULL)
	{
		if(buf[strlen(buf)-1]=='\n')
			line++;
	}
	printf("line=%d\n",line);
	fclose(fq);
	return 0;
}
