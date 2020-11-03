#include <stdio.h>
#include <stdlib.h>
#include "memory.h"



void lw(memory_struct *mem_struct,register_struct *reg_struct ,int reg, short int offset){
    if(reg<32){
        reg_struct->registers[reg]=mem_struct->memory[mem_struct->SP-1+offset];
    }
    else if(reg==32){
        reg_struct->PC=mem_struct->memory[mem_struct->SP-1+offset];
    }
    else if(reg=33){
        reg_struct->HI=mem_struct->memory[mem_struct->SP-1+offset];
    }
    else{
        reg_struct->LO=mem_struct->memory[mem_struct->SP-1+offset];
    }
    mem_struct->SP--;
}

void sw(memory_struct *mem_struct,register_struct *reg_struct ,int reg, short int offset){
    if(reg<32){
        mem_struct->memory[mem_struct->SP+offset]=reg_struct->registers[reg];
    }
    else if(reg==32){
        mem_struct->memory[mem_struct->SP+offset]=reg_struct->PC;
    }
    else if(reg=33){
        mem_struct->memory[mem_struct->SP+offset]=reg_struct->HI;
    }
    else{
        mem_struct->memory[mem_struct->SP+offset]=reg_struct->LO;
    }    
    mem_struct->SP=mem_struct->SP+1;
}


int tests(){
    memory_struct mem;
    mem.SP=0;
    register_struct regs;
    regs.registers[0]=34;
    regs.registers[2]=12;
    sw(&mem,&regs,0,0);

    printf("%d\n",mem.memory[mem.SP-1]);

    sw(&mem,&regs,2,0);
    printf("%d\n",mem.memory[mem.SP-1]);

    lw(&mem,&regs,3,0);
    printf("%d\n",regs.registers[3]);
    return(0);
}