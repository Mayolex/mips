#include <stdio.h>
#include <stdlib.h>
#include "memory.h"



void lw(memory_struct *mem_struct,register_struct *reg_struct ,int indbase,int indrt, short int offset){
    if(indrt<32){
                reg_struct->registers[indrt]=mem_struct->memory[reg_struct->registers[indbase]+offset];
                reg_struct->registers[indrt]+=mem_struct->memory[reg_struct->registers[indbase]+offset+1]<<8;
                reg_struct->registers[indrt]+=mem_struct->memory[reg_struct->registers[indbase]+offset+2]<<16;
                reg_struct->registers[indrt]+=mem_struct->memory[reg_struct->registers[indbase]+offset+3]<<24;

    }
  
}

void sw(memory_struct *mem_struct,register_struct *reg_struct ,int indbase,int indrt, short int offset){
    if(indrt<32){
        mem_struct->memory[reg_struct->registers[indbase]+offset]=reg_struct->registers[indrt]&0xFF;
        mem_struct->memory[reg_struct->registers[indbase]+offset+1]=((reg_struct->registers[indrt])>>8)&0xFF;
        mem_struct->memory[reg_struct->registers[indbase]+offset+2]=((reg_struct->registers[indrt])>>16)&0xFF;
        mem_struct->memory[reg_struct->registers[indbase]+offset+3]=((reg_struct->registers[indrt])>>24)&0xFF;
    }
}
int rw(memory_struct *mem_struct,unsigned int addr){
    int rtrn=0;
    rtrn=mem_struct->memory[addr];
    rtrn+=mem_struct->memory[addr+1]<<8;
    rtrn+=mem_struct->memory[addr+2]<<16;
    rtrn+=mem_struct->memory[addr+3]<<24;
    return(rtrn);
}

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


int main(){
    register_struct regs;
    memory_struct mem;
    regs.registers[0]=32000;
    regs.registers[1]=15;//
    printRegisters(&regs);
    printMemory(&mem);
    return (0);
}