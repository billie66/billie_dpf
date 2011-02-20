#include <stdio.h>
#include <errno.h>
#include <string.h>

#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <linux/fb.h>

#include "common.h"

#define FB_DEVICE "/dev/fb0"

int init_fb(fb_info *fb_inf)
{
	int fd;

	if ((fd = open(FB_DEVICE, O_RDWR)) < 0){
		fprintf(stderr, "Open %s failed:%s\n", FB_DEVICE, strerror(errno));
		return -1;
	}

	struct fb_var_screeninfo fb_var;
	
	if (ioctl(fd, FBIOGET_VSCREENINFO, &fb_var) < 0){
		fprintf(stderr, "fb ioctl failed:%s\n", strerror(errno));
		return -1;
	}
	
	fb_inf->w = fb_var.xres;
	fb_inf->h = fb_var.yres;
	fb_inf->bpp = fb_var.bits_per_pixel;
#if 1
	printf("width:%d\thign:%d\tbpp:%d\n",
		  fb_inf->w, fb_inf->h, fb_inf->bpp);
#endif	
	fb_inf->fbmem = mmap(0, fb_inf->w * fb_inf->h * fb_inf->bpp /8,
					 PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (fb_inf->fbmem == MAP_FAILED){
		fprintf(stderr, "fb mmap failed:%s\n", strerror(errno));
		return -1;
	}
	
	close(fd);
	
	return 0;
}

int fb_pixel(fb_info fb_inf, int x, int y, u32_t color)
{
	u8_t *pos = (u8_t*)fb_inf.fbmem + (fb_inf.w * y + x) * fb_inf.bpp/8;

	switch (fb_inf.bpp){
	case 32:				  /* 32 bits */
		*(pos + 3) = color >> 24;
	case 24:				  /* 24 bits */
		*(pos + 2) = color >> 16;
	case 16:	  		       /* 16 bits */
		*(pos + 1) = color >> 8;
	case 8:			      /* 8 bits */
		*pos = color;
		return 0;
	default:
		return -1;
	}

	return -1;

}

