#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
	return(rtrn);
}
int main(){
	
	instruction *a=cut_instruction("addi 1552 $2 3#lol");
	printf("%s\n%s\n%s\n%s\n",a->opcode,a->op1,a->op2,a->op3);
	return 0;
}
