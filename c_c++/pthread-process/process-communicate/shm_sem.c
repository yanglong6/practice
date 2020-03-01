#include<stdio.h>
#include<string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

union semun {
	int              val;    /* Value for SETVAL */
	struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
	unsigned short  *array;  /* Array for GETALL, SETALL */
	struct seminfo  *__buf;  /* Buffer for IPC_INFO
				    (Linux-specific) */
};

//信号量的初始化
int init_sem(void)
{
	key_t key;
	int semid,ret;
	union semun sem;
	key=ftok(".",'a');
	if(key==-1)
	{
		perror("ftok");
		return -1;
	}

	semid=semget(key,1,IPC_CREAT|0664);
	if(semid==-1)
	{
		perror("semget");
		return -1;
	}
	sem.val=0;
	ret=semctl(semid,0,SETVAL,sem);
	if(ret==-1)
	{
		perror("semctl");
		return -1;
	}
	return semid;

}
//P操作
int sem_wait(int semid)
{
	int ret;
	struct sembuf sem_p;
	sem_p.sem_num=0;
	sem_p.sem_op=-1;
	sem_p.sem_flg=0;
	ret=semop(semid,&sem_p,1);
	if(ret==-1)
	{
		perror("senop");
		return -1;
	}
	return 0;
}

//V操作
int sem_pose(int semid)
{
	int ret;
	struct sembuf sem_v;
	sem_v.sem_num=0;
	sem_v.sem_op=1;
	sem_v.sem_flg=0;
	ret=semop(semid,&sem_v,1);
	if(ret==-1)
	{
		perror("senop");
		return -1;
	}
	return 0;
}

//删除信号量
int delet_sem(int semid)
{
	int ret;
	union semun sem_union;
	ret=semctl(semid,0,IPC_RMID,sem_union);
	if(ret==-1)
	{
		perror("senop");
		return -1;
	}
	return 0;
}
int main()
{
	pid_t pid;
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

	//地址映射
	char *shmadrr=(char *)shmat(shmid,NULL,0);
	if(shmadrr==(char *)-1)
	{
		perror("shmat");
		return -1;
	}

	int semid=init_sem(); 	
	if(semid==-1)
		exit(1);

	pid=fork();
	if(pid==-1)
	{
		perror("pid");
		return -1;
	}
	else if(pid==0)
	{
		while(1)
		{
			gets(buf);
			memcpy(shmadrr,buf,32);
			sem_pose(semid);

		}
		exit(0);
	}
	while(1)
	{
		sem_wait(semid);
//		sleep(1);
		memcpy(buf,shmadrr,32);
		printf("buf:%s\n",buf);
	}
	exit(0);
	return 0;
}
