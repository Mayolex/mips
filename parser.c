#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAILLEOP 10




char** cut_instruction(char  string[],char rtrn[][]){
	int i=0,n=0;
	int pos=0;
	
	
	while(string[i]!='\0' || string[i]!='#'){
		if(string[i]!=' '){
				
			switch(pos){
				case 0: 
					rtrn[0][i-n]=string[i];
					break;
				case 1: 
					rtrn[1][i-n]=string[i];
					break;
				case 2:
					rtrn[2][i-n]=string[i];					
					break;
				case 3: 
					rtrn[3][i-n]=string[i];
					break;
				default:
					break;
			}
			
		}
		else{
			n+=i;
			pos++;
		}
		i++;
	}
	return(rtrn);
}
int main(){
	char rtrn[4][TAILLEOP]={{""},{""},{""},{""}};
	
	cut_instruction("addi ,char rtrn[][])
	return 0;
}
