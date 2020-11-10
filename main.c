#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "parser.h"
#include "moduletp4.h"
#include "instructions.h"

/*
tests/in2.txt->traduction->out_hex.txt
*/
/*int main(int argc, char *argv[]){
    if(argc==3){//on vérifie le nombre d'arguments
        transformeTotal(argv[1],argv[2]);//on utilise les deuxième et troisième arguments
    }
    else{
        printf("Erreur dans les options\nEssayez quelque chose de la forme :\n        ./exe [nom du fichier a lire] [nom du fichier où écrire]\n");
    }
	return 0;
}*/

int main(){
	long unsigned int kappa;
	instruction *lul=cut_instruction("LW $2 0($2)");
	kappa=translate_instruction(lul,"instructiontohex.txt");
    memory_struct mem;
    register_struct regs;
    regs.registers[1]=0; //charge l'adresse 0 
    regs.registers[0]=kappa;
    sw(&mem,&regs,1,0,0); //charge l'instruction a l'adresse 0

    numinstruction *instr=readinstr(0,&mem);
    regs.registers[2]=4;
    regs.registers[3]=4;
    regs.registers[7]=8;
    sw(&mem,&regs,2,3,0);
    regs.registers[GP]=8;
    regs.registers[HI]=0;
    regs.registers[LO]=0;
    regs.registers[RA]=16;
    operation(instr,&regs,&mem);
    printRegisters(&regs);
    return(0);
}