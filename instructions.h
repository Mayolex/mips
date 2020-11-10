#include <stdio.h>
#include <stdlib.h>
#include "memory.h"
#define LO 32
#define HI 33
typedef struct numinstruction numinstruction;
struct numinstruction{
    int op; //voir ligne dans instructiontohex.txt
    int rt;
    int rs;
    int rd;
    int sa;
    int immediate;
    int target;
    int offset;
};

/* renvoit une instruction depuis une instruction stockée en mémoire à l'adresse donnée */
numinstruction *readinstr(unsigned int addr,memory_struct *mem);


void ADDI(numinstruction *addi,register_struct *reg);
void AND(numinstruction *and,register_struct *reg);
void BEQ(numinstruction *beq,register_struct *reg);
void BGTZ(numinstruction *bgtz,register_struct *reg);
void BLEZ(numinstruction *blez,register_struct *reg);
void BNE(numinstruction *bne,register_struct *reg);
void DIV(numinstruction *div,register_struct *reg);
void J(numinstruction *j,register_struct *reg);
void JAL(numinstruction *jal,register_struct *reg);
void JR(numinstruction *jr,register_struct *reg);
void LUI(numinstruction *lui,register_struct *reg);
void LW(numinstruction *lw,register_struct *reg);
void MFHI(numinstruction *mfhi,register_struct *reg);
void MFLO(numinstruction *mflo,register_struct *reg);
void MULT(numinstruction *mult,register_struct *reg);
void NOP(numinstruction *nop,register_struct *reg);
void OR(numinstruction *or,register_struct *reg);
void ROTR(numinstruction *rotr,register_struct *reg);
void SLL(numinstruction *sll,register_struct *reg);
void SLT(numinstruction *slt,register_struct *reg);
void SRL(numinstruction *srl,register_struct *reg);
void SUB(numinstruction *sub,register_struct *reg);
void SW(numinstruction *sw,register_struct *reg);
void SYSCALL(numinstruction *syscall,register_struct *reg);
void XOR(numinstruction *xor,register_struct *reg);