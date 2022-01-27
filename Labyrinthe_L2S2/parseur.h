/*
* Author: Hugo Petiot
* Creation: 28-02-2020
* Modification:
*/

#ifndef __PARSEUR__
#define __PARSEUR__

enum option_type{
 MODE = 0,
 SIZE_LINE = 1,
 SIZE_COLS = 2,
 WAIT = 3,
 UNIQUE = 4,
 SEED = 5,
 ACCESS = 6,
 ENTREE_LINE = 7,
 ENTREE_COLUMN = 8,
 EXIT_LINE = 9,
 EXIT_COLUMN = 10,
 WIN = 11
};
/*WARNING : 'WIN' must stay the last one in the enum type*/

/*
This function searches for the differents options withins the argv table
and fills & allocate the pre-defined 'option' array through its adress.
if an argument was not given it's value is initialised at -1;
It thus need both argv and argc
return 1 on success 0 otherwise
*/
int parseur(int argc, char **argv, int **option, unsigned int *seed);

/* Cruedly display the 'option' table
is intended for debugg only
*/
void display_options(int* option);

#endif