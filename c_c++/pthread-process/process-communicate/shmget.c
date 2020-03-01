
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
	int shmid;
	int ret;
	char buf[128];
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

	shmid=shmget(0,128,IPC_CREAT|0664);
	if(shmid==-1)
	{
		perror("shmid");
		return -1;
	}
	printf("shmid=%d\n",shmid);
	
	//地址映射
	char *shmadrr=(char *)shmat(shmid,NULL,0);
	if(shmadrr==(char *)-1)
	{
		perror("shmat");
		return -1;
	}

	//创建新进程
	pid_t pid=fork();
	if(pid==-1)
	{
		perror("fork");
		return -1;
	}
	else if(pid==0)
	{
		
		
		gets(buf);
		memcpy(shmadrr,buf,sizeof(buf));
		exit(0);
	
	}

//	while(1)
//	{
		memcpy(buf,shmadrr,sizeof(buf));
		sleep(2);
		printf("buf:%s\n",buf);
//	}
//撤销共享内存
	ret=shmdt(shmadrr);
	if(ret==-1)
	{
		perror("shmdt");
		return -1;
	}

//删除共享空间地址
	ret=shmctl(shmid,IPC_RMID,NULL);
	if(ret==-1)
	{
		perror("shmctl");
		return -1;
	}
	exit(0);
	return 0;
}
