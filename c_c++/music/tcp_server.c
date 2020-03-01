#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>

#define SIZE sizeof(stu)


typedef struct node{
	 char name[128];
	 struct node *prev;
	 struct node *next;
}stu,*pstu;


void autofile()//自动生成音乐目录集
{
	
    system("cp ~/18081/bishe/music  ~/18081/bishe/songname");   	
}


pstu LoadInfo()//加载数据
{
	char name[128];
	char filename[]="../songname";
	FILE *fp;
	pstu head,ptr,tmp;
	
	//创建头文件
	head=calloc(1,SIZE);
	ptr=head;
	ptr->next=NULL;
	if((fp=fopen(filename,"r"))==NULL)
	{
		perror("fopen");
		exit(0);
	}
	tmp=(pstu)calloc(1,SIZE);
	
	while(fscanf(fp,"%s\n",name)!=EOF)
	{	
		strcpy(tmp->name, name);	
		ptr->next=tmp;
		tmp->prev=ptr;
		ptr = tmp;
		tmp = (pstu)calloc(1,SIZE);	
	}
        free(tmp);
	fclose(fp);  //关闭文件,已得到保存data信息的链表head
	return head;
}

pstu Find_DownNode(pstu head)
{
	pstu p;
	p=head->next;
	return p;
}
pstu Find_UpNode(pstu head)
{
	pstu p;
	p=head->prev;
	
	return p;
}
void print_Node(pstu head,int connfd)
{
	pstu ptr=head;
	pstu p=ptr->next;
    char buf[512] = {0};
	printf("\t\t\t\t\t\t 歌   单\n\n");
	while(p!=NULL)
	{  
        strcat(buf,p->name);
        strcat(buf,"\n\0");      
        p=p->next;
    }
    buf[strlen(buf)-1] = '\0';
    puts(buf);
    int a=write(connfd,buf,strlen(buf)+2);
    memset(buf,0,strlen(buf));

}

void *foo(void *arg)//云服务
{

	//线程函数，服务一个客户
	int connfd=(int)arg; //通强转，得到套接字描述符
	pthread_detach(pthread_self()); //和主线程分离，避免让主线程来收尸
	char buf1[4096];
	int n;

        int choose=0;
        pid_t pid;
        int flag=0; //0 停止 1 播放 2 暂停
        char pathname[]="../music/";
        char buf[50]={0};
        autofile();
        pstu head,pstr,p;
        head=LoadInfo();  
        head->prev;
        pstr=head->next;
        pstr->prev=head;
        print_Node(head,connfd);

	while(1)//循环接收来自客户端的信息
	{
		n=read(connfd,buf1,sizeof(buf1));
		if(n==0)
			break;
		buf1[n]='\0';
		printf("buf1=%s\n",buf1);
        
    if(buf1[0]=='$')
    {
        switch(buf1[0])
        {
            case 'A':
                {
                    break;
                }
            case 'B':
                {
                    break;
                }
            case 'C':
                {
                    break;
                }
            case 'D':
                {
                    break;
                }    
        }
    }
    else if(buf[0]=='#')
    {
        
    }
  }
}

int main()
{
	int listenfd,connfd;
	listenfd=socket(AF_INET,SOCK_STREAM,0); //创建套接字
    int on=1;
    setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));


	struct sockaddr_in servaddr; //定义一个结构体变量，来代表地址信息
	bzero(&servaddr,sizeof(servaddr)); //将结构体变量清0
	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(6687); //htons从主机字节序，转为网络字节序
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY); //指任意的IP地址
	if(bind(listenfd,(struct sockaddr*)&servaddr,sizeof(servaddr))<0) //给套接字绑定地址信息
	{
		perror("bind");
		exit(EXIT_FAILURE);
	}
	listen(listenfd,20); //给监听套接字，创建一个监听队列
    printf("listen......\n");
	while(1)
	{
		printf("server waiting...\n");
		connfd=accept(listenfd,NULL,NULL); //从监听队列中取出一个连接请求，如果队列为空会阻塞
        printf("acceptghsdkhjs\n");
		pthread_t tid;
		pthread_create(&tid,NULL,foo,(void*)connfd);
	}
	close(listenfd);
	exit(EXIT_SUCCESS);
}



