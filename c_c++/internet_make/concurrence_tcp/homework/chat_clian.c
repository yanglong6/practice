#include<stdio.h>
#include<string.h>
#include<sys/types.h>          
#include<sys/socket.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<time.h>
#include<fcntl.h>
#include<pthread.h>
typedef struct {
	char name[32];
	char passwd[32];
	int connfd;
}MSG;

void *send_msg(void *arg);
void *recv_msg(void *arg);

int do_register(char *buf,int sendfd);
int do_login(char *buf,int sendfd);
int list_online(char *buf,int sendfd);
int chat(char *buf,int sendfd);

int main(int argc,char *argv[])
{
	int sendfd;
	char buf[32];

	if(argc!=3)
	{
		printf("%s <id> <port>\n",argv[0]);
		return -1;
	}
	//建立socket
	sendfd=socket(AF_INET,SOCK_STREAM,0);
	if(sendfd==-1)
	{
		perror("socket");
		return -1;
	}

	struct sockaddr_in sendaddr;

	sendaddr.sin_port=htons(atoi(argv[2]));
	sendaddr.sin_family=AF_INET;
	sendaddr.sin_addr.s_addr=inet_addr(argv[1]);
	int ret=connect(sendfd,(struct sockaddr *)&sendaddr,sizeof(sendaddr));
	if(ret==-1)
	{
		while(1);
		perror("connect");
		return -1;
	}
	while(1)
	{
loop:		printf("chose:1.注册 2.登录 3.查看在线用户 4.聊天模式\n");
		gets(buf);
		if(buf[0]=='1')
		{
			do_register(buf,sendfd);
		}
		else if(buf[0]=='2')
		{
			do_login(buf,sendfd);
		}
		else if(buf[0]=='3')
		{
			list_online(buf,sendfd);
		}
		else if(buf[0]=='4')
		{
			chat(buf,sendfd);
		}
		else
		{
			printf("put error,put agin\n");
			goto loop;
		}
	}
	close(sendfd);
	return 0;
}

int do_register(char *buf,int sendfd)
{
	int ret;
	char date[128];
	send(sendfd,buf,sizeof(buf),0);
	MSG sendmsg;

	printf("name\n");
	gets(sendmsg.name);
	printf("passwd\n");
	gets(sendmsg.passwd);
	sendmsg.connfd=sendfd;

	send(sendfd,&sendmsg,sizeof(sendmsg),0);
	recv(sendfd,date,sizeof(date),0);
	printf("%s\n",date);
	return 0;
}
//登录
int do_login(char *buf,int sendfd)
{
	int ret;
	char date[128];
	send(sendfd,buf,sizeof(buf),0);
	MSG sendmsg;

	printf("name\n");
	gets(sendmsg.name);
	printf("passwd\n");
	gets(sendmsg.passwd);
	sendmsg.connfd=sendfd;

	send(sendfd,&sendmsg,sizeof(sendmsg),0);
	recv(sendfd,date,sizeof(date),0);
	printf("%s\n",date);
	return 0;
}

int list_online(char *buf,int sendfd)
{
	int ret;
	MSG listmsg;
	send(sendfd,buf,sizeof(buf),0);
	while(1)
	{
		ret=recv(sendfd,listmsg.name,sizeof(MSG),0);
		if(strcmp(listmsg.name,"$")==0)
		{
			printf("no user online\n");
			return -1;
		}
		if(strcmp(listmsg.name,"end")==0)
			break;
		printf("%s\n",listmsg.name);
	}
	return 0;
}

int chat(char *buf,int sendfd)
{
	int ret;
	char *q;
	char usr[32];
	char cmp[128];
	char date[128];
	send(sendfd,buf,sizeof(buf),0);
	printf("put chat with usr\n");
	gets(usr);
	send(sendfd,usr,sizeof(usr),0);
	recv(sendfd,date,sizeof(date),0);
	snprintf(cmp,128,"%s no online",usr);
	printf("%s\n",date);
	if(strcmp(date,cmp)==0)
		return -1;

	pthread_t pthread1,pthread2;
	pthread_create(&pthread1,NULL,send_msg,(void *)sendfd);
	pthread_create(&pthread2,NULL,recv_msg,(void *)sendfd);
	pthread_join(pthread1,(void **)&q);
	if(strcmp(q,"exit")==0)
		return -1;
	while(1);
}

void *send_msg(void *arg)
{
	int ret;
	char buf[64];
	char *q=malloc(32);
	q="exit";
	int sendfd=(int)arg;
	while(1)
	{
		//	printf("put:\n");
		memset(buf,0,sizeof(buf));
		gets(buf);
		if(strcmp(buf,"exit")==0)
			pthread_exit((void *)q);
		ret=send(sendfd,buf,strlen(buf),0);
		if(ret==-1)
		{
			perror("send");
			return NULL;
		}
	}
	return NULL;
}

void *recv_msg(void *arg)
{
	int ret;
	int flag;
	char buf[64];
	int sendfd=(int)arg;
	while(1)
	{
		memset(buf,0,sizeof(buf));
		ret=recv(sendfd,buf,sizeof(buf),0);
		if(ret==-1)
		{
			perror("recv");
			return ;
		}
		if(ret>0)
			printf("recv:%s\n",buf);
		if(ret==0)
			break;
	}
	return NULL;
}

