#ifndef __ZONE_H__
#define __ZONE_H__

/* ------------------------------------------------------------------ */
	
	typedef struct {
		int x1;
		int y1;
		int x2;
		int y2;
	} Zone;

/* ------------------------------------------------------------------ */
	
	/* Return a struct "Zone" with the fields equal to those in parameters */
	Zone return_zone(int x1, int y1, int x2, int y2);
	
	/* Return the NO zone of the "zone" in parameter */ 
	Zone no_zone(Zone zone);

	/* Return the NE zone of the "zone" in parameter */ 
	Zone ne_zone(Zone zone);

	/* Return the SO zone of the "zone" in parameter */ 
	Zone so_zone(Zone zone);

	/* Return the SE zone of the "zone" in parameter */ 
	Zone se_zone(Zone zone);

/* ------------------------------------------------------------------ */

#endif