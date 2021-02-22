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
//int lexListIndex = 0;
//char reservedWords[0], specialSymbols[0]
int symbol_checker(char sym, FILE* ifp);

int main(int argc, char **argv){

  //FILE Management Section
  FILE* ifp;
  ifp = fopen(argv[1], "r");

  // prepare to read file 
  char* identifier;
  char* symbols;
  char* digits;
  symbos[0] = '|';
  identifier[0] = '\0';
  int s, identifierIndex, Tcounter, Dcounter = 0;

int*token;
  if (!ifp)
  {
    printf("can't read file");
    return 0;
  }

  int c = fgetc(ifp);
  //Reading character by character
  while(c != EOF)
  {
    //Checking for Control
    if((iscntrl(c) != 0) || c == ' ')
    {
      printf("control! %c \n", c);
      // if there's a word, evaluate it 
      if(word[0] != '|')
      {
        // word checker function
        // erase everything 
        // wordIndex = 0;
      }
      if(symbols[0] != '\0') {
        token[0] = symbol_checker(symbols, ifp);
        // erase evrything in symbols and reset s
        s = 0;
      }

      continue;
    }

    //Checking for alpha values
    else if(isalpha(c))
    {
      // add letter to String word so we can evaluate it later
      word[wordIndex] = c;
      word[wordIndex+ 1] = '\0';
      wordIndex++;
      // see if the next char is a digit or alpha, if it is then add it to String word
      while(isalpha(fgetc(ifp)) || isdigit(fgetc(ifp))) {
        c = fgetc(ifp);
        word[wordIndex] = c;
        word[wordIndex+ 1] = '\0';
        wordIndex++;
      }
    }
    
    //Checking for digits
    else if(isdigit(c))
    {
      printf("digit! %c\n", c);
      
    }

    //Checking for special characters
    else
    {
      symbols[s] = c;
      symbols[s+1] = '\0';
      printf("special Char! %c\n", c);
    }

    c = fgetc(ifp); 
    //CHECK FOR ERRORS
  }


  //Printing TOKENS

  fclose(ifp);
  return 0;
}

// iscntr function checks for space and stuff

// word checker 

// symbol tokenizer 
// symbol checker 
int symbol_checker(char sym, FILE* ifp) {

  int c;
  int token = -15;

  switch(sym) 
  {
    case '%':
      token = modsym;
      break;

    case '+':
      token = plussym; 
      break;

    case '-':
      token = minussym;
      break;

    case '*':
      token = multsym;
      break;

    case '(':
      token = lparentsym;
      break;

    case ')':
      token = rparentsym;
      break;

    case '=':
      token = eqsym;
      break;

    case ',':
      token = commasym;
      break;

    case '.':
      token = periodsym;
      break;

    case '<':
      c = fgetc(ifp);
      //Case for <>
      if(c == '>'){
        token = neqsym;
      }
      //Case for <=
      else if(c == '='){
        token = leqsym;
      }
      //Case for <
      else{
        token = lessym;
      }
      break;

    case '>':
      c=fgetc(ifp);

      //Case +for >=
      if(c=='=')
        token = geqsym;
      //Case for >
      else
        token = gtrsym;
      
      break;
                
    case ';':
      token = semicolonsym;
      break;
                
    case ':':
      c=fgetc(ifp);
      if(c == '=')
        token = becomessym;
      //Prints Error 4 for invalid symbols
      else
        printf("Error 4: Invalid symbols.\n");
        
      break;

    default:
      printf("Error 4: Invalid symbols.\n");
      break;
  }
  return token;
}


// evaluate symbols 
// evaluate word/variables identsym 2 (word)
// evaluate numbersym 3, 8 