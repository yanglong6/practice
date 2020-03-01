#include "V4L2.h"
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

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
int main()
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


