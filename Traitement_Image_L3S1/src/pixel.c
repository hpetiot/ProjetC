#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "pixel.h"

/* ------------------------------------------------------------------ */

double pixel_distance(Pixel p1, Pixel p2) {
	assert(p1.r >= 0 && p1.r <= 255);
	assert(p1.g >= 0 && p1.g <= 255);
	assert(p1.b >= 0 && p1.b <= 255);
	assert(p1.a >= 0 && p1.a <= 255);

	assert(p2.r >= 0 && p2.r <= 255);
	assert(p2.g >= 0 && p2.g <= 255);
	assert(p2.b >= 0 && p2.b <= 255);
	assert(p2.a >= 0 && p2.a <= 255);

	return sqrt(pow(p1.r - p2.r, 2) + pow(p1.g - p2.g, 2) + pow(p1.b - p2.b, 2) + pow(p1.a - p2.a, 2));
}

/* ------------------------------------------------------------------ */