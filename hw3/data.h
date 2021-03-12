/*
University of Central Florida
COP 3402 Systeam Software: HW3
Jesus Ugarte
Mina Beshay
Data
*/

//Used in LEX.c
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


//Used in vm.c
#define MAX_STACK_HEIGHT 50
#define MAX_CODE_LENGTH 100

typedef struct instruction
{
    int opcode;
    int l;
    int m;
} instruction;

//Used in Parser
#define MAX_SYMBOL_TABLE_SIZE = 500
symbol_table[MAX_SYMBOL_TABLE_SIZE];


//Recommended data structure for the symbol.
typedef struct {
	int kind; 		// const = 1, var = 2, proc = 3
	char name[12];	// name up to 11 chars
	int val; 		// number (ASCII value)
	int level; 		// L level
	int addr; 		// M address
} symbol;


//Called by main
void compile(char*);

//called inside main.
void lex(char *);
void parser(void);
void vm(void);
