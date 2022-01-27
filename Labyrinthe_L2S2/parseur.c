/*
* Author: Hugo Petiot
* Creation: 28-02-2020
* Modification:
*/

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>

#include "parseur.h"

#define __NOT_MAIN__

/*This function fills the 'lines' and colonms ('cols') integers
of the option array if its non-default. 
*/
static int get_sizes(char* arg, int* lines, int* cols){
    sscanf(arg, "--size=%dx%d", lines, cols);
    return 1;
}

static int get_coord(char* arg, int* line, int* column){
    sscanf(arg, "%d_%d", line, column);
    return 1;
}

/*This funciton fills the display mode interger 'mode' of the option 
array*/
static int get_mode(char* arg, int* mode){

    char* mode_name;

    mode_name = &(arg[7]);

    if (strcmp(mode_name, "text") == 0)
        *mode = 0;
    else if (strcasecmp(mode_name, "UTF-8") == 0)
        *mode = 1;
    else if (strcasecmp(mode_name, "graphic") == 0)
        *mode = 2;
    else if (strcasecmp(mode_name, "none") == 0)
        *mode = 3;
    return 1;
}

/* This function fills the waiting time between two displays 
of the labyrinth intger 'wait_ms' of the option array*/
static int get_wait(char* arg, int* wait_ms){
    sscanf(arg, "--wait=%d", wait_ms);
    return 1;
}
/* This function fills the 'seed' wih the number stated after '--gaine=' in the argument string'arg'*/
static int get_seed(char* arg, unsigned int* seed){
    sscanf(arg, "--seed=%u", seed);
    return 1;
}

void display_options(int* option){
    if (option == NULL){
        printf("!!!\tWARNING\t!!!\n");
        printf("!!!\tYou are trying to display the \'option\' array\t!!!\n");
        printf("\n!!!\tIT IS STRICTLY EQUAL TO \"NULL\"\t!!!\n\n");
        printf("!!!\tend of warning\t!!!\n");
        return;
    }
    printf("===\tCurrent State of \'option\'\t===\n");
    printf("option[MODE] = %d\n", option[MODE]);
    printf("option[SIZE_LINE] = %d\n", option[SIZE_LINE]);
    printf("option[SIZE_COLS] = %d\n", option[SIZE_COLS]);
    printf("option[SEED] = %d\n", option[SEED]);
    printf("option[WAIT] = %d\n", option[WAIT]);
    printf("option[UNIQUE] = %d\n", option[UNIQUE]);
    printf("option[ACCESS] = %d\n", option[UNIQUE]);
    printf("option[ENTREE_LINE] = %d\n", option[ENTREE_LINE]);
    printf("option[ENTREE_COLUMN] = %d\n", option[ENTREE_COLUMN]);
    printf("option[EXIT_LINE] = %d\n", option[EXIT_LINE]);
    printf("option[EXIT_COLUMN] = %d\n", option[EXIT_COLUMN]);
    printf("option[WIN] = %d\n", option[WIN]);
}

void print_help(){
    printf("Syntaxe: ./labyrinth [options]\n");
    printf("Here is a list of all possible option:\n");
    printf("\t\'--mode\' : \'UTF-8\', \'text\' or \'graphic\'' output\n");
    printf("\t\'--start\' : lets you specify the start point in the labyrinth \'lines\'_\'columns\' format\n");
    printf("\t\'--exit\' : same as \'start\' for the exit point\n");
    printf("\t\'--unique\' : enssure that no unessessary removal is done\n");
    printf("\t\'--victor\' : solve the labyrinth after building it, solution is printed in console\n");
    printf("\t\'--size\' : lets you specify the format of the labyrinth using \'lines\'x\'columns\' format\n");
    printf("\t\'--seed\' : lets you specify the seed you want to use for the random effects\n");
    printf("\t\'--wait\' : 0 means to skip until the labyrinth is formed, X means to wait X milliseconds between each loop\n");
}

/*
This function searches for the differents options withins the argv table
and fills & allocate the pre-defined 'option' array through its adress.
It thus need both argv and argc*/

int parseur(int argc, char **argv, int **option, unsigned int *seed){
    int seed_given;
    int i;

    seed_given = 1;

    if ((*option =(int*) malloc(sizeof(int) * (WIN + 1))) == NULL){
        *option = NULL;
        return -2;
    }

    for(i = 0; i <= WIN; i++)
        (*option)[i] = -1;

    for(i = 1; i< argc; i++){
        if (strcmp(argv[i], "--help") == 0){
            print_help();
            return -1;
        }
        if (strncmp(argv[i], "--mode=", 7) == 0){
            get_mode(argv[i], &((*option)[MODE]));
        }
        else if (strncmp(argv[i], "--size=", 7) == 0){
            get_sizes(argv[i], &((*option)[SIZE_LINE]), &((*option)[SIZE_COLS]));
        }
        else if (strncmp(argv[i], "--wait=", 7) == 0){
            get_wait(argv[i], &((*option)[WAIT]));
        }
        else if (strncmp(argv[i], "--unique", 10) == 0){
            (*option)[UNIQUE] = 1;
        }
        else if (strncmp(argv[i], "--victor", 10) == 0){
            (*option)[WIN] = 1;
        }
        else if (strncmp(argv[i], "--access", 8) == 0){
            (*option)[ACCESS] = 1;
        }
        else if (strncmp(argv[i], "--seed", 6) == 0){
            get_seed(argv[i], seed);
            seed_given ++;
        }
        else if (strncmp(argv[i], "--start=", 8) == 0){
            get_coord(&(argv[i][9]), &((*option)[ENTREE_LINE]), &((*option)[ENTREE_COLUMN]));
        }
        else if (strncmp(argv[i], "--exit=", 7) == 0){
            get_coord(&(argv[i][9]), &((*option)[EXIT_LINE]), &((*option)[EXIT_COLUMN]));
        }
    }
    if ((*option)[ACCESS] == -1)
        (*option)[ACCESS] = 0;
    if ((*option)[WIN] == -1)
        (*option)[WIN] = 0;
    if ((*option)[UNIQUE] == -1)
        (*option)[UNIQUE] = 0;
    if ((*option)[MODE] == -1){
        printf("Wrong/Corrupted/No value for 'mode' switching to default\n");
        (*option)[MODE] = 1;
    }
    if ((*option)[MODE] == 3){
    	printf("Mode \'none\' incompatible with \'attente\' other than 0, overwriting \'attente\'\n");
    	(*option)[WAIT] = 0;
    }
    return seed_given;
}

#ifndef __NOT_MAIN__

int main(int argc, char **argv){
    int *option;
    option = NULL;
    if (parseur(argc, argv, &option) == 0){
        printf("something went wrong");
        return 0;
    }
    display_options(option);
    return 0;
}

#endif