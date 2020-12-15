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
    printf("instruction entrée : %s", before);
    printf("traduction hexadécimale : %lu\n\n", translate_instruction(cut_instruction(before),"instructiontohex.txt"));
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

void interactif(){
    memory_struct mem_vol;
    memory_struct mem;
    register_struct reg;
    init_mem(&mem);
    init_mem(&mem_vol);
    init_reg(&reg);
    int quit=0;
    char instruct[100];
    long unsigned int instr_hex;
    instruction *instr;
    numinstruction *numinstr;
    while(quit!=1){
        printf("donnez votre instruction (EXIT pour quitter) : ");
        fgets(instruct,100,stdin);
        if(strcmp(instruct,"EXIT\n")==0){
            quit=1;
        }
        else{
            mange_blanc(instruct);
            mettreEnMajuscule(instruct);
            instr=cut_instruction(instruct);
            if(strcmp(instr->opcode,"ADD")
                && strcmp(instr->opcode,"ADDI")
                && strcmp(instr->opcode,"AND")
                && strcmp(instr->opcode,"DIV")
                && strcmp(instr->opcode,"LUI")
                && strcmp(instr->opcode,"LW")
                && strcmp(instr->opcode,"MFHI")
                && strcmp(instr->opcode,"MFLO")
                && strcmp(instr->opcode,"MULT")
                && strcmp(instr->opcode,"NOP")
                && strcmp(instr->opcode,"OR")
                && strcmp(instr->opcode,"XOR")
                && strcmp(instr->opcode,"ROTR")
                && strcmp(instr->opcode,"SYSCALL")
                && strcmp(instr->opcode,"SLL")
                && strcmp(instr->opcode,"SLT")
                && strcmp(instr->opcode,"SRL")
                && strcmp(instr->opcode,"SUB")
                && strcmp(instr->opcode,"SW")){
                printf("instruction incorrecte\n");
            }
            else{
                instr_hex=translate_instruction(instr,"instructiontohex.txt");
                swi(&mem_vol,0,instr_hex);
                numinstr=readinstr(0,&mem_vol);
                operation(numinstr,&reg,&mem);

                printMemory(&mem);
                printRegisters(&reg);
            }
        }
    }
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
        instruct=readinstr(reg.registers[GP],&mem);
        operation(instruct,&reg,&mem);
        wr(&reg,GP,reg.registers[GP]+4);
        if(step==1){
            quit=step_by_step(&mem,&reg,fichier);
        }
    }
    printMemory(&mem);
    printRegisters(&reg);
}
#endif