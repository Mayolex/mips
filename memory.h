#define LENGH 1024
/* 32 registres generaux + pc + HI + LO */

typedef struct memory_struct memory_struct;
typedef struct register_struct register_struct;
struct memory_struct{
    unsigned int memory[LENGH];
};

struct register_struct{
    unsigned int registers[35];
};
void lw(memory_struct *mem_struct,register_struct *reg_struct ,int indbase,int indrt, short int offset);
void sw(memory_struct *mem_struct,register_struct *reg_struct ,int indbase,int indrt, short int offset);