
#include<stdio.h>
#include<string.h>
int main(int argc,char *argv[])
{
	int c=0;
	if(argc!=2)
		fprintf(stdout,"user:%s filename\n",argv[0]);
	FILE *fq=fopen(argv[1],"r+");
	if(fq==NULL)
	{
		perror("fopen");
		return -1;
	}
	//	fprintf(stdout,"open seccess");
	while(1)
	{
		c=fgetc(fq);
		if(EOF==c)
		{
			if(feof(fq))
			{
				fclose(fq);
				return -1;
			}
			if(ferror(fq))
				break;
		}
		c=fputc(c,stdout);
		if(c==EOF)
		{
			fclose(fq);
			return -1;
		}
	}
	fclose(fq);
	return 0;
}
