#ifndef __COLOR_H__
#define __COLOR_H__

/* ------------------------------------------------------------------ */

	#include <MLV/MLV_all.h>
	#include "pixel.h"
	#include "quadtree.h"
	#include "zone.h"
	#define MAX_DIST_COLOR 20

/* ------------------------------------------------------------------ */
	/* Return 1 if all of t's leaf have the same color, otherwise 0 */
	int kids_same_color(Tree *t);

	/* Return 1 if r,g,b of c1 and c2 are close enough to each other (max of MAX_DIST_COLOR), otherwise 0 */
	int close_color(MLV_Color c1, MLV_Color c2);

	/* Calculates distance between 2 MLV_Color */
	double color_distance(MLV_Color c1, MLV_Color c2);

	/* Returns the error of a zone (= rectangle of top left corner (x1, y1) and bottom right corner (x2, y2)) */
	double zone_color_error(MLV_Color zone_color, const MLV_Image *image, Zone zone);
	
	/* Returns the average color of a zone (= rectangle of top left corner (x1, y1) and bottom right corner (x2, y2)) */
	MLV_Color zone_average_color(const MLV_Image *image, Zone zone);

	/* Get all average color of zone no, ne, so and se */
	void get_zones_average_color(const MLV_Image *image, Zone zone, MLV_Color *no, MLV_Color *ne, MLV_Color *so, MLV_Color *se);

/* ------------------------------------------------------------------ */

#endif