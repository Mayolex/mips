#ifndef INTERPRETE_H
#define INTERPRETE_H
#include "interpreteur.h"


/*
To clear buffer
*/
void viderBuffer()
{
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}

void lit_ligne(FILE *fichier,int offset_ligne){
    int i;
    char before[100];
    rewind(fichier);
    for(i=0;i<offset_ligne/4 -1;i++){
        fgets(before,100,fichier);
    }
    fgets(before,100,fichier);
    printf("%s", before);
}




int step_by_step(memory_struct *mem, register_struct *reg, char *fichier_instr){
    int ans=-1,quit=0;
    char *instr;
    FILE *fichier=fopen(fichier_instr,"r");
    if(fichier==NULL){
        perror("erreur d'ouverture du fichier, il n'existe peut-être pas");
        exit(1);
    }
    while(ans!=1 && quit!=1){
        printf("1.Next step 2.Show memory 3.Show registers 4.Show instruction 5.Exit\n");
        scanf("%d",&ans);
        viderBuffer();
        if(ans<=0 || ans>=6){
            printf("mauvais paramètre\n");
        }
        switch(ans){
            case 1:
                break;
            case 2:
                printMemory(mem);
                break;
            case 3:
                printRegisters(reg);
                break;
            case 4:
                lit_ligne(fichier,reg->registers[GP]);
                break;
            case 5:
                quit=1;
                break;
        }
    }
    return quit;
}





void interprete(char fichier[],int step){
    int quit=0;
    numinstruction *instruct;
    memory_struct mem;
    register_struct reg;
    wr(&reg,GP,0);
    init_mem(&mem);
    init_reg(&reg);

    loadmemory(&mem,fichier);

    while(rw(&mem,reg.registers[GP])!=0 && quit!=1){
        instruct=readinstr((&mem,reg.registers[GP]),&mem);
        operation(instruct,&reg,&mem);
        wr(&reg,GP,reg.registers[GP]+4);
        if(step==1){
            quit=step_by_step(&mem,&reg,fichier);
        }
    }
    if(step!=1){
        printMemory(&mem);
        printRegisters(&reg);
    }
}
#endif