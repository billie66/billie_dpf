#include "common.h" 
int myline(int x1, int y1, int x2, int y2, int color, fb_info fb_inf) 
{ 

	int iX; /*x方向的坐标变量*/ 
	int iY; /*y方向的坐标变量*/ 
	int iTx; /*x方向的步长变量*/ 
	int iTy; /*y方向的步长变量*/ 
	float fDx; /*x方向的差分变量*/ 
	float fDy; /*y方向的差分变量*/ 
	float fMinf; /*算法中的f*/ 
	float fMaxF; /*算法中的F*/ 
	float fS; /*终点判断变量*/ 
	fMinf = 0.5; /*f=0.5*/ 
	iX = x1; 
	iY = y1; 
	fb_pixel(fb_inf, x1, y1, color); 
	if(x1 == x2 && y1 == y2) /*如果终点和起始点相同*/ 
	{ 
		return(1); 
	} 
	iTx = 1; 
	iTy = 1; 
	fDx = (float)(x2 - x1); 
	fDy = (float)(y2 - y1); 
	fMaxF = fDy / fDx > 0 ? fDy / fDx : (-fDy / fDx); /*F=|dy/dx|*/ 
	if(fDx < 0)iTx = -1; 
	if(fDy < 0)iTy = -1; 
	fS = fDx > 0 ? fDx : (-fDx); 
	if(fMaxF == 1) /*如果F=1*/ 
	{ 
		iX = x1; 
		iY = y1; 
		while(fS > 0) 
		{ 
			iX += iTx; /*x方向走一步*/ 
			iY += iTy; /*y方向走一步*/ 
			fb_pixel(fb_inf, iX, iY, color); 
			fS--; 
		} 
	} 
	else if(fMaxF > 1) /*如果F>1*/ 
	{ 
		fS += fDy > 0 ? fDy : (-fDy); 
		while(fS > 0) 
		{ 
			iY += iTy; /*y方向走一步*/ 
			fb_pixel(fb_inf, iX, iY, color); 
			fMinf += 1 / fMaxF; /*f=f+1/F*/ 
			fS--; 
			if(fMinf >= 1) /*如果f>=1*/ 
			{ 
				iX += iTx; /*x方向走一步*/ 
				fMinf--; /*f=f-1*/ 
				fb_pixel(fb_inf, iX, iY, color); 
				fS--; 
			} 
		} 
	} 
	else /*如果F<1*/ 
	{ 
		fS += fDy > 0 ? fDy : (-fDy); 
		while(fS > 0) 
		{ 
			iX += iTx; /*x方向走一步*/ 
			fb_pixel(fb_inf, iX, iY, color); 
			fMinf += fMaxF; /*f=f+F*/ 
			fS--; 
			if(fMinf >= 1) /*如果f>=1*/ 
			{ 
				iY += iTy; /*y方向走一步*/ 
				fMinf--; /*f=f-1*/ 
				fb_pixel(fb_inf, iX, iY, color); 
				fS--; 
			} 
		} 
	} 
	return 0;
}
