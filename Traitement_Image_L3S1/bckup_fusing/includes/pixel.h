#ifndef __PIXEL_H__
#define __PIXEL_H__

/* ------------------------------------------------------------------ */
	
	typedef struct {
		int r;
		int g;
		int b;
		int a;
	} Pixel;

/* ------------------------------------------------------------------ */
	
	/* Returns the distance between 2 pixels in rgba */ 
	double pixel_distance(Pixel p1, Pixel p2);

/* ------------------------------------------------------------------ */

#endif