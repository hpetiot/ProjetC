#ifndef __COLOR_H__
#define __COLOR_H__

/* ------------------------------------------------------------------ */

	#include <MLV/MLV_all.h>
	#include "pixel.h"
	#include "quadtree.h"
	#include "zone.h"
	#define MAX_DIST_COLOR 20

/* ------------------------------------------------------------------ */
	/**
	* Check if all t leaf have the same color
	* @param t The tree we are looking at
	* @return 1 if all its leaf have the same color
			  0 otherwise
	*/
	int kids_same_color(Tree *t);

	/**
	* Check if c1 and c2 have a close color 
	* @param c1 The first MLV_Color
	* @param c2 The second MLV_Color
	* @return 1 if c1 an c2 r, g, b values are close enough, maximum of MAX_DIST_COLOR 
			  0 otherwise
	*/
	int close_color(MLV_Color c1, MLV_Color c2);

	/**
	* Calculates distance between 2 MLV_Color 
	* @param c1 The first MLV_Color
	* @param c2 The second MLV_Color
	* @return Distance between both colors
	*/
	double color_distance(MLV_Color c1, MLV_Color c2);

	/**
	* Returns the error of a zone (= rectangle of top left corner (x1, y1),
	* and bottom right corner (x2, y2))
	* @param zone_color Zone's color
	* @param image The image we are calculating the error from
	* @param zone The zone we are calculating the error from
	* @return The error from the zone
	*/
	double zone_color_error(MLV_Color zone_color, const MLV_Image *image, Zone zone);
		
	/**
	* Returns the average color of a zone (= rectangle of top left corner (x1, y1) 
	* and bottom right corner (x2, y2))
	* @param image The image we are calculating the error from
	* @param zone The zone we are calculating the error from
	* @return The MLV_Color of the zone
	*/
	MLV_Color zone_average_color(const MLV_Image *image, Zone zone);

	/**
	* Subdivise a zone to get all its zones (NO, NE, SE, SO) average color
	* @param image The image we'll calculate each zone's average color
	* @param zone The zone we are subdivising
	* @param no NO zone of parameter "zone"
	* @param ne NE zone of parameter "zone"
	* @param so SO zone of parameter "zone"
	* @param se SE zone of parameter "zone"
	*/
	void get_zones_average_color(const MLV_Image *image, Zone zone, MLV_Color *no, MLV_Color *ne, MLV_Color *so, MLV_Color *se);

/* ------------------------------------------------------------------ */

#endif