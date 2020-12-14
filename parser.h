#ifndef PARSER_H
#define PARSER_H
#include "main.h"
#include <stdio.h>

#define TAILLEOP 10

typedef struct instruction instruction;
struct instruction{
    char opcode[TAILLEOP];
    char op1[TAILLEOP];
    char op2[TAILLEOP];
    char op3[TAILLEOP];
};


instruction * cut_instruction(char  string[]);
char* instruction_to_hexa(char * string);
int registerToInt(char reg[]);
int immediateToInt(char reg[]);
long int targetToInt(char targ[]);
long unsigned int translate_instruction(instruction * instr, char* instrFile);
void ecrit_fichier(char *nomFichier, long unsigned int *instrliste,int max);
void lit_fichier(FILE *readFile, char *instr);
char *mange_blanc(char *instr);
void transformeTotal(char *fichierALire, char *fichierAEcrire);
long unsigned int stepByStepTrans();
void loadmemory(memory_struct *mem,char *fichierALire);


#endif