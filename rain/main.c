#include "common.h"
#include <stdio.h>

/* main function */
int main(int argc, char *argv[]) 
{
	fb_info fb_inf;
	/* initialize device fb */	
	if (init_fb(&fb_inf) < 0)
	{
		printf("Error init_fb\n");
		exit(1);
	}

    rain("loading.jpg", fb_inf);
    
	return 0;
}

