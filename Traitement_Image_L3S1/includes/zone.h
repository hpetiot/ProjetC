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
	
	/**
	* Return a struct "Zone" with the fields equal to those in parameters
	* @param x1 Field x1 of the zone we are returning
	* @param y1 Field y1 of the zone we are returning
	* @param x2 Field x2 of the zone we are returning
	* @param y2 Field y2 of the zone we are returning
	* @return Zone with x1, y1, x2, y2 parameters values
	*/
	Zone return_zone(int x1, int y1, int x2, int y2);
	
	/**
	* Return the NO zone of the "zone" in parameter
	* @param zone The zone we'll subdivise to get its NO zone
	* @return The NO zone of parameter "zone"
	*/
	Zone no_zone(Zone zone);

	/**
	* Return the NE zone of the "zone" in parameter
	* @param zone The zone we'll subdivise to get its NE zone
	* @return The NE zone of parameter "zone"
	*/
	Zone ne_zone(Zone zone);

	/**
	* Return the SO zone of the "zone" in parameter
	* @param zone The zone we'll subdivise to get its SO zone
	* @return The SO zone of parameter "zone"
	*/
	Zone so_zone(Zone zone);

	/**
	* Return the SE zone of the "zone" in parameter
	* @param zone The zone we'll subdivise to get its SE zone
	* @return The SE zone of parameter "zone"
	*/
	Zone se_zone(Zone zone);

/* ------------------------------------------------------------------ */

#endif