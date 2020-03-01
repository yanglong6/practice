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
			sem_wait(semid);
			printf("chlden\n");
		}
		exit(0);
	}
	while(1)
	{
		sem_pose(semid);
		sleep(1);
		printf("father\n");
	}
	exit(0);
	return 0;
}
