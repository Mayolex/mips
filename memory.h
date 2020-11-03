#define LENGH 1024
/* 32 registres generaux + pc + HI + LO */

typedef struct memory_struct memory_struct;
typedef struct register_struct register_struct;
struct memory_struct{
    unsigned int registers[32];
    unsigned int PC;
    unsigned int HI;
    unsigned int LO;
    unsigned int memory[LENGH];
    unsigned int SP;/* pointe sur le premier element vide*/
};

struct register_struct{
    unsigned int registers[32];
    unsigned int PC;
    unsigned int HI;
    unsigned int LO;
};
void lw(memory_struct *mem_struct,register_struct *reg_struct ,int reg, short int offset);
void sw(memory_struct *mem_struct,register_struct *reg_struct, int reg, short int offset);