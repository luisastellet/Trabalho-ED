#include "TABM.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//          LÊ DADOS PARA ARQUIVO
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void le_dados(char * arquivo, char ** raiz, int t){
    int cont = 1;
    FILE * fp = fopen(arquivo, "r");
    if(!fp) exit(1);
    TJ jogador;
    //int contar = 5;
    char tmp[100];
    while(fscanf(fp, "%s", tmp) == 1){ //lendo por seleção
        while(fscanf(fp, "%d/%d/%2s/%30[^/]/%d %10s %d (aged %d)/%d/%d/%20[^/]/%30[^\n]", 
            &jogador.id, &jogador.num_camisa, jogador.posicao, jogador.nome, 
            &jogador.dia, jogador.mes, &jogador.ano, &jogador.idade, &jogador.part_sel, 
            &jogador.gol_sel, jogador.pais_time, jogador.time) == 12){ //lendo por jogador

                if(strstr(jogador.nome, "(captain)")) jogador.capitao = 1;
                else jogador.capitao = 0;
                //printf("%d %s %d %d %s\n", jogador.dia, jogador.mes, jogador.ano, jogador.idade, jogador.time);
                //a struct jogador já está com as informações
                TABM_insere(jogador, t, raiz, &cont);
            //contar --;
            }
    }
    fclose(fp);
    return;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//          INSERIR NÓ NA ÁRVORE
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TABM_insere(TJ jogador, int t, char ** raiz, int * cont){
    FILE * fp = fopen(*raiz, "rb+");
    //se não tem arvore ainda
    if(!fp){
        TABM aux;
        int nchaves = 1;
        strcpy(*raiz, TABM_cria(t, cont));
        FILE * fraiz = fopen(*raiz, "rb+");
        if(!fraiz) exit(1);
        fread(&aux,sizeof(TABM),1,fraiz);
        aux.nchaves = 1;
        aux.chaves[0].id = jogador.id;
        aux.chaves[0].num_camisa = jogador.num_camisa;
        strcpy(aux.chaves[0].posicao, jogador.posicao);
        strcpy(aux.chaves[0].nome,jogador.nome);
        aux.chaves[0].dia = jogador.dia;
        strcpy(aux.chaves[0].mes,jogador.mes);
        aux.chaves[0].ano = jogador.ano;
        aux.chaves[0].idade = jogador.idade;
        aux.chaves[0].part_sel = jogador.part_sel;
        aux.chaves[0].gol_sel = jogador.gol_sel;
        strcpy(aux.chaves[0].pais_time,jogador.pais_time);
        strcpy(aux.chaves[0].time,jogador.time);
        aux.chaves[0].capitao = jogador.capitao;

        fwrite(&aux,sizeof(TABM),1,fraiz);
        printa_arqb(*raiz);
        fclose(fraiz);
        return;
    }
    fseek(fp, sizeof(int), SEEK_CUR);
    int qtd_chaves;
    fread(&qtd_chaves, sizeof(int), 1 , fp);
    if(qtd_chaves == (2*t)-1){
        char S_arq[25];
        strcpy(S_arq, TABM_cria(t, cont));
        FILE *fs = fopen(S_arq, "rb");
        if(!fs) exit(1);
        TABM S;
        fread(&S, sizeof(TABM),1,fs);
        S.nchaves = 0;
        S.folha = 0;
        strcpy(S.filhos[0], *raiz);
        fwrite(&S, sizeof(TABM),1,fs);
        printa_arqb(S_arq);
        fclose(fs);
        //strcpy(S_arq, divisao(S_arq, 1, raiz, t)); //raiz ta sendo o T dela
        //strcpy(S_arq, insere_nao_completo(S_arq, jogador, t));
        //aqui tem q ver a relação dos filhos com os pais nos arquivos
        return;
    }
    //strcpy(*raiz, insere_nao_completo(raiz, jogador, t));
    fclose(fp);
    return;
}



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
    novo.prox = (char*)malloc(sizeof(char)*5);
    char temp[] = "Prox";
    strcpy(novo.prox, "Prox");
    novo.chaves = (TJ*)malloc(sizeof(TJ)*((t*2)-1));
    for(int i = 0; i < (t*2)-1; i++) strcpy(novo.chaves[i].nome,"Chave");
    novo.filhos=(char**)malloc(sizeof(char*)*t*2);
    for(int i = 0; i < (t*2); i++) novo.filhos[i] = malloc(sizeof(char)*5);
    for(int i = 0; i < (t*2); i++) strcpy(novo.filhos[i],"Filh");
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
    fread(&novo, sizeof(TABM),1,fp);
    printf("Folha: %d\n", novo.folha);
    printf("N Chaves: %d\n", novo.nchaves);
    printf("Proximo: %s\n", novo.prox);
    for (int i = 0; i < 3; i++) printf("%d/%d/%s/%s/%d %s %d (aged %d)/%d/%d/%s/%s\n", 
            novo.chaves[i].id, novo.chaves[i].num_camisa, novo.chaves[i].posicao, novo.chaves[i].nome, 
            novo.chaves[i].dia, novo.chaves[i].mes, novo.chaves[i].ano, novo.chaves[i].idade, novo.chaves[i].part_sel, 
            novo.chaves[i].gol_sel, novo.chaves[i].pais_time, novo.chaves[i].time);
    for (int i = 0; i < 4; i++) printf("%s\n",novo.filhos[i]);
    fclose(fp);
    return;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//          MAIN
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(void){
    int t;
    char * raiz = (char*)malloc(sizeof(char)*5);
    char filename[25];
    printf("Insira o valor de t para a construcao da arvore: ");
    scanf("%d", &t);
    le_dados("EURO.txt", &raiz, t);
    return 0;
}


/*
dentro da insere, tenta abrir o arquivo "raiz", se não existir, cria ele, 
senão lê para fazer as inserções
*/
