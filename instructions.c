#include "instructions.h"



numinstruction *readinstr(unsigned int addr,memory_struct *mem){
    unsigned int valinstr = mem->memory[addr];
    
    numinstruction *instr=malloc(sizeof(numinstruction));
    if(valinstr<<26==0){//cas des instructions de type registre
        instr->op=valinstr&0x3F;
        instr->rs=(valinstr<<21)&0x1F;
        instr->rt=(valinstr<<16)&0x1F;
        instr->rd=(valinstr<<11)&0x1F;
        instr->sa=(valinstr<<6)&0x1F;
    }
    else if((valinstr<<26)<=2){//cas des instructions de type Jump
        instr->op=valinstr<<26;
        instr->target=valinstr&0x3FFFFFF;
    }
    else{//cas des instructions de type immédiat
        instr->op=valinstr<<26;
        instr->rs=(valinstr<<21)&0x1F;
        instr->rt=(valinstr<<16)&0x1F;
        instr->immediate=valinstr&0xFFFF;
    }
    return(instr);
}