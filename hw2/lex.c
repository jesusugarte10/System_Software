/* University of Central Florida
Lexical Analyzer/Scanner

Members:
Jesus Ugarte
Mina Beshay
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

//WE ARE WORKING HERE!!


//FROM ABENDIX B In assignment desciption
//Declaration of Token Types:
typedef enum { 
modsym = 1, identsym = 2, numbersym = 3, plussym = 4, minussym = 5, multsym = 6,  slashsym = 7, oddsym = 8, eqsym = 9, neqsym = 10, lessym = 11, leqsym = 12, gtrsym = 13, geqsym = 14, lparentsym = 15, rparentsym = 16, commasym = 17, semicolonsym = 18, periodsym = 19, becomessym = 20, beginsym = 21, endsym = 22, ifsym = 23, thensym = 24, whilesym = 25, dosym = 26, callsym = 27, constsym = 28, varsym = 29, procsym = 30, writesym = 31, readsym = 32, elsesym = 33, returnsym = 34} token_type;


//For Reserved Special Symbols
const char specialSymbols[]={'+', '-', '*', '/', '(', ')', '=', ',' , '.', '<', '>',  ';' , ':', '%'};

//For Reserved Words || We are not using 'begin' and 'end' as stated in doc <- may need to use it? 
const char* reservedWords[]={"const", "var", "procedure", "call", "if", "then", "else", "while", "do", "read", "write", "odd"};


//struct used to contain all tokens details
typedef struct {
    token_type tokenID;
    int numberValue;
    char name[12];
}tokenStruct;

tokenStruct lexList[5000];
int lexListIndex = 0;

int main(int argc, char **argv){

  //FILE Management Section
  FILE* ifp;
  ifp = fopen(argv[1], "r");
  if (!ifp)
  {
    printf("can't read file");
    return 0;
  }

  int c = fgetc(ifp);
  //Ignores spaces, tabs, and newlines aka whitespace
  while(c != EOF)
  {
    c = fgetc(ifp);
    /*
    Main Program goes HERE
    */
  }

  fclose(ifp);
  return 0;
}