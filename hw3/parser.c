/*
University of Central Florida
COP 3402 Systeam Software: HW3
Jesus Ugarte
Mina Beshay
Parser
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "data.h"

//Recommended data structure for the symbol.
typedef struct {
	int kind; 		// const = 1, var = 2, proc = 3
	char name[12];	// name up to 11 chars
	int val; 		// number (ASCII value)
	int level; 		// L level
	int addr; 		// M address
} symbol;

symbol_table[MAX_SYMBOL_TABLE_SIZE];



//For constants, you must store kind, name and value.
//For variables, you must store kind, name, L and M.

int parser(int argc, char *argv[] ){

    // File pointer to open our input.
    FILE *ifp = fopen(argv[1], "r"); 

    if(!ifp){
        printf("can't open file\n");
        return 1;
    }

    return 0;
}