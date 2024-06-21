// #include "TABM.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct jogador{
    int id;
    int num_camisa;
    char posicao[3];
    char nome[31];
    int dia;
    char mes[11];
    int ano;
    int idade;
    int part_sel;
    int gol_sel;
    char pais_time[21];
    char time[31];
    int capitao; // 1 ou 0 
}TJ;

typedef struct arvbm{
    int folha;
    int nchaves;
    char* prox;
    TJ* chaves; //vetor de structs jogador
    char** filhos; //arq de 0000 até 9999
}TABM;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//          LÊ DADOS PARA ARQUIVO
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void le_dados(char * arquivo){
    FILE * fp = fopen(arquivo, "r");
    if(!fp) exit(1);
    TJ jogador;
    char tmp[21];
    while(fscanf(fp, "%s", tmp) == 1){ //lendo por seleção
        while(fscanf(fp, "%d/%d/%2s/%30[^/]/%d %10s %d (aged %d)/%d/%d/%20[^/]/%30[^\n]", 
            &jogador.id, &jogador.num_camisa, jogador.posicao, jogador.nome, 
            &jogador.dia, jogador.mes, &jogador.ano, &jogador.idade, &jogador.part_sel, 
            &jogador.gol_sel, jogador.pais_time, jogador.time) == 12){ //lendo por jogador

                if(strstr(jogador.nome, "(captain)")) jogador.capitao = 1;
                else jogador.capitao = 0;
                //printf("%d %s %d %d %s\n", jogador.dia, jogador.mes, jogador.ano, jogador.idade, jogador.time);
                //a struct jogador já está com as informações

                //TABM_insere(TJ)
            }
    }
    return;
}

/*
dentro da insere, tenta abrir o arquivo "raiz", se não existir, cria ele, 
senão lê para fazer as inserções
*/

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//          CRIA O ARQUIVO "VAZIO"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
char * TABM_cria(int t, int *cont){
    char * filename = (char*)malloc(sizeof(char)*21);
    sprintf(filename, "Arquivos/%04d.bin", (*cont));
    FILE * fp = fopen(filename, "wb");
    if(!fp) exit(1);
    TABM novo;
    TJ jogador;
    novo.folha = 1;
    novo.nchaves = 0;
    novo.prox = (char*)malloc(sizeof(char)*7);
    char temp[] = "Prox";
    strcpy(novo.prox, "Prox");
    novo.chaves = (TJ*)malloc(sizeof(TJ)*((t*2)-1));
    for(int i = 0; i < (t*2)-1; i++) strcpy(novo.chaves[i].nome,"Chave");
    novo.filhos=(char**)malloc(sizeof(char*)*t*2);
    for(int i = 0; i < (t*2); i++) novo.filhos[i] = malloc(sizeof(char)*6);
    for(int i = 0; i < (t*2); i++) strcpy(novo.filhos[i],"Filho");
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
    TABM novo;
    fread(&novo,sizeof(TABM),1,fp);
    printf("Folha: %d\n", novo.folha);
    printf("N Chaves: %d\n", novo.nchaves);
    printf("Proximo: %s\n", novo.prox);
    for (int i = 0; i < 3; i++) printf("%s\n",novo.chaves[i].nome);
    for (int i = 0; i < 4; i++) printf("%s\n",novo.filhos[i]);
    return;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TABM * inicializa(void){
    return NULL;
} 


int main(void){
    int cont = 0;
    int t;
    char filename[25], filename1[25];
    //le_dados("EURO.txt");
    printf("Insira o valor de t para a construcao da arvore: ");
    scanf("%d", &t);
    strcpy(filename, TABM_cria(t,&cont));
    printa_arqb(filename);
    strcpy(filename1, TABM_cria(t,&cont));
    printa_arqb(filename1);

    return 0;
}
