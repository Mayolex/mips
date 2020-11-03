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
long unsigned int translate_instruction(instruction * instr, char* instrFile);
void ecrit_fichier(char *nomFichier, long unsigned int aEcrire);
char *lis_fichier(FILE *readFile);
void transformeTotal(char *fichierALire, char *fichierAEcrire);