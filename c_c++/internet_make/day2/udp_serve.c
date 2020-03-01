#include<stdio.h>
#include<string.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h> /* superset of previous */

int main()
{
	int sockfd;
	int ret;
	char buf[128];
	int clilen;
	sockfd=socket(AF_INET,SOCK_DGRAM,0);
	if(sockfd==-1)
	{
		perror("socket");
		return -1;
	}
	
	struct sockaddr_in servaddr,cliaddr;

	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(1234);
	servaddr.sin_addr.s_addr=inet_addr("0");

	ret=bind(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
	if(ret==-1)
	{
		perror("bind");
		return -1;
	}
	clilen=sizeof(cliaddr);
	while(1)
	{
		memset(buf,0,sizeof(buf));
	ret=recvfrom(sockfd,buf,sizeof(buf),0,(struct sockaddr *)&cliaddr,&clilen);
		if(ret==-1)
		{
			perror("recvfrom");
			return -1;
		}
		printf("recv:%s len:%d  id:%s  port:%d\n",buf,strlen(buf),inet_ntoa(cliaddr.sin_addr),ntohs(cliaddr.sin_port));
		int i;
		for(i=0;i<ret;i++)
		{
			if(('a'<buf[i])&&(buf[i]<'z'))
			buf[i]=toupper(buf[i]);
		}

		ret=sendto(sockfd,buf,strlen(buf),0,(struct sockaddr *)&cliaddr,sizeof(cliaddr));
		if(ret==-1)
		{
			perror("sendto");
				return -1;
		}
	}
	close(sockfd);
	return 0;
	
}
