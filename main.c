#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "parser.h"
#include "moduletp4.h"


/*
tests/in2.txt->traduction->out_hex.txt
*/
int main(int argc, char *argv[]){

    if(argc==3){
        FILE *readFile=fopen(argv[1],"r");
        if(readFile == NULL){/*test ouverture fichier*/
            perror("erreur a l'ouverture du fichier à lire : il n'existe peut-être pas\n");
            exit(1);
        }
        FILE *writeFile=fopen(argv[2], "w");
        if(writeFile == NULL){/*test ouverture fichier*/
            perror("erreur a l'ouverture du fichier d'écriture\n");
            exit(1);
        }
        char instr[100];
        /*
        en lisant avec le fscanf, pas besoin de cut_instruction()
        */
        fscanf(readFile,"%s", instr);
        printf("instr : %s\n",instr);
        instruction *a = cut_instruction(instr);
        printf("%s\n%s\n%s\n%s\nto int: %d\n",a->opcode,a->op1,a->op2,a->op3,registerToInt(a->op1));
        translate_instruction(a,"instructiontohex.txt",readFile,writeFile);
        fclose(readFile);
        fclose(writeFile);
    }
    else{
        printf("Erreur dans les options\nEssayez quelque chose de la forme :\n        ./exe [nom du fichier a lire] [nom du fichier où écrire]\n");
    }
	return 0;
}