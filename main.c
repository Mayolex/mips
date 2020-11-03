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
    if(argc==3){//on vérifie le nombre d'arguments
        transformeTotal(argv[1],argv[2]);//on utilise les deuxième et troisième arguments
    }
    else{
        printf("Erreur dans les options\nEssayez quelque chose de la forme :\n        ./exe [nom du fichier a lire] [nom du fichier où écrire]\n");
    }
	return 0;
}