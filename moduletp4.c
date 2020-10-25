#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

/*
myStrlen({}) -> 0
myStrlen({1,2,3}) -> 3
*/
int myStrlen(char T[])
{
    int n=0;
    while(T[n]!='\0')
    {
        n++;
    }
    return(n);
}

/*
myStrcpy({},{2,3,1})->{2,3,1}
myStrcpy({2,3,1},{})->{}
*/
char *myStrcpy(char * Tdest, char * Tsrc)
{
    int i=0;
    while(Tsrc[i]!='\0')
    {
        Tdest[i]=Tsrc[i];
        i++;
    }
    Tdest[i]='\0';
    return(Tdest);
}

/*
affichageEnHexadecimal("GHrdJghH")->47 48 72 64 4a 67 68 48
affichageEnHexadecimal(" ")->20
*/
void affichageEnHexadecimal(char T[])
{
    int i=0;
    printf("%s vaut en hexa : ", T);
    while(T[i]!='\0')
    {
        printf("%x ", T[i]);
        i++;
    }
    printf("\n");
}

/*
affichageEnDecimal("GHrdJghH")->71 72 114 100 74 103 104 72
*/
void affichageEnDecimal(char T[])
{
    int i=0;
    printf("%s vaut en decimal : ", T);
    while(T[i]!='\0')
    {
        printf("%d ", T[i]);
        i++;
    }
    printf("\n");
}

/*
Pour les fonctions suivantes, pour ne pas écraser les tableaux donnes
en entree, on peut declarer un tableau a l'interieur des fonctions 
que l'on retournera.
Pour cela, on affectera les valeurs modifiees du tableau passe en parametre
a notre tableau de sortie.
*/

/*
mettreEnMajuscule("ESISAR")->"ESISAR"
mettreEnMajuscule("esisar")->"ESISAR"
mettreEnMajuscule("esISaR")->"ESISAR"
*/
char * mettreEnMajuscule(char T[])
{
    int i=0;
    while(T[i]!='\0')
    {
        if(T[i]<123 && T[i]>96)
        {
            T[i]=T[i]-32;/*T2[i]=T1[i]-32;*/
        }
        else
        {
            T[i]=T[i];/*T2[i]=T1[i];*/
        }
        i++;
    }
    return(T);/*return(T2);*/
}

/*
mettreEnMajuscule("ESISAR")->"esisar"
mettreEnMajuscule("esisar")->"esisar"
mettreEnMajuscule("esISaR")->"esisar"
*/
char * mettreEnMinuscule(char T[])
{
    int i=0;
    while(T[i]!='\0')
    {
        if(T[i]<91 && T[i]>64)
        {
            T[i]=T[i]+32;/*T2[i]=T1[i]+32;*/
        }
        else
        {
            T[i]=T[i];/*T2[i]=T1[i];*/
        }
        i++;
    }
    return(T);/*return(T2);*/
}

/*
transformerMinMaj("GHrdJghH")->ghRDjGHh
*/
char * transformerMinMaj(char T[])
{
    int i=0;
    while(T[i]!='\0')
    {
        if(T[i]<91 && T[i]>64)
        {
            T[i]=T[i]+32;/*T2[i]=T1[i]+32;*/
        }
        else if(T[i]<123 && T[i]>96)
        {
            T[i]=T[i]-32;/*T2[i]=T1[i]-32;*/
        }
        else
        {
            T[i]=T[i];/*T2[i]=T1[i];*/
        }
        i++;
    }
    return(T);/*return(T2);*/

}

/*
a priori, un mot, meme en allemand ne mesure pas plus de 63 lettres (Rindfleischetikettierungsüberwachungsaufgabenübertragungsgesetz)
*/
/*
retournerMot(" ")->" "
retournerMot("ghRDjGHh")->"hHGjDRhg"
*/
char * retournerMot(char T[])
{
    char tmp[64];
    int n=myStrlen(T);
    int i=0;
    while(T[i]!='\0')
    {
        tmp[i]=T[n-i-1];/*-1 pour enlever \0*/
        i++;
    }
    myStrcpy(T,tmp);
    return(T);
}

/*
Les deux fonctions suivantes considerent que la position de la premiere lettre dans
une chaine est 0
*/
/*
rechercherCaractereG("ghrdjghh", 'g')->0
rechercherCaractereD("GHRDJGHH", 'g')->-1
*/
int rechercherCaractereG(char T[], char a)
{
    int i=0, n=-1;
    while(T[i]!=a && T[i]!='\0')
    {
        i++;
    }
    if(T[i]==a)
    {
        n=i;
    }
    return(n);
}

/*
rechercherCaractereD("ghrdjghh", 'h')->7
rechercherCaractereD("GHRDJGHH", 'h')->-1
*/
int rechercherCaractereD(char T[], char a)
{
    int i,n=-1;
    for(i=0;i<myStrlen(T);i++)
    {
        if(T[i]==a)
        {
            n=i;
        }
    }
    return(n);
}

/*
estPalindrome("ghghabccbaghgh",'4','9')->1
estPalindrome("ghghabccbaghghghgh",'4','9')->1
estPalindrome("ghghabcbaghghghgh",'4','8')->1
estPalindrome("ghghabccbaghghghgh",'5','8')->1
estPalindrome("ghghabccbghghghgh",'5','8')->0
*/
int estPalindrome(char T[], int d, int f)
{
    int res=0, n=myStrlen(T)-1;
    char cmp[100];
    myStrcpy(cmp, T);
    retournerMot(cmp);
    while((T[d]==cmp[n-f]) && d<f)
    {
        d++;
        f--;
    }
    if(d>=f)
    {
        res=1;
    }
    return(res);
}

/*
comparerChaine("totoo","totooi")->-105
comparerChaine("toto","toto")->0
comparerChaine("toto","titi")->6
*/
int comparerChaine(char T1[], char T2[])
{
    int i, res;
    while(T1[i]==T2[i] && T1[i]!='\0' && T2[i]!='\0')
    {
        i++;
    }
    if(T1[i]=='\0' && T2[i]=='\0')
    {
        res=0;
    }
    else if(T1[i]=='\0' || T1[i]<T2[i])
    {
        res=T1[i]-T2[i];
    }
    else if(T2[i]=='\0' || T1[i]>T2[i])
    {
        res=T1[i]-T2[i];
    }
    return(res);
}

/*
entiers en ascii [0,9] -> [48,57]
*/
/*
valeurDecimale("")->0
valeurDecimale("2546")->2546 (ou -2546)
*/
long int valeurDecimale(char T1[]){
	int lengh= myStrlen(T1);
	long int result =0;
	int i;
	if(T1[0]=='-'){
		
		for(i=1;i<lengh;i++){
			result= result+pow(10,lengh-i-1)*((T1[i])-48);
		}
		result=-result;
	
	}
	else{
		for(i=0;i<lengh;i++){
			result= result+pow(10,lengh-i-1)*((T1[i])-48);
		}
	}
	return(result);
}

void retournerChaine(char T1[]){
	int n = myStrlen(T1);
	char T2[n];
	int i = 0;

	for(i=0;i<n;i++){
		T2[i]=T1[i];
	}
	for(i=0;i<n;i++){
		T1[i]=T2[n-i-1];
	}
	
}


/*
intVersChaine(2546)->"2546"
intVersChaine(-2546)->"-2546"
*/
void intVersChaine(int nombre, char T1[]){
	int i=0;
	int pos=1;
	char car;
	if(nombre<0) {
		pos=-1;
	}
	nombre = nombre * pos;
	while(nombre!= 0){
		car = (nombre%10)+48;
		T1[i]=car;
		i++;
		nombre = nombre/10;
	}
	if(pos==-1){
		T1[i]='-';
	}
	retournerChaine(T1);
	
}


















