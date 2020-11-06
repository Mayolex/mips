#define LENGH 1024
/* 32 registres generaux + pc + HI + LO */

typedef struct memory_struct memory_struct;
typedef struct register_struct register_struct;
struct memory_struct{
    unsigned char memory[LENGH];
};

struct register_struct{
    unsigned int registers[35];
};

/*indbase: indice du registre adresse dans la mémoire  indrt : indice du registre*/
void lw(memory_struct *mem_struct,register_struct *reg_struct ,int indbase,int indrt, short int offset);
void sw(memory_struct *mem_struct,register_struct *reg_struct ,int indbase,int indrt, short int offset);
