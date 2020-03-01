#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct msgbuf {
	long mtype;       /* message type, must be > 0 */
	char mtext[128];    /* message data */
};

int main()
{
	int msgid;
	key_t key;
	int ret;
	int type;
	char buf[128];
	struct msgbuf msg;

	key=ftok(".",'a');
	if(key==-1)
	{
		perror("ftok");
		return -1;
	}
	//创建消息队列
	msgid=msgget(key,IPC_CREAT|0664);
	if(msgid==-1)
	{
		perror("msgget");
		return -1;
	}
	//添加消息
	while(1)
	{
		ret=msgrcv(msgid,&msg,sizeof(msg),0,0);
		if(ret==-1)
		{
			perror("msgrcv");
			return -1;
		}
		printf("msg:%d %s\n",msg.mtype,msg.mtext);
	}
	//控制消息队列：删除
	ret=msgctl(msgid,IPC_RMID,NULL);
	if(ret==-1)
	{
		perror("msgctl");
		return -1;
	}
	exit(0);
	return 0;
}
