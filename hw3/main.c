/*
University of Central Florida
COP 3402 Systeam Software: HW1
Jesus Ugarte
Mina Beshay
Main Function
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "data.h"

int main(int argc, char *argv[] ){

    //these are flags that will say whether or not we want to print something or not
    int lexoutput;
    int codegenoutput;
    int vmoutput;

    //temporary variable to be used to check -l, -a, and -v
    char** temp = argv;

        while (argc > 1) {
            if (strcmp(temp[1], "-l") == 0) {
                lexoutput = 1;
            }
            if (strcmp(temp[1], "-a") == 0) {
                codegenoutput = 1;
            }
            if (strcmp(temp[1], "-v") == 0) {
                vmoutput = 1;
            }
            argc--;
            temp++;
        }

    // if just ./compile, or just the test file is given, ie "./compile test.txt" then a usage function will be given.


    // when you are out here, if argc is > 1, then argv[1] will be the source file, unless you want to read from a pre-determined input file,
    // then you would check while (argc > 1) and glob the last one
    // this sends the input file name to the compile function below

    compile(argv[1]);
    return 0;
}

//runs all .c files
void compile(char* filename) {
    
    //run lex.c with the test case. Lex outputs a file with the lexeme list that parser reads from
    lex(filename);
    
    //run parser.c with the input file, that is the output file from lex. 
    parser();
    
    //run vm.c with the input file, that is the output file from the parser. 
    vm();
}