#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "parser.h"
#include "moduletp4.h"



instruction * cut_instruction(char  string[]){
	int i=0,n=0;
	int pos=0;
	instruction *rtrn = malloc(sizeof(instruction));
	i=0;
	while(string[i]!='\0' && string[i]!='#'){
		if(string[i]!=' ' && string[i]!=','){
			switch(pos){
				case 0: 
					rtrn->opcode[i-n]=string[i];
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
int registerToInt(char reg[]){
	int rtrn=0;
	if(reg[0]=='$'){
		rtrn=valeurDecimale(&reg[1]);
	}
	return(rtrn&31);
}
int immediateToInt(char im[]){
	int rtrn=0;
	rtrn=valeurDecimale(im)&65535;/* on s'assure de respecter les 16 bit*/
	printf("\nhexa :%x \n",rtrn);
	return(rtrn);
}
long int targetToInt(char targ[]){
	int rtrn=0;
	rtrn=(valeurDecimale(targ)&67108863);
	return(rtrn);
}

void translate_instruction(instruction * instr){
	char instrname[TAILLEOP];
	int hex;
	char type='u'; /* cas de base: type inconnu */
	int i=0;
	long unsigned int rtrn=0;
	FILE * instructionFile=fopen("instructiontohex.txt","r");
	if(instructionFile == NULL){
		perror("erreur a l'ouverture du fichier liste des instructions\n");
		exit(1);
	}


	while(!feof(instructionFile) && strcmp(instrname,instr->opcode)!=0){
		fscanf(instructionFile,"%s %X %c",&instrname,&hex,&type);
	}
	printf("%s %X %c\n",instrname, hex,type);
	fclose(instructionFile);
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
		printf("rtrn:%X",rtrn);
}


int main(){
	
	instruction *a=cut_instruction("ADDI $12 $18 28 #lol");
	printf("%s\n%s\n%s\n%s\nto int: %d\n",a->opcode,a->op1,a->op2,a->op3,registerToInt(a->op1));
	translate_instruction(a);
	return 0;
}
