#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "parser.h"
#include "moduletp4.h"


/*
Reçoit une instruction en chaîne de caractères
Sépare l'opcode et les opérandes
Retourne les chaînes de caractèeres contenant l'opcode et les opérandes dans un type instruction
*/
instruction * cut_instruction(char  string[]){
	int i=0,n=0,pos=0;
	instruction *rtrn = malloc(sizeof(instruction));
	while(string[i]!='\0' && string[i]!='#'){
		if(string[i]!=' ' && string[i]!=','){
			switch(pos){
				case 0: 
					rtrn->opcode[i]=string[i];
					break;
				case 1: 
					rtrn->op1[i-n]=string[i];
					break;
				case 2:
					rtrn->op2[i-n]=string[i];					
					break;
				case 3: 
					rtrn->op3[i-n]=string[i];
					break;
				default:
					break;
			}
			
		}
		else{
			n=i+1;
			pos++;
		}
		i++;
	}
	rtrn->arg_nb=pos;
	return(rtrn);
}
/*
Reçoit un registre en chaîne de caractère
Transforme la chaîne en entier
Retourne la valeur entière du registre (avec le bit de poids faible à 0 car il valait $)
*/
int registerToInt(char reg[]){
	int rtrn=0;
	if(reg[0]=='$'){
		rtrn=valeurDecimale(&reg[1]);
	}
	return(rtrn&31);
}
/*
Reçoit une valeur immédiate en chaîne de caractère
Transforme en entier de 16 bits maximum
Retourne l'entier
*/
int immediateToInt(char im[]){
	int rtrn=0;
	rtrn=valeurDecimale(im)&65535;/*on s'assure de respecter les 16 bits*/
	/*printf("\nhexa :%x \n",rtrn);*/
	return(rtrn);
}
/*
Reçoit un registre destination de 26 bits (type jump)
Transforme en entier avec premier bit nul car contenait $
Retourne l'entier
*/
long int targetToInt(char targ[]){
	int rtrn=0;
	rtrn=(valeurDecimale(targ)&67108863);/*2^26*/
	return(rtrn);
}
/*
Reçoit une instruction de type instruction (instruction découpée)
Lit l'opcode d'une instruction dans un fichier
Traduit l'instruction complète en fonction de son type en hexadécimal
Ecrit dans un fichier de sortie l'instruction reconstituée traduite
Ne retourne rien
*/
long unsigned int translate_instruction(instruction * instr, char* instrFile){
	char instrname[TAILLEOP];
	int hex;
	char type='u'; /* cas de base: type inconnu */
	int i=0;
	long unsigned int rtrn=0;
	FILE* instructFile=fopen(instrFile,"r");
    if(instructFile == NULL){/*test ouverture fichier*/
        perror("erreur a l'ouverture du fichier à lire : il n'existe peut-être pas\n");
        exit(1);
    }
	while(!feof(instructFile) && strcmp(instrname,instr->opcode)!=0){
		fscanf(instructFile,"%s %X %c",&instrname,&hex,&type);
	}
	fclose(instructFile);
	
	if(type=='I'){
		rtrn+=(hex<<26);
		rtrn+=(registerToInt(instr->op1)<<16); /* ajout de rt*/
		rtrn+=(registerToInt(instr->op2)<<21); /* ajout de rs*/
		rtrn+=(immediateToInt(instr->op3));/* ajout de la valeur immédiate*/
	}
	if(type=='R'){
		rtrn=hex;
		rtrn+=(registerToInt(instr->op1)<<11); /* ajout de rd*/
		rtrn+=(registerToInt(instr->op2)<<21); /* ajout de rs*/
		rtrn+=(registerToInt(instr->op3)<<16); /* ajout de rt*/
	}
	if(type=='J'){
		rtrn=(hex<<26);
		rtrn+=(targetToInt(instr->op1));/*ajout de target*/
	}
	return (rtrn);
}

/*
Reçoit un nom de fichier et un nombre
Ecrit le nombre dans le fichier
Ne retourne rien
*/
void ecrit_fichier(char *nomFichier, long unsigned int aEcrire){
	FILE *fichier=fopen(nomFichier,"w");
	if(fichier==NULL){
		perror("l'ouverture du fichier d'écriture a échoué");
		exit(0);
	}
	fprintf(fichier,"%X\n",aEcrire);
	fclose(fichier);
}

/*
Reçoit un fichier à lire
Lit une ligne du fichier
Retourne ce qui a été lu du fichier
*/
char *lis_fichier(FILE *readFile){
	char instr[100];//une instruction sans commentaire ne sera pas plus grande que 99 caractères
	fgets(instr,100,readFile);
	return(instr);
}

/*
Reçoit un fichier où lire et un fichier où écrire
Traduit les instructions du fichier à lire en hexa dans le fichier où écrire
Ne retourne rien
*/
void transformeTotal(char *fichierALire, char *fichierAEcrire){
	char *instr;
	long unsigned int aEcrire;
	instruction *a;
	FILE *readFile=fopen(fichierALire,"r");
    if(readFile == NULL){/*test ouverture fichier*/
        perror("erreur a l'ouverture du fichier à lire : il n'existe peut-être pas\n");
        exit(1);
    }
	while(!feof(readFile)){
        instr=lis_fichier(readFile);
        a = cut_instruction(instr);
        aEcrire = translate_instruction(a,"instructiontohex.txt");
        ecrit_fichier(fichierAEcrire,aEcrire);
	}
	fclose(readFile);
}

