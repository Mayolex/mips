#include "instructions.h"

/*
On transforme une instruction en numinstruction
*/
numinstruction *readinstr(unsigned int addr,memory_struct *mem){
    unsigned int valinstr = rw(mem,addr);
    numinstruction *instr=malloc(sizeof(numinstruction));
    if(valinstr>>26==0){//cas des instructions de type registre
        instr->op=valinstr&0x3F;
        instr->rs=(valinstr>>21)&0x1F;
        instr->rt=(valinstr>>16)&0x1F;
        instr->rd=(valinstr>>11)&0x1F;
        instr->sa=(valinstr>>6)&0x1F;
        instr->type=2;
    }
    else if((valinstr>>26)<=3){//cas des instructions de type Jump
        instr->op=valinstr>>26;
        instr->target=valinstr&0x3FFFFFF;
        instr->type=1;
    }
    else{//cas des instructions de type immédiat
        instr->op=valinstr>>26;
        instr->rs=(valinstr>>21)&0x1F;
        instr->rt=(valinstr>>16)&0x1F;
        instr->immediate=valinstr&0xFFFF;
        instr->type=0;
    }
    return(instr);
}

void ADD(numinstruction *add,register_struct *reg){
    wr(reg,add->rd,(reg->registers[add->rs])+(reg->registers[add->rt]));
}
void ADDI(numinstruction *addi,register_struct *reg){
    wr(reg,addi->rt,(reg->registers[addi->rs])+(addi->immediate));
}
void AND(numinstruction *and,register_struct *reg){
    wr(reg,and->rd,(reg->registers[and->rs])&(reg->registers[and->rt]));
}
void BEQ(numinstruction *beq,register_struct *reg){
    if((reg->registers[beq->rs])==(reg->registers[beq->rt])){
        wr(reg,GP,(beq->immediate)-4);//pas sûr pour le -4
    }
}
void BGTZ(numinstruction *bgtz,register_struct *reg){
    if((reg->registers[bgtz->rs])>0){
        wr(reg,GP,(bgtz->immediate)-4);
    }
}
void BLEZ(numinstruction *blez,register_struct *reg){
    if((reg->registers[blez->rs])<=0){
        wr(reg,GP,(blez->immediate)-4);
    }
}
void BNE(numinstruction *bne,register_struct *reg){
    if((reg->registers[bne->rs])!=(reg->registers[bne->rt])){
        wr(reg,GP,(bne->immediate)-4);
    }
}
                                                                                                    //void wr(register_struct *reg_struct, int reg, unsigned int value);
void DIV(numinstruction *div,register_struct *reg){
    wr(reg,LO,((reg->registers[div->rs])/(reg->registers[div->rt])));
    wr(reg,HI,((reg->registers[div->rs])%(reg->registers[div->rt])));
}
void J(numinstruction *j,register_struct *reg){
    wr(reg,GP,(j->target)-4);
}
void JAL(numinstruction *jal,register_struct *reg){
    wr(reg,RA,reg->registers[GP]);
    J(jal,reg);
}
void JR(numinstruction *jr,register_struct *reg){
    wr(reg,GP,(reg->registers[RA])-4);
}
void LUI(numinstruction *lui,register_struct *reg){
    wr(reg,lui->rt,(lui->immediate)<<16);
}
void LW(numinstruction *Lw,register_struct *reg,memory_struct *mem){
    lw(mem,reg,Lw->rs,Lw->rt,Lw->immediate);
}
//fin fonctions testées
void MFHI(numinstruction *mfhi,register_struct *reg){
    wr(reg,mfhi->rd,reg->registers[HI]);
}
void MFLO(numinstruction *mflo,register_struct *reg){
    wr(reg,mflo->rd,reg->registers[LO]);
}
void MULT(numinstruction *mult,register_struct *reg){
    wr(reg,LO,(reg->registers[mult->rs]*reg->registers[mult->rt])&0x0000FFFF);
    wr(reg,HI,(reg->registers[mult->rs]*reg->registers[mult->rt])&0xFFFF0000);
}
void NOP(numinstruction *nop,register_struct *reg){
    ;//ou SLL r0 r0 0;
}
void OR(numinstruction *or,register_struct *reg){
    wr(reg,or->rd,(reg->registers[or->rs] | reg->registers[or->rt]));
}
void ROTR(numinstruction *rotr,register_struct *reg){
    int i=0,tmp=0;
    while(i<rotr->sa){
        tmp=((rotr->rt)&1)+tmp;
        tmp*=2;
        (rotr->rt)>>1;
        i++;
    }
    (rotr->rt)>>(rotr->sa);
    rotr->rd=(rotr->rt)|(tmp);
}
void SLL(numinstruction *sll,register_struct *reg){
    (sll->rt)<<(sll->sa);
    sll->rd=sll->rt;
}
void SLT(numinstruction *slt,register_struct *reg){
    if((slt->rs)<(slt->rt)){
        wr(reg,slt->rd,1);
    }
    else{
        wr(reg,slt->rd,0);
    }
}
void SRL(numinstruction *srl,register_struct *reg){
    (srl->rt)>>(srl->sa);
    srl->rd=srl->rt;
}
void SUB(numinstruction *sub,register_struct *reg){
    wr(reg,sub->rd,(reg->registers[sub->rs])-(reg->registers[sub->rt]));
}
void SW(numinstruction *Sw,register_struct *reg,memory_struct *mem){
    sw(mem,reg,Sw->rs,Sw->rt,Sw->immediate);
}
void SYSCALL(numinstruction *syscall,register_struct *reg){
    ;//?
}
void XOR(numinstruction *xor,register_struct *reg){
    int res=(xor->rs)|(xor->rt);
    res%=2;
    wr(reg,xor->rd,res);
}

void operation(numinstruction *instr,register_struct *reg, memory_struct *mem){
    switch(instr->op){
        case 0x20://ADD
            ADD(instr,reg);
            break;
        case 0x08://ADDI ou JR
        printf("on rentre ici %d",instr->type);
            if(instr->type==0){
                ADDI(instr,reg);
            }
            else if(instr->type==1){
                JR(instr,reg);
            }
            break;
        case 0x24://AND
            AND(instr,reg);
            break;
        case 0x04://BEQ
            BEQ(instr,reg);
            break;
        case 0x07://BGTZ
            BGTZ(instr,reg);
            break;
        case 0x06://BLEZ
            BLEZ(instr,reg);
            break;
        case 0x05://BNE
            BNE(instr,reg);
            break;
        case 0x1A://DIV
            DIV(instr,reg);
            break;
        case 0x02://J ou ROTR ou SRL
            if(instr->type==1){
                J(instr,reg);
            }
            else if(instr->type==2){
                ROTR(instr,reg);
                SRL(instr,reg);//?
            }
            break;
        case 0x03://JAL
            JAL(instr,reg);
            break;
        case 0x0F://LUI
            LUI(instr,reg);
            break;
        case 0x23://LW
            LW(instr,reg,mem);
            break;
        case 0x10://MFHI
            MFHI(instr,reg);
            break;
        case 0x12://MFLO
            MFLO(instr,reg);
            break;
        case 0x18://MULT
            MULT(instr,reg);
            break;
        case 0x00://NOP ou SLL
            //NOP(instr,reg);
            SLL(instr,reg);//pour un NOP, on fait un SLL sans valeur (instructions de même type)
            break;
        case 0x25://OR
            OR(instr,reg);
            break;
        case 0x2A://SLT
            SLT(instr,reg);
            break;
        case 0x22://SUB
            SUB(instr,reg);
            break;
        case 0x2B://SW
            SW(instr,reg,mem);
            break;
        case 0x0C://SYSCALL
            SYSCALL(instr,reg);
            break;
        case 0x26://XOR
            XOR(instr,reg);
            break;
    }
}
