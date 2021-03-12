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

void parser(void){

    // File pointer to open our input reading from lex output
    FILE *ifp = fopen("lexoutput.txt", "r"); 

    //generating file pointer to output from parser output
    FILE *ofp = fopen("parserout.txt", "w");

    if(!ifp){
        printf("can't open file\n");
        //return 1;
    }
}