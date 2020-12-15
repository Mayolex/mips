#include "main.h"
/*
tests/in2.txt->traduction->out_hex.txt
*/

int main(int argc, char *argv[]){
    if(argc==1){
        interactif();
    }
    else if(argc==2){//on vérifie le nombre d'arguments
        interprete(argv[1],0);
    }
    else if(argc==3){
        if(strcmp(argv[2],"-pas")==0){
            interprete(argv[1],1);
        }
        else{
            printf("\n%s n'est pas reconnu\n",argv[2]);
        }
    }
    else{
        printf("Erreur dans les options\nEssayez quelque chose de la forme :\n        ./exe [nom du fichier a lire] [nom du fichier où écrire]\n");
    }
	return 0;
}/*
int main(int argc,char *argv[]){
    memory_struct mem;
    register_struct regs;
    init_mem(&mem);
    loadmemory(&mem,"tests/in2.txt");
    
	long unsigned int kappa;
	instruction *lul=cut_instruction("ROTR $4 $2 1");
    numinstruction *instr;
    printf("%s %s %s %s",lul->opcode,lul->op1,lul->op2,lul->op3);
	kappa=translate_instruction(lul,"instructiontohex.txt");
    printf("l'instruction: %X",kappa);
    regs.registers[0]=kappa; 
    regs.registers[1]=0; //charge l'adresse 0
    regs.registers[2]=2;
    regs.registers[3]=2;
    /*regs.registers[7]=8;
    regs.registers[LO]=10;
    regs.registers[GP]=8;
    regs.registers[LO]=0;
    regs.registers[RA]=16;
    sw(&mem,&regs,1,0,0); //charge l'instruction a l'adresse 0
    sw(&mem,&regs,2,3,0);
    instr=readinstr(0,&mem);
    
    //operation(instr,&regs,&mem);
    printRegisters(&regs);
    printMemory(&mem);
    return(0);
}*/