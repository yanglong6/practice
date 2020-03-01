#include "V4L2.h"
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include<termios.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

int uart_set(int fd,int baude,int c_flow,int bits,char parity,int stop);
int tcpserve_init(int servefd);
int car_run(int fd,char *buf,char *ll);

int main()
{
	pid_t pid;
	pid=fork();
	if(pid==-1)
	{
		perror("fork error");
		return -1;
	}
	else if(pid==0)
	{
	unsigned char ll[]={0xff,0x00,0x00,0x00,0xff};
	int servefd,connfd,ret,fd;
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

		while(1)
		{
			memset(buf,0,sizeof(buf));
			ret=recv(connfd,buf,sizeof(buf),0);
			printf("%s\n",buf);
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
				break;
			}
			else
			{
				car_run(fd,buf,ll);
			}
		}
	}
	}
	else
	{
		int camfd = camera_init();
     	int socket=server_init();
        camera_start(camfd);
		struct v4l2_buffer buf;
		struct sockaddr_in c_addr;
		char flag;

	while(1)
	{
		memset(&c_addr,0,sizeof(c_addr));
		socklen_t c_len=sizeof(c_addr);
		int rws=accept(socket,(struct sockaddr *)&c_addr,&c_len);
		if(-1 == rws)
		{
			perror("accept");
			return -1;
		}
		else
		{
			while(1)
		   {
			
			memset(&buf, 0, sizeof(buf));
			buf.type		=V4L2_BUF_TYPE_VIDEO_CAPTURE;
			buf.memory		=V4L2_MEMORY_MMAP;
			ioctl(camfd,VIDIOC_DQBUF,&buf);//取缓冲帧
			ioctl(camfd,VIDIOC_QBUF,&buf);
			int ret1=send(rws,videoBufs[buf.index].start,buf.length,MSG_NOSIGNAL);
			if(ret1==-1)
			{
				perror("send");
				close(rws);
				break;
			}
			else if(ret1==0)
			{
				printf("recv 0");
				close(rws);
				break;
			}
			else
			{
			    printf("%d\n",ret1);
			    recv(rws,&flag,1,MSG_NOSIGNAL);
			}
		    }
		}
	}
	camera_stop(camfd);
	return 0;
	}
	return 0;
}

int camera_init()
{
	cameraFd = open("/dev/video0",O_RDWR);// 打开视频设备；
	if(cameraFd==0)
	{
		perror("open:");
		return -1;
	}
	//显示设备信息
	struct v4l2_capability cap;

	ioctl(cameraFd,VIDIOC_QUERYCAP,&cap);

	printf("Driver Name:%s\nCard Name:%s\nBus info:%s\nDriver Version:%u.%u.%u\n",cap.driver,cap.card,cap.bus_info,(cap.version>>16)&0XFF, (cap.version>>8)&0XFF,cap.version&0XFF);
	//显示所有支持的格式
	struct v4l2_fmtdesc fmtdesc; 
	fmtdesc.index=0;
	fmtdesc.type=V4L2_BUF_TYPE_VIDEO_CAPTURE; printf("Support format:\n");

	while(ioctl(cameraFd, VIDIOC_ENUM_FMT, &fmtdesc) != -1)

	{

		printf("\t%d.%s\n",fmtdesc.index+1,fmtdesc.description);

		fmtdesc.index++;

	}
	//设置视频捕获格式
	struct v4l2_format fmt;
	memset(&fmt,0,sizeof(fmt));
	fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	fmt.fmt.pix.width = 320;
	fmt.fmt.pix.height = 240;
	fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_MJPEG;
	fmt.fmt.pix.field       = V4L2_FIELD_INTERLACED;
	if(-1==ioctl(cameraFd,VIDIOC_S_FMT,&fmt))
	{
		perror("ioctl fmt:");
		return -1;
	}
	//给摄像头分配内存
	struct v4l2_requestbuffers  req;
	memset(&req, 0, sizeof(req));
	req.count=4;
	req.type= V4L2_BUF_TYPE_VIDEO_CAPTURE;
	req.memory= V4L2_MEMORY_MMAP;

	if (-1 == ioctl(cameraFd, VIDIOC_REQBUFS, &req) ) 
	{
		printf("VIDIOC_REQvideoBufs ERROR\n");
		return -1;        
	}
	//获取并记录缓存的物理空间
	if(( videoBufs=calloc(req.count,sizeof(*videoBufs))) == NULL )
	{
		return -1;
	}
	for(numvideoBufs = 0; numvideoBufs < req.count; ++numvideoBufs)
	{
		struct v4l2_buffer buf;
		memset(&buf, 0, sizeof(buf));
		buf.type		=V4L2_BUF_TYPE_VIDEO_CAPTURE;
		buf.memory		=V4L2_MEMORY_MMAP;
		buf.index		=numvideoBufs;

		//映射用户空间
		if(-1 == ioctl(cameraFd, VIDIOC_QUERYBUF, &buf))
		{
			printf("VIDIOC_QUERYBUF ERROR\n");
			return -1;
		}

		videoBufs[numvideoBufs].length= buf.length;
		//建立映射关系
		videoBufs[numvideoBufs].start= mmap(NULL, buf.length, PROT_READ | PROT_WRITE,MAP_SHARED,cameraFd, buf.m.offset);
		if(videoBufs[numvideoBufs].start == MAP_FAILED)
		{
			return -1;
		}
		//放入缓存队列
		if (ioctl(cameraFd, VIDIOC_QBUF, &buf) == -1) 
		{
			return -1;
		}	
		printf("QBUF OK %d \n",buf.length);
		width = fmt.fmt.pix.width;
		height = fmt.fmt.pix.height;
	}
	return cameraFd;

}
int server_init()
{
	//服务器网络套接字初始化
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(-1 == sockfd)
	{
		perror("socket");
		return -1;
	}
	//允许重用地址
	int optval = 1;
	if(0 > setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR,&optval, sizeof(int)))
	{
		perror("setsockopt");
		return -1;
	}
	//Internet协议地址结构
	struct sockaddr_in s_addr;
	memset(&s_addr, 0, sizeof(s_addr));
	s_addr.sin_family = AF_INET; //ipv4协议
	s_addr.sin_port = htons(8888);//将port由主机转网络字节序
	s_addr.sin_addr.s_addr = inet_addr("192.168.1.1");//将ip由主机转网络
	socklen_t s_len = sizeof(s_addr);
	//服务器绑定主机地址
	int ret = bind(sockfd, (struct sockaddr *)&s_addr,s_len);
	if(-1 == ret)
	{
		perror("bind");
		close(sockfd);
		return -1;
	}
	//服务器监听套接字
	ret = listen(sockfd,1024);//sockfd变为监听套接字
	if(-1 == ret)
	{
		perror("listen");
		close(sockfd);
		return -1;
	}
	return sockfd;
}

int camera_start(int camfd)
{
	type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	if(-1 == ioctl (camfd, VIDIOC_STREAMON, &type))
	{
		printf("VIDIOC_STREAMON ERROR\n");
	}
	return 0;
}

int camera_stop(int camfd)
{
	int i = 0;
	for(i = 0; i<numvideoBufs; ++i)
	{
		if(munmap(videoBufs[i].start,videoBufs[i].length) == -1)
		{
			exit(-1);
		}
	}
	type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	if(-1==ioctl(camfd,VIDIOC_STREAMOFF,&type))
	{
		printf("VIDIOC_STREAMOFF ERROR\n");
	}
	return 0;
}

int car_run(int fd,char *buf,char *yy)
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
	if(strcmp(buf,"down")==0)
	{
		yy[1]=0x00;
		yy[2]=0x01;
		yy[3]=0x00;
		write(fd,yy,5);	
	}
	if(strcmp(buf,"up")==0)
	{
		yy[1]=0x00;
		yy[2]=0x02;
		yy[3]=0x00;
		write(fd,yy,5);	
	}
	if(strcmp(buf,"right")==0)
	{
		yy[1]=0x00;
		yy[2]=0x03;
		yy[3]=0x00;
		write(fd,yy,5);	
	}
	if(strcmp(buf,"left")==0)
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

int uart_set(int fd,int baude,int c_flow,int bits,char parity,int stop)
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
