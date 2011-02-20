
/*
 *		Copyright (C) 2010	Xu Yinhai (徐银海)<xuyinhai@live.cn>
 *      
 */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <time.h>
#include "common.h"
#define N 6 

#define DEBUG 0
#if DEBUG
#endif

int rain(char * filename, fb_info fb_inf)
{

	fb_info jpeg_inf;

    u8_t *buf24 = decode_jpeg(filename, &jpeg_inf);
    u8_t * scale_buf = scale24(buf24, fb_inf, jpeg_inf);
    //u32_t *buf32 = rgb24to32(scale_buf, fb_inf);
    u16_t *buf16 = rgb24to16(scale_buf, fb_inf);

	int x, y, x1, y1, i, j;
	srand(time(NULL));
	int m, n;
	m = 0;
	while(m < 500) {
		n = 0;
		while(n < 200)  {
			x = rand()%fb_inf.w;
			y = rand()%fb_inf.h;
			x1 = x + N;
			y1 = y + 2*N;
			if(x1 > 0 && x1 < fb_inf.w && y1 < fb_inf.h && y1 > 0)
				myline(x1, y1, x, y, 0xffffff, fb_inf);
			n++;
		}
		for(j = 0; j < fb_inf.h; j++)
        	for(i = 0; i < fb_inf.w; i++)
        		fb_pixel(fb_inf, i, j, buf16[j*fb_inf.w + i]);
		usleep(100);
		m++;

	}

	free(buf24);
	free(scale_buf);
	free(buf16);
	return 0;
}
