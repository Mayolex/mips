
#define TAILLEOP 10

char* instruction_to_hexa(char * string);
typedef struct instruction instruction;
struct instruction{
    char opcode[TAILLEOP];
    char op1[TAILLEOP];
    char op2[TAILLEOP];
    char op3[TAILLEOP];
};
