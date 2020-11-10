#include "instructions.h"


numinstruction *readinstr(unsigned int addr,memory_struct *mem){
    unsigned int valinstr = rw(mem,addr);
    printf("valinstr: %X  ",valinstr>>26);
    numinstruction *instr=malloc(sizeof(numinstruction));
    if(valinstr>>26==0){//cas des instructions de type registre
        instr->op=valinstr&0x3F;
        instr->rs=(valinstr>>21)&0x1F;
        instr->rt=(valinstr>>16)&0x1F;
        instr->rd=(valinstr>>11)&0x1F;
        instr->sa=(valinstr>>6)&0x1F;
    }
    else if((valinstr>>26)<=2){//cas des instructions de type Jump
        instr->op=valinstr>>26;
        instr->target=valinstr&0x3FFFFFF;
    }
    else{//cas des instructions de type immédiat
        instr->op=valinstr>>26;
        instr->rs=(valinstr>>21)&0x1F;
        instr->rt=(valinstr>>16)&0x1F;
        instr->immediate=valinstr&0xFFFF;
    }
    return(instr);
}

void ADDI(numinstruction *addi,register_struct *reg){
    reg->registers[addi->rt]=(reg->registers[addi->rs])+(addi->immediate);
}
void AND(numinstruction *and,register_struct *reg){
    reg->registers[and->rd]=(reg->registers[and->rs])&(reg->registers[and->rt]);
}
void BEQ(numinstruction *beq,register_struct *reg){
    if((reg->registers[beq->rs])==(reg->registers[beq->rt])){
        pc+=(beq->offset);
    }
}
void BGTZ(numinstruction *bgtz,register_struct *reg){
    if((reg->registers[bgtz->rs])>0){
        pc+=(bgtz->offset);
    }
}
void BLEZ(numinstruction *blez,register_struct *reg){
    if((reg->registers[blez->rs])<=0){
        pc+=(blez->offset);
    }
}
void BNE(numinstruction *bne,register_struct *reg){
    if((reg->registers[bne->rs])!=(reg->registers[bne->rt])){
        pc+=(bne->offset);
    }
}
void DIV(numinstruction *div,register_struct *reg){
    reg->registers[LO]=(reg->registers[div->rs])/(reg->registers[div->rt]);
    reg->registers[HI]=reg->registers[div->rs])%(reg->registers[div->rt]);
}
void J(numinstruction *j,register_struct *reg)
void JAL(numinstruction *jal,register_struct *reg)
void JR(numinstruction *jr,register_struct *reg)
void LUI(numinstruction *lui,register_struct *reg)
void LW(numinstruction *lw,register_struct *reg)
void MFHI(numinstruction *mfhi,register_struct *reg)
void MFLO(numinstruction *mflo,register_struct *reg)
void MULT(numinstruction *mult,register_struct *reg)
void NOP(numinstruction *nop,register_struct *reg)
void OR(numinstruction *or,register_struct *reg)
void ROTR(numinstruction *rotr,register_struct *reg)
void SLL(numinstruction *sll,register_struct *reg)
void SLT(numinstruction *slt,register_struct *reg)
void SRL(numinstruction *srl,register_struct *reg)
void SUB(numinstruction *sub,register_struct *reg)
void SW(numinstruction *sw,register_struct *reg)
void SYSCALL(numinstruction *syscall,register_struct *reg)
void XOR(numinstruction *xor,register_struct *reg)

void operation(numinstruction *instr){
    switch(instr->op){
        case 0x08://ADDI
            ADDI(instr);
            break;
        case 0x24://AND
            AND(instr);
            break;
        case 0x04://BEQ
        case 0x07://BGTZ
        case 0x06://BLEZ
        case 0x05://BNE
        case 0x1A://DIV
        case 0x02://J
        case 0x03://JAL
        case 0x08://JR
        case 0x0F://LUI
        case 0x23://LW
        case 0x10://MFHI
        case 0x12://MFLO
        case 0x18://MULT
        case 0x00://NOP
        case 0x25://OR
        case 0x02://ROTR
        case 0x00://SLL
        case 0x2A://SLT
        case 0x02://SRL
        case 0x22://SUB
        case 0x2B://SW
        case 0x0C://SYSCALL
        case 0x26://XOR
    }
}
