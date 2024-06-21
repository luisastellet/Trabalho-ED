// #include "TABM.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct arvbm{
    int folha;
    int nchaves;
    char* prox;
    char** chaves; //no max 284 chaves
    char** filhos; //arq de 0000 até 9999
}TABM;
<<<<<<< Updated upstream


char * TABM_cria(int t, int *cont){
    char * filename = (char*)malloc(sizeof(char)*25);
    sprintf(filename, "Arquivos/%04d.bin", (*cont));
=======
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//          CRIA O ARQUIVO "VAZIO"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TABM_cria(int t, int *cont){
    char * filename = (char*)malloc(sizeof(char)*21);
    sprintf(filename, "arq%d.bin", (*cont));
>>>>>>> Stashed changes
    FILE * fp = fopen(filename, "wb");
    if(!fp) exit(1);
    TABM novo;
    novo.folha = 1;
    novo.nchaves = 0;
    novo.prox = (char*)malloc(sizeof(char)*7);
    char temp[] = "Miguel";
    strcpy(novo.prox, "MIGUEL");
    novo.chaves = (char**)malloc(sizeof(char*)*((t*2)-1)); 
    for(int i = 0; i < ((t*2)-1); i++) novo.chaves[i] = malloc(sizeof(char)*6);
    for(int i = 0; i < (t*2)-1; i++) strcpy(novo.chaves[i],"Bebel");
    novo.filhos=(char**)malloc(sizeof(char*)*t*2);
    for(int i = 0; i < (t*2); i++) novo.filhos[i] = malloc(sizeof(char)*6);
    for(int i = 0; i < (t*2); i++) strcpy(novo.filhos[i],"Luisa");
    fwrite(&novo, sizeof(TABM), 1, fp);
    fclose(fp);
    (*cont)++;
    return filename;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//          PRINTAR CONTEÚDO DO ARQUIVO BINÁRIO
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void printa_arqb(char* entrada){
    FILE* fp = fopen(entrada, "rb");
    //TABM* novo = (TABM*)malloc(sizeof(TABM));
    TABM novo;
    fread(&novo,sizeof(TABM),1,fp);
    printf("Folha: %d\n", novo.folha);
    printf("N Chaves: %d\n", novo.nchaves);
    for (int i = 0; i < 4; i++) printf("%s\n",novo.filhos[i]);
    for (int i = 0; i < 3; i++) printf("%s\n",novo.chaves[i]);
    printf("Proximo: %s\n", novo.prox);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TABM * inicializa(void){
    return NULL;
} 


int main(void){
    int cont = 0;
    int t;
    char filename[25];
    printf("Insira o valor de t para a construcao da arvore: ");
    scanf("%d", &t);
    strcpy(filename, TABM_cria(t,&cont));
    printa_arqb(filename);

    return 0;
}

// TABM *TABM_busca(TABM *a, int mat);
// TABM *TABM_insere(TABM *T, int mat, int t);
// TABM* TABM_retira(TABM* arv, int k, int t);
// void TABM_libera(TABM *a);
// void TABM_imprime(TABM *a);
// void TABM_imprime_chaves(TABM *a);