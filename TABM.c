// #include "TABM.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct arvbm{
    int folha;
    int nchaves;
    char* prox;
    char** chaves;
    char** filhos;
}TABM;


void TABM_cria(int t, int *cont){
    char * filename = (char*)malloc(sizeof(char)*21);
    sprintf(filename, "arq%d.bin", (*cont));
    FILE * fp = fopen(filename, "wb");
    if(!fp) exit(1);
    TABM* novo = (TABM*)malloc(sizeof(TABM));
    novo->folha = 1;
    novo->nchaves = 0;
    novo->prox = (char*)malloc(sizeof(char)*8);
    char temp[] = "Miguel";
    strcpy(novo->prox,temp);
    novo->chaves = (char**)malloc(sizeof(char*)*((t*2)-1));
    for(int i = 0; i < ((t*2)-1); i++) 
        novo->chaves[i] = malloc(sizeof(char)*8);
    for(int i = 0; i < ((t*2)-1); i++) strcpy(novo->chaves[i],"Bebel");


    novo->filhos=(char**)malloc(sizeof(char*)*t*2);
    for(int i = 0; i < (t*2); i++) novo->filhos[i] = malloc(sizeof(char)*8);

    for(int i = 0; i < (t*2); i++) strcpy(novo->filhos[i],"Luisa");
    fwrite(novo, sizeof(TABM), 1, fp);
    fclose(fp);
    (*cont)++;
    return;
}

void printa_arqb(char* entrada){
    FILE* fp = fopen(entrada, "rb");
    TABM* novo = (TABM*)malloc(sizeof(TABM));
    fread(novo,sizeof(TABM),1,fp);
    printf("Folha: %d\n", novo->folha);
    printf("N Chaves: %d\n", novo->nchaves);
    for (int i = 0; i < 4; i++) printf("%s\n",novo->filhos[i]);
    for (int i = 0; i < 3; i++) printf("%s\n",novo->chaves[i]);
    printf("Proximo: %s\n", novo->prox);
}




TABM * inicializa(void){
    return NULL;
} 


int main(void){
    int cont = 0;
    int t;
    printf("Insira o valor de t para a construcao da arvore: ");
    scanf("%d", &t);
    TABM_cria(t,&cont);
    printa_arqb("arq0.bin");


    return 0;
}

// TABM *TABM_busca(TABM *a, int mat);
// TABM *TABM_insere(TABM *T, int mat, int t);
// TABM* TABM_retira(TABM* arv, int k, int t);
// void TABM_libera(TABM *a);
// void TABM_imprime(TABM *a);
// void TABM_imprime_chaves(TABM *a);
