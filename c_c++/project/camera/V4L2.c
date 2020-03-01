/*************************************************************************
  > File Name: V4L2.c
  > Author: 
  > Mail: 
  > Created Time: Sun 18 Mar 2018 11:04:39 PM PDT
 ************************************************************************/
#include "V4L2.h"
#include <stdio.h>
int camera_init()
{
	int ret;
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
fmt.fmt.pix.width = 640;
fmt.fmt.pix.height = 480;
fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_YUYV;
fmt.fmt.pix.field       = V4L2_FIELD_INTERLACED;
if(-1==ioctl(cameraFd,VIDIOC_S_FMT,&fmt))
{
	perror("ioctl fmt:");
	return -1;
}
//设置共享内存
struct v4l2_requestbuffers  req;
memset(&req, 0, sizeof(req));
req.count= 4;
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
#if 0
int send_pic(int camfd)
{

	int ret; 
	struct v4l2_buffer buf;
	memset(&buf, 0, sizeof(buf));
	buf.type		=V4L2_BUF_TYPE_VIDEO_CAPTURE;
	buf.memory		=V4L2_MEMORY_MMAP; 
	//printf("1111111111\n");
	/*******将数据从队列里读取出来************/
	if (ioctl(camfd, VIDIOC_DQBUF, &buf) == -1)
	{
		perror("DQBUF ERROR:");
		return -1;
	}
	//printf("22222222222\n");
	/**************************yuv转成rgb格式*****************************/
	convert_yuv_to_rgb(videoBufs[buf.index].start, rgb, width, height, 24);
	//printf("3333333333\n");
	/******初始化jpeg************/
	convert_rgb_to_jpg_init();
	//printf("44444444\n");
	/*********************************将rgb转成jpeg***********************************/
	videoJpegs->length =convert_rgb_to_jpg_work(rgb, videoJpegs->jpg,width,height,24,90);
	//printf("55555555\n");
	//sprintf(sendbuf,"%d",videoJpegs->length);
	if (ioctl(camfd, VIDIOC_QBUF, &buf) == -1)
	{
		perror("QBUF");
		return -1;
	}
	//printf("QBUF succeseful\n");
}
#endif



