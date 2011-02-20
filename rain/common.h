/*
 *		Copyright (C) 2010	Xu Yinhai (徐银海)<xuyinhai@live.cn>
 *      
 */
#ifndef __COMMON_H__
#define __COMMON_H__
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <time.h>
#include <string.h>
#include <linux/fb.h>

typedef unsigned char u8_t;
typedef unsigned short u16_t;
typedef unsigned int u32_t;

typedef struct 
{
	int w;				  /* width */
	int h;				  /* high */
	int bpp;				  /* bits per pixel */
	u8_t *fbmem;
}fb_info;


/* ******************** fb.c ******************** */

/* initial framebuf */
extern int init_fb(fb_info *fb_inf);

/* drawing pixel */
extern int fb_pixel(fb_info fb_inf, int x, int y, u32_t color);


/* ******************** jpeg.c ******************** */

/*This returns an array for a 24 bit image.*/
extern u8_t *decode_jpeg (const char *filename, fb_info *jpeg_inf);

extern u32_t * rgb24to32(u8_t *buf24, fb_info jpeg_inf);
extern u16_t * rgb24to16(u8_t *buf24, fb_info jpeg_inf);

extern u8_t * scale24(u8_t *buf24, fb_info new_inf, fb_info jpeg_inf);


/* ******************** line.c ******************** */

extern int myline(int x1,int y1,int x2,int y2,int color, fb_info fb_inf);


/* ******************** rain.c ******************** */

extern int rain(char * filename, fb_info fb_inf);


#endif
