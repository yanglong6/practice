#include <stdio.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <fcntl.h>
#include <pthread.h>
#include <sqlite3.h>

typedef struct {
	char name[32];
	char passwd[32];
	int connfd;
}MSG;

typedef struct node{
	MSG msg;
	int connfd;
	struct node *next;
}online_link;

typedef struct groupfd{
	int selffd;
	int otherfd;
}ropfd;

typedef struct {                                                                                   
	char name[32];
	int connfd;
}userinfo;

typedef struct {
	userinfo user[32];
	int num; 
}ugroup;

ugroup *userdb;


int do_login(MSG *msg,int connfd);
int do_register(MSG *msg,int connfd);
int list_online_client(online_link *head,int connfd);
int do_chat(MSG *msg,online_link *head,int connfd);
online_link *create_link();
int insert_link(MSG *mg,online_link *head,int *connfd);
int delect(online_link *head,int connfd);
void *fun1(void *arg);

void *client_handler(void *argv);
int TcpInit(char *ip,short port);


online_link *head;

int main(void)
{
	//创建链表 保存在线用户信息
	head=create_link();
	if(head==NULL)
		return -1; 

	struct sockaddr_in cliaddr;
	int len = sizeof(cliaddr);
	int ret;
	int connfd;
	char buf[128];
	MSG recvmsg;
	int sockfd = TcpInit("192.168.0.104",6666);

	while(1)
	{
		//建立tcp链接
		connfd = accept(sockfd, (struct sockaddr *)&cliaddr, &len);
		printf("connect a client ip:%s,prot:%u\n",inet_ntoa(cliaddr.sin_addr),ntohs(cliaddr.sin_port));

		//来一个链接  创建一个线程为客户服务              
		pthread_t pid ;
		ret = pthread_create(&pid,NULL,client_handler, (void *)connfd );
		if(ret!=0){
			perror("pthread_create");
			exit(-1);
		}
		pthread_detach(pid);

	}
	close(sockfd);
	return 0;
}

//chat1
void *fun1(void *arg)
{
	int ret;
	char lv[]={"oppsite leave connect"};
	ropfd *fd=(ropfd *)arg;
	char date[256];
	while(1)
	{
		memset(date,0,sizeof(date));
		printf("input:\n");
		ret=recv(fd->selffd,date,sizeof(date),0);
		if(ret==-1)
		{
			perror("recv talk");
			return ;
		}
		else if(ret==0)
		{
			printf("clian quit\n");
			send(fd->otherfd,lv,sizeof(lv),0);
			close(fd->selffd);
			pthread_detach(pthread_self());
			pthread_exit((void *)fd->selffd);
		}
		printf("len=%d,%s\n",ret,date);
		ret=send(fd->otherfd,date,ret,0);
		if(ret==-1)
		{
			perror("send");
			return ;
		}
	}

}

//线程函数 处理客户端的请求与响应
void *client_handler(void *argv)
{
	int ret;
	char buf[32];
	MSG recvmsg;
	int connfd = (int )argv;

	while(1)
	{
		//1.读客户端的 请求
		memset(buf,0,sizeof(buf));
		bzero(&recvmsg,sizeof(recvmsg));
		printf("chose:1 2 3 4\n");
		ret=recv(connfd,buf,sizeof(buf),0);
		if(ret<=0){
			delect(head,connfd);
			printf("client quit\n"); 
			break;
		}
		//2.根据请求 给响应
		switch(buf[0])
		{
			case '1'     : do_register(&recvmsg,connfd);       break;  //注册 
			case '2'     : do_login(&recvmsg,connfd);          break;  //登录
			case '3'     : list_online_client(head,connfd);           break;  //列出在线用户
			case '4'     : do_chat(&recvmsg,head,connfd);      break;         //聊天模式
			default: printf("error  input\n");           break;
		}
	}
	close(connfd);
	pthread_exit(0); 
}

//列出在线用户
int list_online_client(online_link *head,int connfd)
{
	//1.遍历链表
	//2.发送在线用户名字
	char buf[]={"end"};
	online_link *q=head->next;
	if(q==NULL)
	{
		send(connfd,"$",sizeof(MSG),0);
		return -1;
	}
	else
	{
		while(q!=NULL)
		{
			printf("%s\n",q->msg.name);
			send(connfd,q->msg.name,sizeof(MSG),0);
			q=q->next;
		}
		usleep(10);
		send(connfd,buf,sizeof(MSG),0);
	}
	return 0;
}

//建立空链表
online_link *create_link()
{
	online_link *head=(online_link *)malloc(sizeof(online_link));
	if(head==NULL)
		return NULL;
	memset(head->msg.name,0,sizeof(head->msg.name));
	memset(head->msg.passwd,0,sizeof(head->msg.passwd));
	head->connfd=-1;
	head->next=NULL;
	return head;
}
//节点插入
int insert_link(MSG *mg,online_link *head,int *connfd)
{
	online_link *q=head;
	if(q==NULL)
		return -1;
	online_link *new=(online_link *)malloc(sizeof(online_link));
	new->connfd=0;
	new->next=NULL;
	memset(new->msg.name,0,sizeof(new->msg.name));
	memset(new->msg.passwd,0,sizeof(new->msg.passwd));

	new->connfd=*connfd;
	strcpy(new->msg.name,mg->name);
	strcpy(new->msg.passwd,mg->passwd);
	new->next=q->next;
	q->next=new;

	return 0;
}
//节点的删除
int delect(online_link *head,int connfd)
{
	online_link *q=head->next;
	online_link *p=head;
	while(q->connfd!=connfd)
		q=q->next;
	while(p->next!=q)
		p=p->next;
	p->next=q->next;
	free(q);
	q=NULL;
	return 0;
}


//进入聊天功能
int do_chat(MSG *msg,online_link *head,int connfd)
{
	//查看对方是否在线
	//开启聊天模式 
	if(head==NULL)
		return -1;
	online_link *q=head->next;
	char buf[32];
	char date[128];
	int ret;
	ropfd *fd=(ropfd *)malloc(sizeof(ropfd));
	printf("put chat with usr\n");
	memset(buf,0,sizeof(buf));
	ret=recv(connfd,buf,sizeof(buf),0);
	if(ret<-1)
	{
		perror("recv");
		return -1;
	}

	while(q)
	{
		if(strcmp(q->msg.name,buf)==0)
			break;
		else
			q=q->next;
	}

	if(q==NULL)
	{
		printf("%s no online\n",buf);
		snprintf(date,128,"%s no online",buf);
		send(connfd,date,sizeof(date),0);
		return -1;
	}

	printf("%s online\n",buf);
	snprintf(date,128,"%s online",buf);
	send(connfd,date,sizeof(date),0);
	fd->selffd=connfd;
	fd->otherfd=q->connfd;

	pthread_t pthread1;
	ret=pthread_create(&pthread1,NULL,fun1,(void *)fd);
	while(1);
	return 0;
}

//注册
int do_register(MSG *msg,int connfd)
{
	//获取用户名与密码
	//写入数据库中
	int ret;
	sqlite3 *db;
	char date[128];
	char sql[128]={0};
	char *erromsg;

	ret=sqlite3_open("my.db",&db);
	if(ret!=0)
	{
		printf("open my.db fail\n");
		return -1;
	}
	recv(connfd,msg,sizeof(MSG),0);
	printf("name:%s\n",msg->name);
	printf("passwd:%s\n",msg->passwd);

	snprintf(sql,128,"insert into usr values('%s','%s')",msg->name,msg->passwd);
	ret=sqlite3_exec(db,sql,NULL,NULL,&erromsg);
	if(ret!=0)
	{
		printf("select failed :%s\n",erromsg);
		snprintf(date,128,"register fail");
		send(connfd,date,sizeof(date),0);
		return -1;
	}
	printf("register success\n");
	snprintf(date,128,"register success");
	send(connfd,date,sizeof(date),0);
	sqlite3_close(db);
}

int do_login(MSG *msg,int connfd)
{
	//查询数据库 
	//登录成功 将用户信息加入在线用户表
	int ret;
	sqlite3 *db;
	char **resultp;
	int nrow;
	int ncolumn;
	char sql[128]={0};
	char date[128];
	char *erromsg;

	ret=sqlite3_open("my.db",&db);
	if(ret!=0)
	{
		printf("open my.db fail\n");
		return -1;
	} 

	recv(connfd,msg,sizeof(MSG),0);
	printf("name:%s %d\n",msg->name,strlen(msg->name));
	printf("passwd:%s %d\n",msg->passwd,strlen(msg->passwd));

	snprintf(sql,128,"select * from usr where name='%s' and password='%s'",msg->name,msg->passwd);
	ret=sqlite3_get_table(db,sql,&resultp,&nrow,&ncolumn,&erromsg);
	printf("ret=%d\n",ret);
	if(nrow==0)
	{
		printf("no exit user\n");
		snprintf(date,128,"no exit user");
		send(connfd,date,sizeof(date),0);
		return -1;
	}
	printf("login succese\n");
	snprintf(date,128,"login succese");
	send(connfd,date,sizeof(date),0);
	printf("connfd=%d\n",connfd);
	insert_link(msg,head,&connfd);
	sqlite3_close(db);
	return 0;

}

int TcpInit(char *ip,short port)
{
	int ret;
	int sockfd = socket(PF_INET, SOCK_STREAM,0); //创建tcp通信

	/* 构建一张卡  */
	struct sockaddr_in addr;
	addr.sin_family = PF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = inet_addr(ip);

	ret = bind(sockfd, (struct sockaddr *)&addr, sizeof(addr));//绑定地址信息
	if(ret==-1){
		perror("bind");
		exit(-1);
	}

	listen(sockfd,32); //建立监听队列
	return sockfd;
}

