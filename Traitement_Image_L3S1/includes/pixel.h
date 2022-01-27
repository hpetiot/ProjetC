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
	
	/**
	* Returns the distance between 2 pixels in rgba
	* @param p1 The first pixel
	* @param p2 The second pixel
	* @return Distance between p1 and p2
	*/
	double pixel_distance(Pixel p1, Pixel p2);

/* ------------------------------------------------------------------ */

#endif