#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
	int shmid;
	char *shmadrr;
	char buf[64];
	pid_t pid;
	key_t key;
	key=ftok(".",'a');
	if(key==-1)
	{
		perror("ftok");
		return -1;
	}

	//创建内存
	shmid=shmget(key,128,IPC_CREAT|0664);
	if(shmid==-1)
	{
		perror("shmid");
		return -1;
	}
	printf("shmid=%d\n",shmid);
	
	system("ipcs -m");
	//创建进程
	pid=fork();
	if(pid==-1)
	{
		perror("fork");
		return -1;
	}
	else if(fork==0)
	{
		shmadrr=(char *)shmat(shmid,NULL,0);
		if(shmadrr==NULL)
		{
			perror("shmat");
			return -1;
		}
		while(1)
		{
			fgets(buf,sizeof(buf),stdin);
			memcpy(shmadrr,buf,64);
		}

	system("ipcs -m");
		exit(0);
	}
	return 0;
}
