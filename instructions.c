#include "instructions.h"

/*
On transforme une instruction en numinstruction
*/
numinstruction *readinstr(int addr,memory_struct *mem){
    unsigned int valinstr = rw(mem,addr);
    numinstruction *instr=malloc(sizeof(numinstruction));
    if(valinstr>>26==0){//cas des instructions de type registre et F
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

/*
suite de fonctions claires, de base du processeur
*/
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
        wr(reg,GP,reg->registers[GP]+=(beq->immediate));//pas sûr pour le -4
    }
}
void BGTZ(numinstruction *bgtz,register_struct *reg){
    if((reg->registers[bgtz->rs])>0){
        wr(reg,GP,reg->registers[GP]+=(bgtz->immediate));
    }
}
void BLEZ(numinstruction *blez,register_struct *reg){
    if((reg->registers[blez->rs])<=0){
        wr(reg,GP,reg->registers[GP]+=(blez->immediate));
    }
}
void BNE(numinstruction *bne,register_struct *reg){
    if((reg->registers[bne->rs])!=(reg->registers[bne->rt])){
        wr(reg,GP,reg->registers[GP]+=(bne->immediate));
    }
}
void DIV(numinstruction *div,register_struct *reg){
    wr(reg,LO,((reg->registers[div->rs])/(reg->registers[div->rt])));
    wr(reg,HI,((reg->registers[div->rs])%(reg->registers[div->rt])));
}
void J(numinstruction *j,register_struct *reg){
    wr(reg,GP,(j->target));
}
void JAL(numinstruction *jal,register_struct *reg){
    wr(reg,RA,reg->registers[GP]);
    J(jal,reg);
}
void JR(numinstruction *jr,register_struct *reg){
    wr(reg,GP,(reg->registers[RA]));
}
void LUI(numinstruction *lui,register_struct *reg){
    wr(reg,lui->rt,(lui->immediate)<<16);
}
void LW(numinstruction *Lw,register_struct *reg,memory_struct *mem){
    lw(mem,reg,Lw->rs,Lw->rt,Lw->immediate);
}
void MFHI(numinstruction *mfhi,register_struct *reg){
    wr(reg,mfhi->rd,reg->registers[HI]);
}
void MFLO(numinstruction *mflo,register_struct *reg){
    wr(reg,mflo->rd,reg->registers[LO]);
}
void MULT(numinstruction *mult,register_struct *reg){
    long int entier =(reg->registers[mult->rs]*reg->registers[mult->rt]);
    wr(reg,LO,(reg->registers[mult->rs]*reg->registers[mult->rt])&0xffffffff);
    wr(reg,HI,(entier>>32)&0xffffffff);
}
void NOP(numinstruction *nop,register_struct *reg){
    ;//ou SLL r0 r0 0;
}
void OR(numinstruction *or,register_struct *reg){
    printf(" %x",or->rs);
    wr(reg,or->rd,(reg->registers[or->rs] | reg->registers[or->rt]));
}
void ROTR(numinstruction *rotr,register_struct *reg){
    int tmp=0;
    tmp=(reg->registers[rotr->rt])&((1<<rotr->sa+1)-1);
    wr(reg,rotr->rd,(reg->registers[rotr->rt])/(1<<(rotr->sa)));
    wr(reg,rotr->rd,reg->registers[rotr->rd]+tmp*(1<<32-(rotr->sa)));
}
//fin fonctions testées mais des tests supplémentaires au dessus c'est bien aussi 
void SLL(numinstruction *sll,register_struct *reg){
    //(reg->registers[sll->rt])<<(reg->registers[sll->sa]);
    //reg->registers[sll->rd]=reg->registers[sll->rt];
    //wr(reg,sll->rd,reg->registers[sll->rt]);
    int decalage=(((*reg).registers[(*sll).rt])<<((*reg).registers[(*sll).sa]));
    printf("%d",decalage);
    wr(reg,sll->rd,((reg->registers[sll->rt])<<(sll->sa)));
}
void SLT(numinstruction *slt,register_struct *reg){
    if((reg->registers[slt->rs])<(reg->registers[slt->rt])){
        wr(reg,slt->rd,1);
    }
    else{
        wr(reg,slt->rd,0);
    }
}
void SRL(numinstruction *srl,register_struct *reg){
    wr(reg,srl->rd,(reg->registers[srl->rt])>>(srl->sa));
}
void SUB(numinstruction *sub,register_struct *reg){
    wr(reg,sub->rd,(reg->registers[sub->rs])-(reg->registers[sub->rt]));
}
void SW(numinstruction *Sw,register_struct *reg,memory_struct *mem){
    sw(mem,reg,Sw->rs,Sw->rt,Sw->immediate);
}
void SYSCALL(numinstruction *syscall,register_struct *reg){
    printf("SYSCALL\n");
}
void XOR(numinstruction *xor,register_struct *reg){
    int res=(reg->registers[xor->rs])^(reg->registers[xor->rt]);
    wr(reg,xor->rd,res);
}

/*
choix de l'opération en fonction de l'instruction
lien instruction exécution
*/
void operation(numinstruction *instr,register_struct *reg, memory_struct *mem){
        switch(instr->op){
        case 0x20://ADD
            ADD(instr,reg);
            break;
        case 0x08://ADDI ou JR
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
                if(instr->rs==1){
                    ROTR(instr,reg);
                }
                else{
                    SRL(instr,reg);
                }
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
