#include "moduletp4.h"
#define TAILLEOP 10

typedef struct instruction instruction;
struct instruction{
    char opcode[TAILLEOP];
    char op1[TAILLEOP];
    char op2[TAILLEOP];
    char op3[TAILLEOP];
    char type;
    int arg_nb;
};


instruction * cut_instruction(char  string[]);
char* instruction_to_hexa(char * string);
int registerToInt(char reg[]);
int immediateToInt(char reg[]);
long int targetToInt(char targ[]);
void translate_instruction(instruction * instr, char* instructFile,FILE* fichierEntree, FILE* fichierSortie);