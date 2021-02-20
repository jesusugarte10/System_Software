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
modsym = 1, identsym, numbersym, plussym, minussym,
multsym,  slashsym, oddsym, eqsym, neqsym, lessym, leqsym,
gtrsym, geqsym, lparentsym, rparentsym, commasym, semicolonsym,
periodsym, becomessym, beginsym, endsym, ifsym, thensym, 
whilesym, dosym, callsym, constsym, varsym, procsym, writesym,
readsym , elsesym, returnsym } token_type;


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

  /*
    Main Program goes HERE
  */

  fclose(ifp);
  return 0;
}