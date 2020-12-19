
#include "memory.h"

/*
charge une valeur d'une adresse mémoire contenue dans un registre vers un registre
un offset peut être ajouté à la valeur du registre
*/
void lw(memory_struct *mem_struct,register_struct *reg_struct ,int indbase,int indrt, short int offset){
    if(indrt<32){
        reg_struct->registers[indrt]=mem_struct->memory[reg_struct->registers[indbase]+offset];
        reg_struct->registers[indrt]+=mem_struct->memory[reg_struct->registers[indbase]+offset+1]<<8;
        reg_struct->registers[indrt]+=mem_struct->memory[reg_struct->registers[indbase]+offset+2]<<16;
        reg_struct->registers[indrt]+=mem_struct->memory[reg_struct->registers[indbase]+offset+3]<<24;

    }
  
}

/*
charge une valeur d'un registre vers une adresse mémoire contenue dans un registre
un offset peut être ajouté à la valeur du registre
*/
void sw(memory_struct *mem_struct,register_struct *reg_struct ,int indbase,int indrt, short int offset){
    if(indrt<32){
        mem_struct->memory[reg_struct->registers[indbase]+offset]=reg_struct->registers[indrt]&0xFF;
        mem_struct->memory[reg_struct->registers[indbase]+offset+1]=((reg_struct->registers[indrt])>>8)&0xFF;
        mem_struct->memory[reg_struct->registers[indbase]+offset+2]=((reg_struct->registers[indrt])>>16)&0xFF;
        mem_struct->memory[reg_struct->registers[indbase]+offset+3]=((reg_struct->registers[indrt])>>24)&0xFF;
    }
}

/*
lit un mot en mémoire mémoire à l'adresse donnée
*/
int rw(memory_struct *mem_struct,int addr){
    int rtrn=0;
    rtrn=mem_struct->memory[addr]&0xFF;
    rtrn+=(mem_struct->memory[addr+1]&0xFF)<<8;
    rtrn+=(mem_struct->memory[addr+2]&0xFF)<<16;
    rtrn+=(mem_struct->memory[addr+3]&0xFF)<<24;
    return(rtrn);
}

/*
charge un mot (entier long non signé) en mémoire
*/
void swi(memory_struct *mem_struct,int ind,long unsigned int value){
    mem_struct->memory[ind]=value&0xFF;
    mem_struct->memory[ind+1]=((value)>>8)&0xFF;
    mem_struct->memory[ind+2]=((value)>>16)&0xFF;
    mem_struct->memory[ind+3]=((value)>>24)&0xFF;
}

/*
écrit un entier non signé dans un registre passé en paramètre
les registres spéciaux sont protégés en écriture
*/
void wr(register_struct *reg_struct,int reg,unsigned int value){
    if(reg!=0 && reg!=26 && reg!=27 &&reg!=30){
        reg_struct->registers[reg]=value;
    }

}

/*
imprime l'état de la structure des registres passée en paramètre à l'écran
*/
void printRegisters(register_struct *reg_struct){
    int i = 0;
    printf("REGISTER STATES:\n\n");
    printf("----------------------------------------------------------\n");

    while(i<NBREG){
        printf("$%02d: %-8x  ",i,reg_struct->registers[i]);
        i++;
        while(i%4!=0 && i<NBREG){
        printf("$%02d: %-8x  ",i,reg_struct->registers[i]);
        i++;
        }
        printf("\n");
    }
    printf("----------------------------------------------------------\n");
    printf("\n\n");

}

/*
imprime l'état de la structure mémoire passée en paramètre à l'écran
*/
void printMemory(memory_struct *mem){
        int i = 0;
    printf("Memory STATES:\n\n");
    printf("----------------------------------------------------------\n");

    while(i<LENGH){
        printf("@%08X: %-8X  ",i,rw(mem,i));
        i+=4;
        while(i%16!=0 && i<LENGH){
        printf("@%08X: %-8X  ",i,rw(mem,i));
        i+=4;
        }
        printf("\n");
    }
    printf("----------------------------------------------------------\n");
    printf("\n\n");

}

/*
initialise les emplecements mémoire à 0
*/
void init_mem(memory_struct *mem){
    int i=0;
    for(i=0;i<LENGH;i++){
        mem->memory[i]=0;
    }
}

/*
initialise les registres à 0
*/
void init_reg(register_struct *reg){
    int i=0;
    for(i=0;i<NBREG;i++){
        reg->registers[i]=0;
    }
}