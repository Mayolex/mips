#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "parser.h"




instruction * cut_instruction(char  string[]){
	int i=0,n=0;
	int pos=0;
	instruction *rtrn = malloc(sizeof(instruction));
	i=0;
	while(string[i]!='\0' && string[i]!='#'){
		if(string[i]!=' '){
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

void find_instruction(instruction * instr){
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
		printf("%d %s %s\n\n",strcmp(instrname,instr->opcode),instrname,instr->opcode);
		fscanf(instructionFile,"%s %X %c",&instrname,&hex,&type);
	}
	printf("%s %X %c\n",instrname, hex,type);
	fclose(instructionFile);
	if(type=='I'){
		rtrn=rtrn+(hex<<26);
	}
	if(type=='R'){
		rtrn=hex;
		printf("%X",rtrn);
	}
}


int main(){
	
	instruction *a=cut_instruction("ADD 1552 $2 3#lol");
	/*printf("%s\n%s\n%s\n%s\n",a->opcode,a->op1,a->op2,a->op3);*/
	find_instruction(a);
	return 0;
}
