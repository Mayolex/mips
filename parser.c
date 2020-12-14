#include "parser.h"



/*
Reçoit une instruction en chaîne de caractères
Sépare l'opcode et les opérandes
Retourne les chaînes de caractèeres contenant l'opcode et les opérandes dans un type instruction
*/
instruction * cut_instruction(char  string[]){
	int i=0,n=0,pos=0;
	instruction *rtrn = malloc(sizeof(instruction));
	while(string[i]!='\0' && string[i]!='#' && string[i]!='\n' && string[i]!=')'){//conditions d'arrêt de lecture de la ligne
		if(string[i]!=' ' && string[i]!=',' && string[i]!='('){//séparateurs
			switch(pos){//on sépare les éléments de l'instruction
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
	while(!feof(instructFile) && strcmp(instrname,instr->opcode)!=0){//on cherche le bon opcode dans la table de traduction
		fscanf(instructFile,"%s %X %c %d",&instrname,&hex,&type);
	}
	
	//on attribue l'espace de chaque opérande dans l'instruction en fonction de son type
	if(type=='I'){
		rtrn+=(hex<<26);
		rtrn+=(registerToInt(instr->op1)<<16); // ajout de rt
		rtrn+=(registerToInt(instr->op2)<<21); // ajout de rs
		rtrn+=(immediateToInt(instr->op3));// ajout de la valeur immédiate
	}
	if(type=='R'){
		rtrn=hex;
		rtrn+=(registerToInt(instr->op1)<<11); // ajout de rd
		rtrn+=(registerToInt(instr->op2)<<21); // ajout de rs
		rtrn+=(registerToInt(instr->op3)<<16); // ajout de rt
	}
	if(type=='J'){
		rtrn=(hex<<26);
		rtrn+=(targetToInt(instr->op1));//ajout de target
	}
	if(type=='M'){
		rtrn+=(hex<<26);
		rtrn+=(registerToInt(instr->op1)<<16); // ajout de rt
		rtrn+=(immediateToInt(instr->op2));// ajout offset
		rtrn+=(registerToInt(instr->op3)<<21); // ajout de base
	}
	if(type=='D'){
		rtrn=hex;
		rtrn+=(registerToInt(instr->op1)<<21); // ajout de rs
		rtrn+=(registerToInt(instr->op2)<<16); // ajout de rt
	}
	if(type=='L'){
		rtrn=(hex<<26);
		rtrn+=(registerToInt(instr->op1)<<16); // ajout de rt
		rtrn+=(immediateToInt(instr->op2));// ajout de la valeur immédiate
	}
	if(type=='F'){
		rtrn=hex;
		rtrn+=(registerToInt(instr->op1)<<11); // ajout de rd
	}
	if(type=='S'){
		rtrn=hex;
		rtrn+=(registerToInt(instr->op1)<<11); // ajout de rd
		rtrn+=(registerToInt(instr->op2)<<16);
		rtrn+=(immediateToInt(instr->op3)<<6);
		rtrn+=1<<21;
	}
	return (rtrn);
}

/*
Reçoit un nom de fichier et un nombre
Ecrit le nombre dans le fichier
Ne retourne rien
*/
void ecrit_fichier(char *nomFichier, long unsigned int *instrliste,int max){
	int i=0;
	FILE *fichier=fopen(nomFichier,"a");
	if(fichier==NULL){
		perror("l'ouverture du fichier d'écriture a échoué");
		exit(0);
	}
	while(i<max){
		fprintf(fichier,"%X\n",instrliste[i]);//on écrit toutes les instructions traduites stockées dans le tableau
		i++;
	}
	fclose(fichier);
}

/*
Reçoit un fichier à lire et une chaîne de caractère où stocker
Lit une ligne du fichier
Retourne ce qui a été lu du fichier
*/
void lit_fichier(FILE *readFile, char *instr){
	fgets(instr,100,readFile);//on lit le minimum entre 100 caractères et une ligne du fichier
}

/*
Reçoit une chaîne de caractères
Supprime les espaces ou retours à la ligne dans le début de la chaîne
Renvoit la chaîne modifiée
*/
char *mange_blanc(char *instr){
	int i=0;
	while(instr[0]==' ' || instr[0]=='\n'){
		while(instr[i]!='\0'){
			instr[i]=instr[i+1];//on décale toute la chaîne en avant
			i++;
		}
		instr[i]='\0';
	}
	return(instr);
}

/*
Reçoit un fichier où lire et un fichier où écrire
Traduit les instructions du fichier à lire en hexa dans le fichier où écrire
Ne retourne rien
*/
void transformeTotal(char *fichierALire, char *fichierAEcrire){
	int i=0;
	long unsigned int instrliste[100];
	char instr[100];
	long unsigned int aEcrire;
	instruction *a;
	remove(fichierAEcrire);
	FILE *readFile=fopen(fichierALire,"r");
    if(readFile == NULL){/*test ouverture fichier*/
        perror("erreur a l'ouverture du fichier à lire : il n'existe peut-être pas\n");
        exit(1);
    }

	//on effectue les étapes de la transformation dans l'ordre
	while(!feof(readFile)){
        lit_fichier(readFile,instr);
		mange_blanc(instr);
		mettreEnMajuscule(instr);
        a = cut_instruction(instr);
        aEcrire = translate_instruction(a,"instructiontohex.txt");
		instrliste[i]=aEcrire;
		i++;
	}
	fclose(readFile);
	ecrit_fichier(fichierAEcrire,instrliste,i);
	
}

void loadmemory(memory_struct *mem,char *fichierALire){
	int i=0;
	long unsigned int instrliste[100];
	char instr[100];
	long unsigned int aEcrire;
	instruction *a;
    FILE *readFile=fopen(fichierALire,"r");
    if(readFile == NULL){/*test ouverture fichier*/
        perror("erreur a l'ouverture du fichier à lire : il n'existe peut-être pas\n");
        exit(1);
    }
    while(!feof(readFile)){
        lit_fichier(readFile,instr);
		mange_blanc(instr);
		mettreEnMajuscule(instr);
        a = cut_instruction(instr);
        aEcrire = translate_instruction(a,"instructiontohex.txt");
		swi(mem,4*i,aEcrire);
		i++;
	}

}