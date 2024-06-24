#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TABM.h"


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//          LIBERA NÓ NA MEMÓRIA PRINCIPAL
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TABM_libera_no(TABM * no){
    int i;
    for(i=0; i<=no->nchaves; i++) free(no->filhos[i]);
    free(no->filhos);
    free(no->chaves);
    free(no->prox);
    free(no);
}



TABM *TABM_cria_no(int t){
    TABM* novo = (TABM*)malloc(sizeof(TABM));
    novo->nchaves = 0;
    novo->folha = 1;
    novo->prox = (char*)malloc(sizeof(char)*30);
    novo->chaves = (TJ*)malloc(sizeof(TJ)*((t*2)-1));
    novo->filhos=(char**)malloc(sizeof(char*)*t*2);
    for(int i = 0; i < (t*2); i++) novo->filhos[i] = malloc(sizeof(char)*30);
    return novo;
}

// TABM * TABM_preenche(TJ * jogador, int t, TABM * T){
//     T->nchaves = 1;
//     T->chaves[0].id = jogador->id;
//     T->chaves[0].num_camisa = jogador->num_camisa;
//     strcpy(T->chaves[0].posicao, jogador->posicao);
//     strcpy(T->chaves[0].nome, jogador->nome);
//     T->chaves[0].dia = jogador->dia;
//     strcpy(T->chaves[0].mes, jogador->mes);
//     T->chaves[0].ano = jogador->ano;
//     T->chaves[0].idade = jogador->idade;
//     T->chaves[0].part_sel = jogador->part_sel;
//     T->chaves[0].gol_sel = jogador->gol_sel;
//     strcpy(T->chaves[0].pais_time, jogador->pais_time);
//     strcpy(T->chaves[0].time, jogador->time);
//     T->chaves[0].capitao = jogador->capitao;

//     return T;
// }


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//          FUNÇÃO DE DIVIDIR
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TABM *divisao(TABM *S, int i, TABM* T, int t, int * cont){
    TABM *z = TABM_cria_no(t);
    char z_arq[30];
    strcpy(z_arq,TABM_cria(t, cont));
    z->folha = T->folha;
    int j;
    if(!T->folha){
    z->nchaves = t-1;
    for(j=0;j<t-1;j++) z->chaves[j] = T->chaves[j+t];
    for(j=0;j<t;j++){
        strcpy(z->filhos[j],T->filhos[j+t]);
        strcpy(T->filhos[j+t],"NULL");
    }
    }
    else {
    z->nchaves = t; //z possuirá uma chave a mais que T se for folha
    for(j=0;j < t;j++) z->chaves[j] = T->chaves[j+t-1];//Caso em que T é folha, temos q passar a info para o nó da direita
    strcpy(z->prox,T->prox); 
    strcpy(T->prox, z_arq);
    }
    T->nchaves = t-1;
    for(j=S->nchaves; j>=i; j--) strcpy(S->filhos[j+1],S->filhos[j]);
    strcpy(S->filhos[i],z_arq);
    for(j=S->nchaves; j>=i; j--) S->chaves[j] = S->chaves[j-1];
    S->chaves[i-1] = T->chaves[t-1];
    S->nchaves++;
    return S;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//          INSERE NO NÓ NÃO COMPLETO
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TABM *insere_nao_completo(TABM *S, TJ * jogador, int t, int * cont){
    int i = S->nchaves-1;
    
    if(S->folha){
        while((i>=0) && (jogador->id < S->chaves[i].id)){
            S->chaves[i+1] = S->chaves[i];
            i--;
        }
        S->chaves[i+1] = *jogador;
        S->nchaves++;
        return S;
    }
    while((i>=0) && (jogador->id < S->chaves[i].id)) i--;
    i++;

    FILE* fp = fopen(S->filhos[i],"rb");
    TABM* S_filho = TABM_cria_no(t);
    fread(S_filho,sizeof(TABM),1,fp);

    if(S_filho->nchaves == ((2*t)-1)){
        S = divisao(S, (i+1), S_filho, t, cont);
        if(jogador->id > S->chaves[i].id) i++;
        fwrite(S,sizeof(TABM),1,fp);
        
    }
    fclose(fp);

    fp = fopen(S->filhos[i],"rb");
    S_filho = TABM_cria_no(t);
    fread(S_filho,sizeof(TABM),1,fp);
    S_filho = insere_nao_completo(S_filho, jogador, t, cont);
    fwrite(S_filho,sizeof(TABM),1,fp);
    fclose(fp);
    TABM_libera_no(S_filho);
    return S;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//          INSERIR NÓ NA ÁRVORE
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
char* TABM_insere(TJ *jogador, int t, char ** raiz, int * cont){
    FILE * fp = fopen(*raiz, "rb+");
    //se não tem arvore ainda
    if(!fp){
        strcpy(*raiz, TABM_cria(t, cont));// Esse cara é o nosso "retorno", visto que temos uma variável raiz para controlar qual o nó do topo
        FILE * fraiz = fopen(*raiz, "rb+");
        if(!fraiz) exit(1);
        TABM *T = TABM_cria_no(t);
        fread(T,sizeof(TABM),1,fraiz);
        T->chaves[0] = *jogador;
        T->nchaves = 1;
        rewind(fraiz);
        fwrite(T, sizeof(TABM), 1, fraiz);
        //printa_arqb(*raiz);
        TABM_libera_no(T);
        fclose(fraiz);
        return *raiz;
    }
    fclose(fp);

    fp = fopen(*raiz, "rb+");
    if(!fp) exit (1);
    printa_arqb(*raiz);
    TABM *T = TABM_cria_no(t);
    rewind(fp);
    fread(T,sizeof(TABM),1,fp);

    if(T->nchaves == (2*t)-1){ //tá lotado
        char * S_arq = (char*)malloc(sizeof(char)*30);
        strcpy(S_arq, TABM_cria(t, cont));
        FILE *fs = fopen(S_arq, "rb");
        if(!fs) exit(1);
        TABM* S = (TABM*)malloc(sizeof(TABM));
        fread(S, sizeof(TABM),1,fs);
        S->nchaves = 0;
        S->folha = 0;
        strcpy(S->filhos[0],(*raiz));
        S = divisao(S,1,T,t, cont);
        S = insere_nao_completo(S, jogador, t, cont);
        fwrite(S, sizeof(TABM),1,fs);
        fwrite(T,sizeof(TABM),1,fp);
        printa_arqb(*raiz);
        printa_arqb(S_arq);
        TABM_libera_no(T);
        TABM_libera_no(S);
        fclose(fp);
        fclose(fs);
        return S_arq;
    }

    T = insere_nao_completo(T, jogador, t,cont);
    fwrite(T,sizeof(TABM),1,fp);
    fclose(fp);
    TABM_libera_no(T);
    printa_arqb(*raiz); 
    return *raiz;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//          CRIA O ARQUIVO "VAZIO"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
char * TABM_cria(int t, int *cont){
    char * filename = (char*)malloc(sizeof(char)*30);
    sprintf(filename, "Arquivos/%04d.bin", (*cont));
    FILE * fp = fopen(filename, "wb");
    if(!fp) exit(1);
    TABM novo;
    TJ jogador;
    novo.folha = 1;
    novo.nchaves = 0;
    novo.prox = (char*)malloc(sizeof(char)*30);
    char tmp[30];
    strcpy(novo.prox, "Prox");
    novo.chaves = (TJ*)malloc(sizeof(TJ)*((t*2)-1));
    for(int i = 0; i < (t*2)-1; i++) strcpy(novo.chaves[i].nome,"Chave");
    novo.filhos=(char**)malloc(sizeof(char*)*t*2);
    for(int i = 0; i < (t*2); i++) novo.filhos[i] = malloc(sizeof(char)*30);
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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//          LÊ DADOS PARA ARQUIVO
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void le_dados(char * arquivo, char ** raiz, int t){
    int cont = 1;
    FILE * fp = fopen(arquivo, "r");
    if(!fp) exit(1);
    TJ *jogador = (TJ*)malloc(sizeof(TJ));
    //int contar = 1;
    char tmp[30];
    while(fscanf(fp, "%s", tmp) == 1){ //lendo por seleção
        while((fscanf(fp, "%d/%d/%4[^/]/%30[^/]/%d %10s %d (aged %d)/%d/%d/%20[^/]/%30[^\n]", &jogador->id, &jogador->num_camisa, jogador->posicao, jogador->nome, &jogador->dia, jogador->mes, &jogador->ano, &jogador->idade, &jogador->part_sel, &jogador->gol_sel, jogador->pais_time, jogador->time) == 12)){ //lendo por jogador
            
            if(strstr(jogador->nome, "(captain)")) jogador->capitao = 1;
            else jogador->capitao = 0;
            //printf("%d %s %d %d %s\n", jogador->dia, jogador->mes, jogador->ano, jogador->idade, jogador->time);
            //a struct jogador já está com as informações
            strcpy((*raiz),TABM_insere(jogador, t, raiz, &cont));
            //contar--;
        }
    }
    fclose(fp);
    return;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//          MAIN
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(void){
    int t;
    char * raiz = (char*)malloc(sizeof(char)*30);
    char filename[30];
    printf("Insira o valor de t para a construcao da arvore: ");
    scanf("%d", &t);
    le_dados("EURO.txt", &raiz, t);
    return 0;
}


/*
dentro da insere, tenta abrir o arquivo "raiz", se não existir, cria ele, 
senão lê para fazer as inserções
*/
