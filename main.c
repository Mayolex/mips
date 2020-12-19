#include "main.h"
/*
tests/in2.txt->traduction->out_hex.txt
*/

int main(int argc, char *argv[]){
    if(argc==1){
        interactif();
    }
    else if(argc==2){//mode pas pas à pas : la distinction interactif se fait plus loin
        interprete(argv[1],0);
    }
    else if(argc==3){//mode non interactif pas à pas
        if(strcmp(argv[2],"-pas")==0){
            interprete(argv[1],1);
        }
        else{
            printf("\n%s n'est pas reconnu\n",argv[2]);
        }
    }
    else{
        printf("Erreur dans les options\nEssayez quelque chose de la forme :\n        ./exe [nom du fichier a lire] [nom du fichier où écrire]\n");
    }
	return 0;
}