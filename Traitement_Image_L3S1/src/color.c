#include <MLV/MLV_all.h>
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "color.h"

/* ------------------------------------------------------------------ */

int kids_same_color(Tree *t) {
	return (t->sub->no->sub->color == t->sub->ne->sub->color) &&
	       (t->sub->no->sub->color == t->sub->so->sub->color) &&
	       (t->sub->no->sub->color == t->sub->se->sub->color);
}

/* ------------------------------------------------------------------ */

int close_color(MLV_Color c1, MLV_Color c2) {
	unsigned char r1, g1, b1, a1,
				  r2, g2, b2, a2;

	MLV_convert_color_to_rgba(c1, &r1, &g1, &b1, &a1);
	MLV_convert_color_to_rgba(c2, &r2, &g2, &b2, &a2);

	if (abs(r1 - r2) <= MAX_DIST_COLOR &&
	    abs(g1 - g2) <= MAX_DIST_COLOR &&
	    abs(b1 - b2) <= MAX_DIST_COLOR) {
    	return 1;
    }

	return 0;
}




/* ------------------------------------------------------------------ */

double color_distance(MLV_Color c1, MLV_Color c2) {
	unsigned char r1, g1, b1, a1,
				  r2, g2, b2, a2;

	MLV_convert_color_to_rgba(c1, &r1, &g1, &b1, &a1);
	MLV_convert_color_to_rgba(c2, &r2, &g2, &b2, &a2);


	return sqrt(pow(r1 - r2, 2) + pow(g1 - g2, 2) + pow(b1 - b2, 2) + pow(a1 - a2, 2));
}


/* ------------------------------------------------------------------ */

double zone_color_error(MLV_Color zone_color, const MLV_Image *image, Zone zone) {
	int i, j;
	unsigned char r, g, b, a;
	double color_error = 0.0;
	Pixel px, zone_px;

	MLV_convert_color_to_rgba(zone_color, &r, &g, &b, &a);

	zone_px.r = (int) r;
	zone_px.g = (int) g;
	zone_px.b = (int) b;
	zone_px.a = (int) a;

	for (i = zone.y1 ; i < zone.y2 ; i++) {
		for (j = zone.x1 ; j < zone.x2 ; j++) {
			MLV_get_pixel_on_image(image, j, i, &(px.r), &(px.g), &(px.b), &(px.a));

			color_error += pixel_distance(px, zone_px);
		}
	}

	return color_error;
}


/* ------------------------------------------------------------------ */

MLV_Color zone_average_color(const MLV_Image *image, Zone zone) {
	int r = 0, g = 0, b = 0, a = 0; 
	int i, j, nb_pixel = 0;
	Pixel px;
	
	assert(zone.x1 >= 0 && zone.x1 <= SIZE_IMAGE);
	assert(zone.y1 >= 0 && zone.y1 <= SIZE_IMAGE);
	assert(zone.x2 >= 0 && zone.x2 <= SIZE_IMAGE);
	assert(zone.y2 >= 0 && zone.y2 <= SIZE_IMAGE);
	
	for (i = zone.y1 ; i < zone.y2 ; i++) {
		for (j = zone.x1 ; j < zone.x2 ; j++) {
			MLV_get_pixel_on_image(image, j, i, &(px.r), &(px.g), &(px.b), &(px.a));
			r += px.r;
			g += px.g;
			b += px.b;
			a += px.a;

			nb_pixel++;
		}
	}

	r = (r == 0) ? r : (r / nb_pixel);
	g = (g == 0) ? g : (g / nb_pixel);
	b = (b == 0) ? b : (b / nb_pixel);
	a = (a == 0) ? a : (a / nb_pixel);

	return MLV_convert_rgba_to_color(r, g, b, a);
}

/* ------------------------------------------------------------------ */

void get_zones_average_color(const MLV_Image *image, Zone zone, MLV_Color *no, MLV_Color *ne, MLV_Color *so, MLV_Color *se) {
	*no = zone_average_color(image, no_zone(zone));
	*ne = zone_average_color(image, ne_zone(zone));
	*so = zone_average_color(image, so_zone(zone));
	*se = zone_average_color(image, se_zone(zone));
}

/* ------------------------------------------------------------------ */
