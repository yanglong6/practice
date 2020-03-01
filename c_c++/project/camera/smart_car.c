#include<stdio.h>
#include<termios.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
//#include"convert.h"
#include"V4L2.h"

int uart_set(int fd,int baude,int c_flow,int bits,char parity,int stop);
int tcpserve_init(int servefd);
int car_run(int fd,char *buf,char *ll);
void *camera_hander(void *argv);

int main()
{
	unsigned char ll[]={0xff,0x00,0x00,0x00,0xff};
	int servefd,connfd,ret,fd;
	pthread_t pid;
	char buf[32]={0};

	servefd=tcpserve_init(servefd);
	while(1)
	{
		connfd=accept(servefd,NULL,NULL);
		if(connfd==-1)
		{
			perror("accept fail");
			return -1;
		}
		printf("%d connect success\n",connfd);
		fd=open("/dev/ttyATH0",O_RDWR|O_NOCTTY| O_NONBLOCK);
		if(fd==-1)
			return -1;
		uart_set(fd,9600,0,8,'N',1);
		pthread_create(&pid,NULL,camera_hander,(void *)connfd);
		if(ret!=0)
		{
			perror("pthcreat\n");
			return -1;
		}

		while(1)
		{
			memset(buf,0,sizeof(buf));
			ret=recv(connfd,buf,sizeof(buf),0);
			//printf("%s\n",buf);
			if(ret==-1)
			{
				close(fd);
				close(connfd);
				break;
			}
			else if(ret==0)
			{
				printf("recv 0");
				close(fd);
				close(connfd);
				return 0;
			}
			else
			{
				car_run(fd,buf,ll);
			}
		}
	}
	return 0;
}
void *camera_hander(void *argv)//摄像头处理函数
{
	int connfd=(int)argv;
	int ret;
	int camfd=camera_init();
	//rgb=malloc(width*height*3);
	//videoJpegs=malloc(sizeof(*videoJpegs));

	camera_start(camfd);
	while(1)
	{
		//send_pic(camfd);
		//printf("%d\n",videoJpegs->length);
		//ret=send(connfd,videoJpegs->jpg,videoJpegs->length,0);
		struct v4l2_buffer buf;
		memset(&buf, 0, sizeof(buf));
		buf.type		=V4L2_BUF_TYPE_VIDEO_CAPTURE;
		buf.memory		=V4L2_MEMORY_MMAP;
		ioctl(camfd,VIDIOC_DQBUF,&buf);//取缓冲帧
		ioctl(camfd,VIDIOC_QBUF,&buf);
		printf("ready read............\n%d\n",buf.length);      
#if 0
		FILE *fd=fopen("1.jpg","wb");
		if(NULL == fd)
		{

			perror("fopen");
			return;
		}
		fwrite(videoBufs[buf.index].start,buf.length,1,fd);
		fclose(fd);	
#endif
	}
	camera_stop(camfd);
	close(camfd);
	return 0;
}

int car_run(int fd,char *buf,char *yy)//小车控制
{
	if(buf==NULL)
		return -1;
	if(strcmp(buf,"stop")==0)
	{
		yy[1]=0x00;
		yy[2]=0x00;
		yy[3]=0x00;
		write(fd,yy,5);	
	}
	if(strcmp(buf,"up")==0)
	{
		yy[1]=0x00;
		yy[2]=0x01;
		yy[3]=0x00;
		write(fd,yy,5);	
	}
	if(strcmp(buf,"down")==0)
	{
		yy[1]=0x00;
		yy[2]=0x02;
		yy[3]=0x00;
		write(fd,yy,5);	
	}
	if(strcmp(buf,"left")==0)
	{
		yy[1]=0x00;
		yy[2]=0x03;
		yy[3]=0x00;
		write(fd,yy,5);	
	}
	if(strcmp(buf,"right")==0)
	{
		yy[1]=0x00;
		yy[2]=0x04;
		yy[3]=0x00;
		write(fd,yy,5);	
	}
	if(strcmp(buf,"right_up")==0)
	{
		yy[1]=0x00;
		yy[2]=0x07;
		yy[3]=0x00;
		write(fd,yy,5);	
	}
	if(strcmp(buf,"right_down")==0)
	{
		yy[1]=0x00;
		yy[2]=0x08;
		yy[3]=0x00;
		write(fd,yy,5);	
	}
	if(strcmp(buf,"left_up")==0)
	{
		yy[1]=0x00;
		yy[2]=0x05;
		yy[3]=0x00;
		write(fd,yy,5);	
	}
	if(strcmp(buf,"left_down")==0)
	{
		yy[1]=0x00;
		yy[2]=0x06;
		yy[3]=0x00;
		write(fd,yy,5);	
	}
	/*
	   if(strncmp(buf,"2",1)==0)//变速
	   {	
	   yy[1]=0x00;
	   yy[2]=0x01;
	   yy[3]=0x00;
	   write(fd,yy,5);

	   yy[1]=0x02;
	   yy[2]=0x01;
	   yy[3]=buf[1];
	   write(fd,yy,5);
	//yy[2]=0x02;
	//write(fd,yy,5);

	}
	*/
	return 0;

}

int tcpserve_init(int servefd)
{
	int ret;
	servefd=socket(AF_INET,SOCK_STREAM,0);
	if(servefd==-1)
	{
		perror("sockt fail");
		return -1;
	}

	struct sockaddr_in servaddr;
	servaddr.sin_port=htons(6666);
	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=inet_addr("192.168.1.1");

	ret=bind(servefd,(struct sockaddr *)&servaddr,sizeof(servaddr));
	if(ret==-1)
	{
		perror("bind fail");
		return -1;
	}
	ret=listen(servefd,5);
	if(ret==-1)
	{

		perror("listen");
		return -1;
	}
	return servefd;
}

int uart_set(int fd,int baude,int c_flow,int bits,char parity,int stop)//串口初始化
{
	struct termios options;
	/*获取终端属性*/
	if(tcgetattr(fd,&options) < 0)
	{

		perror("tcgetattr error");
		return -1;
	}

	/*设置输入输出波特率，两者保持一致*/
	switch(baude)
	{
		case 4800:
			cfsetispeed(&options,B4800);
			cfsetospeed(&options,B4800);
			break;
		case 9600:
			cfsetispeed(&options,B9600);
			cfsetospeed(&options,B9600);
			break;
		case 19200:
			cfsetispeed(&options,B19200);
			cfsetospeed(&options,B19200);
			break;
		case 38400:
			cfsetispeed(&options,B38400);
			cfsetospeed(&options,B38400);
			break;
		default:
			fprintf(stderr,"Unkown baude!\n");
			return -1;
	}

	/*设置控制模式*/
	options.c_cflag |= CLOCAL;//保证程序不占用串口
	options.c_cflag |= CREAD;//保证程序可以从串口中读取数据

	/*设置数据流控制*/
	switch(c_flow)
	{
		case 0://不进行流控制
			options.c_cflag &= ~CRTSCTS;
			break;
		case 1://进行硬件流控制
			options.c_cflag |= CRTSCTS;
			break;
		case 2://进行软件流控制
			options.c_cflag |= IXON|IXOFF|IXANY;
			break;
		default:
			fprintf(stderr,"Unkown c_flow!\n");
			return -1;
	}

	/*设置数据位*/
	switch(bits)
	{
		case 5:
			options.c_cflag &= ~CSIZE;//屏蔽其它标志位
			options.c_cflag |= CS5;
			break;
		case 6:
			options.c_cflag &= ~CSIZE;//屏蔽其它标志位
			options.c_cflag |= CS6;
			break;
		case 7:
			options.c_cflag &= ~CSIZE;//屏蔽其它标志位
			options.c_cflag |= CS7;
			break;
		case 8:
			options.c_cflag &= ~CSIZE;//屏蔽其它标志位
			options.c_cflag |= CS8;
			break;
		default:
			fprintf(stderr,"Unkown bits!\n");
			return -1;
	}

	/*设置校验位*/
	switch(parity)
	{
		/*无奇偶校验位*/
		case 'n':
		case 'N':
			options.c_cflag &= ~PARENB;//PARENB：产生奇偶位，执行奇偶校验
			options.c_cflag &= ~INPCK;//INPCK：使奇偶校验起作用
			break;
			/*设为空格,即停止位为2位*/
		case 's':
		case 'S':
			options.c_cflag &= ~PARENB;//PARENB：产生奇偶位，执行奇偶校验
			options.c_cflag &= ~CSTOPB;//CSTOPB：使用两位停止位
			break;
			/*设置奇校验*/
		case 'o':
		case 'O':
			options.c_cflag |= PARENB;//PARENB：产生奇偶位，执行奇偶校验
			options.c_cflag |= PARODD;//PARODD：若设置则为奇校验,否则为偶校验
			options.c_cflag |= INPCK;//INPCK：使奇偶校验起作用
			options.c_cflag |= ISTRIP;//ISTRIP：若设置则有效输入数字被剥离7个字节，否则保留全部8位
			break;
			/*设置偶校验*/
		case 'e':
		case 'E':
			options.c_cflag |= PARENB;//PARENB：产生奇偶位，执行奇偶校验
			options.c_cflag &= ~PARODD;//PARODD：若设置则为奇校验,否则为偶校验
			options.c_cflag |= INPCK;//INPCK：使奇偶校验起作用
			options.c_cflag |= ISTRIP;//ISTRIP：若设置则有效输入数字被剥离7个字节，否则保留全部8位
			break;
		default:
			fprintf(stderr,"Unkown parity!\n");
			return -1;
	}

	/*设置停止位*/
	switch(stop)
	{
		case 1:
			options.c_cflag &= ~CSTOPB;//CSTOPB：使用两位停止位
			break;
		case 2:
			options.c_cflag |= CSTOPB;//CSTOPB：使用两位停止位
			break;
		default:
			fprintf(stderr,"Unkown stop!\n");
			return -1;
	}

	/*设置输出模式为原始输出*/
	options.c_oflag &= ~OPOST;//OPOST：若设置则按定义的输出处理，否则所有c_oflag失效

	/*设置本地模式为原始模式*/
	options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
	/*
	 *      *ICANON：允许规范模式进行输入处理
	 *           *ECHO：允许输入字符的本地回显
	 *                *ECHOE：在接收EPASE时执行Backspace,Space,Backspace组合
	 *                     *ISIG：允许信号
	 *                          */

	/*设置等待时间和最小接受字符*/
	options.c_cc[VTIME] = 0;//可以在select中设置
	options.c_cc[VMIN] = 1;//最少读取一个字符

	/*如果发生数据溢出，只接受数据，但是不进行读操作*/
	tcflush(fd,TCIFLUSH);

	/*激活配置*/
	if(tcsetattr(fd,TCSANOW,&options) < 0)
	{

		//	perror("111tcsetattr failed");
		return -1;
	}
	return 0;
}
