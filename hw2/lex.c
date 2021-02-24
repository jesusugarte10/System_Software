/* 
University of Central Florida
COP 3402 System Software: HW2
Lexical Analyzer/Scanner
Member:
Jesus Ugarte
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// Modified.
typedef enum { 
    modsym = 1, identsym, numbersym, plussym, minussym, multsym, slashsym,
    oddsym, eqlsym, neqsym, lessym, leqsym, gtrsym, geqsym, lparentsym,
    rparentsym, commasym, semicolonsym, periodsym, becomessym,
    beginsym, endsym, ifsym, thensym, whilesym, dosym,callsym,
    constsym, varsym, procsym, writesym, readsym, elsesym, returnsym
} token_type;

typedef struct {
  token_type token;
  int number_v;
  char name[12];
}token_struct;


// For Reserved Words given to us (Modified)
const char* reserved_words[]={"const", "var", "procedure", "call", "begin", "end", "if", 
"then", "else", "while", "do", "read", "write", "odd", "return"};

// Special Symbols given to us. (Modified)
const char special_symbols[]={'+', '-', '*', '/', '(', ')', '=', ',' , '.', '<', '>',  ';' , ':', '%'};

int main(int argc, char *argv[]){

    // File pointer to open our input.
    FILE *ifp = fopen(argv[1], "r"); 
    if(!ifp){
        printf("can't open file\n");
        return 1;
    }

    token_struct lex_list[10000];
    for(int counter = 0; counter < 10000; counter++){
      lex_list[counter].token = 0;
    }

    // Variable declarations
    int i = 0; 
    int j = 0; 
    int k = 0;

    // Errors variable to store them
    int errors;
    // Variable to hold each character read in
    int character;
    //For comments
    int comments = 0;
    //Looks ahead at next character read in
    int lookAhead=0;
    int lex_index = 0;

    printf("Lexeme Table:\n");
    printf("\tlexeme\ttoken type\n");

    character = fgetc(ifp);
    //Ignores spaces, tabs, and newlines aka whitespace
    while(character != EOF){
        if((iscntrl(character) != 0) || isspace(character)){
            character = fgetc(ifp);
            lookAhead = 0;
            continue;
        }
        //reads if the next character is part of the alphabet
        if(isalpha(character)){
            char string[12];
            memset(string, 0, sizeof string);
            
            int index = 0;
            string[index]=character;

            index++;
            lookAhead=1;
            //Prints Error 3 if the variable name is too long
            while(isalpha(character=fgetc(ifp))||isdigit(character)){
                if(index > 10){
                    printf("Error : Identifier names cannot exceed 11 characters\n");

                    //Error Checking
                    while (isalpha(character=fgetc(ifp))||isdigit(character)) {

                    }
                    errors=1;

                    //lookAhead=0;
                    break;
                }
                string[index]=character;
                index++;
            }

            //If there was an error, continue without accepting token
            if(errors == 1) {
                errors = 0;
            }

            //Compares the variable name to see if it is one of the reserved words
            int reservedSwitch=-1;

            for(i=0; i<15;i++){
                if(strcmp(string, reserved_words[i])==0){
                    reservedSwitch=i;
                }
            }

            //If it is a reserved word, print out the correct tokentype
            switch(reservedSwitch){

                //Case for const
                case 0:
                    lex_list[lex_index].token = constsym;
                    break;
                //Case for var
                case 1:
                    lex_list[lex_index].token = varsym;
                    break;
                //Case for procedure
                case 2:
                    lex_list[lex_index].token = procsym;
                    break;
                //Case for call
                case 3:
                    lex_list[lex_index].token = callsym;
                    break;
                //Case for begin
                case 4:
                    lex_list[lex_index].token = beginsym;
                    break;
                //Case for end
                case 5:
                    lex_list[lex_index].token = endsym;
                    break;
                //Case for if
                case 6:
                    lex_list[lex_index].token = ifsym;
                    break;
                //Case for then
                case 7:
                    lex_list[lex_index].token = thensym;
                    break;
                //Case for else
                case 8:
                    lex_list[lex_index].token = elsesym;
                    break;
                //Case for while
                case 9:
                    lex_list[lex_index].token = whilesym;
                    break;
                //Case for do
                case 10:
                    lex_list[lex_index].token = dosym;
                    break;
                //Case for read
                case 11:
                    lex_list[lex_index].token = readsym;
                    break;
                //Case for write
                case 12:
                    lex_list[lex_index].token = writesym;
                    break;
                //Case for odd
                case 13:
                    lex_list[lex_index].token = oddsym;
                    break;
                //Case for return
                case 14:
                    lex_list[lex_index].token = returnsym;
                    break;
                //default case when it is a symbol
                default:
                    if(strlen(string) < 11){
                        lex_list[lex_index].token = identsym;
                        strcpy(lex_list[lex_index].name,string);
                    }
                    break;
            }
            
            //Making sure only the right value is printed
            if(strlen(string) < 11){
                printf("%10s\t%d\n", string, lex_list[lex_index].token);
                lex_index++;
            }
        }
        //reads if the next character is part of the 0-9 digits
        else if(isdigit(character)){
            int number = character - '0';
            int d;
            int place = 1;

            lookAhead = 1;

            //Prints Error 2 if the number is too long
            while(isdigit(character = fgetc(ifp))){
                if(place > 4){
                    printf("Error : Numbers cannot exceed 5 digits\n");

                    //Error checking
                    while (isdigit(character = fgetc(ifp))) {

                    }
                    errors = 1;
                    //lookAhead=0;
                    break;
                }
                d=character - '0';
                number=10*number+d;
                place++;
            }
            //Prints Error 1 if the variable starts with a digit, and not a number
            if(isalpha(character)){
                
                //handle error when identifiers cannot begin witha  digit
                if(errors != 1)
                    printf("Error : Identifiers cannot begin with a digit\n");

                while(isalpha(character = fgetc(ifp)) || isdigit(character)){
                }
                continue;
             }

            //If there was an error, continue without accepting token
            if(errors == 1) {
                errors = 0;
                continue;
            }

            lex_list[lex_index].token = numbersym;
            lex_list[lex_index].number_v = number;

            printf("%10d\t%d\n", lex_list[lex_index].number_v, lex_list[lex_index].token);
            lex_index++;
        }

        //reads if the next character is part of the special symbols
        else {
            lookAhead = 0;
            int spec = -1;
            for(i = 0; i < 14; i++){
                if(character == special_symbols[i]){
                    spec = i;
                }
            }
            //If it is a special symbol, print out the correct tokentype
            switch(spec){
                //Case for +
                case 0:
                    lex_list[lex_index].token = plussym;
                    lex_index++;
                    break;
                //Case for -
                case 1:
                    lex_list[lex_index].token = minussym;
                    lex_index++;
                    break;
                //Case for *
                case 2:
                    lex_list[lex_index].token = multsym;
                    lex_index++;
                    break;
                //Case for comments
                case 3:
                    character = fgetc(ifp);
                    lookAhead=1;
                    if(character == '*'){
                        comments = 1;
                        lookAhead = 0;
                        character = fgetc(ifp);
                        while(comments == 1){
                            if(character == '*'){
                                character = fgetc(ifp);
                                if(character == '/'){
                                    comments = 0;
                                }
                            }
                            else{
                                character = fgetc(ifp);
                            }
                        }
                    }
                    else{
                        lex_list[lex_index].token = slashsym;
                        lex_index++;
                    }
                    break;
                //Case for (
                case 4:
                    lex_list[lex_index].token = lparentsym;
                    lex_index++;
                    break;
                //Case for )
                case 5:
                    lex_list[lex_index].token = rparentsym;
                    lex_index++;
                    break;
                //Case for =
                case 6:
                    lex_list[lex_index].token = eqlsym;
                    lex_index++;
                    break;
                //Case for ,
                case 7:
                    lex_list[lex_index].token = commasym;
                    lex_index++;
                    break;
                //Case for .
                case 8:
                    lex_list[lex_index].token = periodsym;
                    lex_index++;
                    break;
                //Case for <>
                case 9:
                    character = fgetc(ifp);
                    lookAhead=1;
                    if(character == '>'){
                        lex_list[lex_index].token = neqsym;
                        lookAhead=0;
                    }
                    //Case for <=
                    else if(character == '='){
                        lex_list[lex_index].token = leqsym;
                        lookAhead=0;
                    }
                    //Case for <
                    else{
                        lex_list[lex_index].token = lessym;
                    }
                    lex_index++;
                    break;
                //Case for >=
                case 10:
                    character = fgetc(ifp);
                    lookAhead = 1;
                    if(character == '='){
                        lex_list[lex_index].token = geqsym;
                        lookAhead = 0;
                    }
                    //Case for >
                    else{
                        lex_list[lex_index].token = gtrsym;
                    }
                    lex_index++;
                    break;
                //Case for ;
                case 11:
                    lex_list[lex_index].token = semicolonsym;
                    lex_index++;
                    break;
                //Case for :=
                case 12:
                    character = fgetc(ifp);
                    if(character == '='){
                        lex_list[lex_index].token = becomessym;
                        lex_index++;
                    }
                    //Prints Error 4 for invalid symbols
                    else{
                        printf("Error : Invalid Symbol\n");
                    }
                    break;
                case 13:
                    lex_list[lex_index].token = modsym;
                    lex_index++;
                    break;

                //Prints Error 4 for invalid symbols
                default:
                    printf("Error : Invalid Symbol\n");
                    break;
            }
            
            //Making sure only to print when there is a valid symbol
            if((spec>=0 ) && (spec<=13))
            {    //Handling cases where char is double digit based on token value
                if(lex_list[lex_index - 1].token == becomessym)
                    printf("%10s\t%d\n", ":=", lex_list[lex_index - 1].token);
                else if(lex_list[lex_index - 1].token == neqsym)
                    printf("%10s\t%d\n", "<>", lex_list[lex_index - 1].token);
                else if(lex_list[lex_index - 1].token == leqsym)
                    printf("%10s\t%d\n", "<=", lex_list[lex_index - 1].token);
                else if(lex_list[lex_index - 1].token == geqsym)
                    printf("%10s\t%d\n", ">=", lex_list[lex_index - 1].token);
                else if((spec == 3) && (comments==0)){
                    comments = 1 ;
                }
                else
                    printf("%10c\t%d\n", special_symbols[spec], lex_list[lex_index - 1].token);
            }
        }
        //if we aren't looking at next character, read in next as a part of a new variable/number/symbol
        if(lookAhead == 0){
            character = fgetc(ifp);
        }
    }

    printf("\nToken List:\n");
    
    //Takes care of variable names
    printf("%d", lex_list[0].token);
    if(lex_list[0].token == 2){
        printf(" %s", lex_list[0].name);
    }
    //Takes care of numbers
    else if(lex_list[0].token == 3){
        printf(" %d", lex_list[0].number_v);
    }
    //prints out variable names in Lexeme List
    for(i = 1; i < lex_index; i++){
        printf(" %d", lex_list[i].token);
        if(lex_list[i].token == 2)
            printf(" %s", lex_list[i].name);
        else if(lex_list[i].token == 3)
            printf(" %d", lex_list[i].number_v);
    }
    fclose(ifp);
  printf("\n");
  return 0;
}