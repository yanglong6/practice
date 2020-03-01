#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>

int main(int argc,char *argv[])
{
	char buf[64];
	time_t t;
	if(argc<2)
	{
		fprintf(stdout,"usege: %s <file>\n",argv[0]);
		return -1;
	}
	FILE *fq=fopen(argv[1],"a+");
	if(fq==NULL)
	{
		perror("fopen");
		return -1;
	}
	while(1)
	{
		time(&t);
		fprintf(fq,"%s",ctime(&t));
		sleep(1);
	}
	fclose(fq);

		return 0;

}
