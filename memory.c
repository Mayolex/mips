#include <stdio.h>
#include <stdlib.h>
#include "memory.h"



void lw(memory_struct *mem_struct,register_struct *reg_struct ,int indbase,int indrt, short int offset){
    if(indrt<32){
                reg_struct->registers[indrt]=mem_struct->memory[reg_struct->registers[indbase]+offset];

    }
  
}

void sw(memory_struct *mem_struct,register_struct *reg_struct ,int indbase,int indrt, short int offset){
    if(indrt<32){
        mem_struct->memory[reg_struct->registers[indbase]+offset]=reg_struct->registers[indrt];
    }
}

