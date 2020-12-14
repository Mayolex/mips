
#ifndef INTERPRETEUR_H
#define INTERPRETEUR_H
#include <stdlib.h>
#include <stdio.h>

#include "main.h"

void lit_ligne(FILE *fichier,int offset_ligne);
int step_by_step(memory_struct *mem, register_struct *reg, char *fichier_instr);
void interprete(char fichier[],int step);

#endif