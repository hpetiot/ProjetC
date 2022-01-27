#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "zone.h"

/* ------------------------------------------------------------------ */

Zone return_zone(int x1, int y1, int x2, int y2) {
	Zone zone;

	zone.x1 = x1;
	zone.y1 = y1;
	zone.x2 = x2;
	zone.y2 = y2;

	return zone;
}
/* ------------------------------------------------------------------ */

Zone no_zone(Zone zone) {
	Zone no_zone;

	no_zone.x1 = zone.x1;
	no_zone.y1 = zone.y1;
	no_zone.x2 = (zone.x1 + zone.x2) / 2;
	no_zone.y2 = (zone.y1 + zone.y2) / 2;

	return no_zone;
}

/* ------------------------------------------------------------------ */

Zone ne_zone(Zone zone) {
	Zone ne_zone;

	ne_zone.x1 = (zone.x1 + zone.x2) / 2;
	ne_zone.y1 = zone.y1;
	ne_zone.x2 = zone.x2;
	ne_zone.y2 = (zone.y1 + zone.y2) / 2;

	return ne_zone;
}

/* ------------------------------------------------------------------ */

Zone so_zone(Zone zone) {
	Zone so_zone;

	so_zone.x1 = zone.x1;
	so_zone.y1 = (zone.y1 + zone.y2) / 2;
	so_zone.x2 = (zone.x1 + zone.x2) / 2;
	so_zone.y2 = zone.y2;

	return so_zone;
}

/* ------------------------------------------------------------------ */

Zone se_zone(Zone zone) {
	Zone se_zone;

	se_zone.x1 = (zone.x1 + zone.x2) / 2;
	se_zone.y1 = (zone.y1 + zone.y2) / 2;
	se_zone.x2 = zone.x2;
	se_zone.y2 = zone.y2;

	return se_zone;
}

/* ------------------------------------------------------------------ */