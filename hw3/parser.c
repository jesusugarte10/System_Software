/*
Jesus Ugarte
Mina Beshay
University of Central FLorida
 Parser
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

//Recommended data structure for the symbol.
typedef struct {
	int kind; 		// const = 1, var = 2, proc = 3
	char name[12];	// name up to 11 chars
	int val; 		// number (ASCII value)
	int level; 		// L level
	int addr; 		// M address
} symbol;

int main(int argc, char *argv[] ){

    // File pointer to open our input.
    FILE *ifp = fopen(argv[1], "r"); 

    if(!ifp){
        printf("can't open file\n");
        return 1;
    }




    return 0;
}