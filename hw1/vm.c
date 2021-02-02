/*
University of Central Florida
COP 3402 Systeam Software: HW1
Jesus Ugarte
Mina Beshay
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_STACK_HEIGHT 50
#define MAX_CODE_LENGTH 100

typedef struct instruction
{
    int opcode;
    int l;
    int m;
} instruction;


// Helper base function
int base(int stack[], int level, int BP)
{
    int base = BP;
    int counter = level;
    while (counter > 0)
    {
        base = stack[base];
        counter--;
    }
    return base;
}

//Main function run
int main(int argc, char **argv)
{
    // open infile pointer to read from input file
    FILE *ifp = fopen(argv[1], "r");

    // prepare for PM/O cycle by declaring and initilizing variables
    int numInst = 0;
    instruction program[MAX_CODE_LENGTH];
    instruction IR; // Instruction Register
    int SP = -1;    // Stack pointer
    int BP = 0;     // Base pointer
    int PC = 0;     // Program Counter
    int numAR = 0;  // Activation Record # used for dividing of stack
    int iLN = 0;    // input line number
    int op, l, m;   // used to read from file
    int halt = 1;   // used to end the program at 9 0 3
    char opName[4]; // stores the name of the opcode
    int ar[3];
    int *stack = calloc(MAX_STACK_HEIGHT, sizeof(int)); // make stack with all values 0

    if (!ifp)
    {
        printf("can't read file");
        return 0;
    }

    //Take the input file and store it in the program array of structs
    while (!feof(ifp))
    {
        instruction inst;
        if (fscanf(ifp, "%d %d %d", &op, &l, &m) < 3)
            break;
        inst.opcode = op;
        inst.l = l;
        inst.m = m;
        program[numInst] = inst;
        numInst++;
    }

    // print the first two lines of
    printf(" \t\t\t\tPC\tBP\tSP\tstack\n");
    printf("Initial values:\t%d\t%d\t%d\n", PC, BP, SP);

    //Executing Program until it reaches the end 9 0 3
    while (halt == 1)
    {
        // Execute Fetch cycle
        IR = program[PC];
        PC++;

        // store input line number
        iLN = PC - 1;

        // evaluate opcode to determine what operation to do
        switch (IR.opcode)
        {
        // LIT: Pushes a constant value (literal) M onto the stack
        case 1:
            strcpy(opName, "LIT");
            SP++;
            stack[SP] = IR.m;
            break;

        // OPR: Operation to be performed on the data at the top of the stack based on IR.m
        case 2:
            switch (IR.m)
            {
            // RTN
            case 0:
                strcpy(opName, "RTN");
                stack[BP - 1] = stack[SP];
                SP = BP - 1;
                BP = stack[SP + 2];
                PC = stack[SP + 3];
                break;
            // NEG: Negative
            case 1:
                strcpy(opName, "NEG");
                stack[SP] = -1 * stack[SP];
                break;
            // ADD: Add Stack[SP] +the one after
            case 2:
                strcpy(opName, "ADD");
                SP--;
                stack[SP] = stack[SP] + stack[SP + 1];
                break;
            // SUB: Subtract
            case 3:
                strcpy(opName, "SUB");
                SP--;
                stack[SP] = stack[SP] - stack[SP + 1];
                break;
            // MUL: Multiply
            case 4:
                strcpy(opName, "MUL");
                SP--;
                stack[SP] = stack[SP] * stack[SP + 1];
                break;
            // DIV: divide
            case 5:
                strcpy(opName, "DIV");
                SP--;
                stack[SP] = stack[SP] / stack[SP + 1];
                break;
            // ODD: if stack[SP] is odd(%2)
            case 6:
                strcpy(opName, "ODD");
                stack[SP] = stack[SP] % 2;
                break;
            // MOD: SP remainder SP+1
            case 7:
                strcpy(opName, "MOD");
                SP--;
                stack[SP] = stack[SP] % stack[SP + 1];
                break;
            // EQL: Equal
            case 8:
                strcpy(opName, "EQL");
                SP--;
                stack[SP] = (stack[SP] == stack[SP + 1]);
                break;
            // NEQ: Not equal
            case 9:
                strcpy(opName, "NEQ");
                SP--;
                stack[SP] = (stack[SP] != stack[SP + 1]);
                break;
            // LSS: less tha statementn
            case 10:
                strcpy(opName, "LSS");
                SP--;
                stack[SP] = (stack[SP] < stack[SP + 1]);
                break;
            // LSQ: Less than or equal
            case 11:
                strcpy(opName, "LSQ");
                SP--;
                stack[SP] = (stack[SP] <= stack[SP + 1]);
                break;
            // GTR: Greater than
            case 12:
                strcpy(opName, "GTR");
                SP--;
                stack[SP] = (stack[SP] > stack[SP + 1]);
                break;
            // GEQ: Greater or equal
            case 13:
                strcpy(opName, "GEQ");
                SP--;
                stack[SP] = (stack[SP] >= stack[SP + 1]);
                break;

            default:
                break;
            }
            break;

        // LOD: Load value to top of stack from the stack location at
        //offset M from L lexicographical levels down
        case 3:
            strcpy(opName, "LOD");
            SP++;
            stack[SP] = stack[base(stack, IR.l, BP) + IR.m];
            break;

        //STO: Store value at top of stack in the stack location at offset M
        //from L lexicographical levels down
        case 4:
            strcpy(opName, "STO");
            stack[base(stack, IR.l, BP) + IR.m] = stack[SP];
            SP--;
            break;

        //CAL: Call procedure at code index M (generates new
        //Activation Record andPC  M)
        case 5:
            strcpy(opName, "CAL");
            stack[SP + 1] = base(stack, IR.l, BP); // static link (SL)
            stack[SP + 2] = BP;                    // dynamic link (DL)
            stack[SP + 3] = PC;                    // return address (RA)
            stack[SP + 4] = stack[SP];             // parameter (P)
            BP = SP + 1;
            PC = IR.m;

            //Handle Activation Record division
            ar[numAR] = SP;
            numAR++;
            break;

        // INC: Call procedure at code index M (generates new
        //Activation Record and PC  M)
        case 6:
            strcpy(opName, "INC");
            SP += IR.m;
            break;

        //JMP: Jump to instruction M (PC  M
        case 7:
            strcpy(opName, "JMP");
            PC = IR.m;
            break;

        // JPC: Jump to instruction M if top stack element is 0
        case 8:
            strcpy(opName, "JPC");
            if (stack[SP] == 0)
                PC = IR.m;
            SP--;
            break;

        //SYS Statement
        case 9:
            strcpy(opName, "SYS");
            //Write the top stack element to the screen
            if (IR.m == 1)
            {
                printf("Top of Stack Value: %d\n", stack[SP]);
                SP--;
            }
            // Read in input from the user and store it on top of the stack
            else if (IR.m == 2)
            {
                SP++;
                printf("Please Enter an Integer:\n");
                scanf("%d", &stack[SP]);
            }

            // End program
            else if (IR.m == 3)
                halt = 0;
            break;

        default:
            break;
        }

        // print daily line at the end of every iteration
        printf("%2d %s %-3d%-4d\t", iLN, opName, IR.l, IR.m);
        printf("%-5d%-5d%-5d\t", PC, BP, SP);

        //Making sure | is printed in stack when needed
        int countAR = 0;
        for (int d = 0; d <= SP; d++)
        {
            if (countAR < numAR && ar[countAR] < d)
            {
                countAR++;
                printf(" |");
            }
            // print stack
            printf(" %d", stack[d]);
        }

        printf("\n");
    }

    // close file and free stack
    fclose(ifp);
    free(stack);
    return 0;
}
