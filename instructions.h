#include "parser.h"
typedef struct numinstruction numinstruction;
struct numinstruction{
    int op; //voir ligne dans instructiontohex.txt
    int rt;
    int rs;
    int rd;
    int sa;
    int immediate;
    int target;
};

/* renvoi une instruction depuis une instruction stocké en mémoire a l'adresse donnée */
numinstruction readinstr(unsigned int addr,memory_struct *mem);