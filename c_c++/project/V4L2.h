/*************************************************************************
  > File Name: V4L2.h
  > Author: 
  > Mail: 
  > Created Time: Tue 20 Mar 2018 07:13:25 PM PDT
 ************************************************************************/
#ifndef _V4L2_H
#define _V4L2_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <assert.h>
#include <getopt.h>           
#include <fcntl.h>            
#include <unistd.h>
#include <errno.h>
#include <malloc.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <asm/types.h>        
#include <linux/videodev2.h> 
#include <sys/shm.h>
#include <pthread.h>
#include <signal.h>
enum v4l2_buf_type type;
struct VideoBuffer {

	    char *start;
	        size_t length;
};
unsigned int width;
unsigned int height;


struct VideoBuffer *videoBufs;
struct VideoJpegs *videoJpegs;

int numvideoBufs;
int cameraFd;
int camera_init();
int camera_start(int camfd);
int camera_stop(int camfd);
int send_pic(int camfd);
#endif
