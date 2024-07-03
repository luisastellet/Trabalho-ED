#include "TABM.h"
#include "Tabelas.c"
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//          FUNÇÃO DE BUSCA
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
char* TABM_busca(char* arq, int id){
    FILE* fp = fopen(arq,"rb");
    if(!fp) exit(1);
    TABM a;
    fread(&a,sizeof(TABM),1,fp);
    fclose(fp);
    int i = 0;
    while ((i < a.nchaves) && (id > a.chaves[i].id)) i++;
    if ((i < a.nchaves) && (a.folha) && (id == a.chaves[i].id)) return arq;
    if (a.folha) return "NULL";
    if (a.chaves[i].id == id) i++;
    return TABM_busca(a.filhos[i], id);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//          LIBERA NÓ NA MEMÓRIA PRINCIPAL
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TABM_libera_no(TABM * no){
    free(no);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//          FUNÇÃO DE IMPRESSÃO AUXILIAR
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void imp(char* raiz,int andar, int t){
    FILE* fp = fopen(raiz,"rb");
    if(fp){
        TABM * a = TABM_cria_no(t);
        fread(a,sizeof(TABM),1,fp);
        int i,j;
        for(i = 0; i < a->nchaves; i++){
            imp(a->filhos[i],andar+1,t);
            for(j = 0; j<= andar; j++) printf("\t");
            printf("%d\n", a->chaves[i].id);
        }
        imp(a->filhos[i],andar+1,t);
        fclose(fp);
        TABM_libera_no(a);
    }
    return;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//          FUNÇÃO DE IMPRIMIR A ÁRVORE PELOS IDS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TABM_imprime(char** raiz,int t){
    imp(*raiz,0,t);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//          FUNÇÃO DE COPIAR STRUCTS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void copia(TABM * T, TABM * aux, int t){
    aux->nchaves = T->nchaves;
    aux->folha = T->folha;
    strcpy(aux->prox,T->prox);

    int i;
    for (int i=0; i<T->nchaves; i++){
        aux->chaves[i].id = T->chaves[i].id;
        aux->chaves[i].num_camisa = T->chaves[i].num_camisa;
        strcpy(aux->chaves[i].posicao, T->chaves[i].posicao);
        strcpy(aux->chaves[i].nome,T->chaves[i].nome);
        aux->chaves[i].dia = T->chaves[i].dia;
        strcpy(aux->chaves[i].mes,T->chaves[i].mes);
        aux->chaves[i].ano = T->chaves[i].ano;
        aux->chaves[i].idade = T->chaves[i].idade;
        aux->chaves[i].part_sel = T->chaves[i].part_sel;
        aux->chaves[i].gol_sel = T->chaves[i].gol_sel;
        strcpy(aux->chaves[i].pais_time,T->chaves[i].pais_time);
        strcpy(aux->chaves[i].time,T->chaves[i].time);
        aux->chaves[i].capitao = T->chaves[i].capitao;
    }
    for(i = 0; i<= 2 * t;i++){
        strcpy(aux->filhos[i],T->filhos[i]);
    }
    return;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//          FUNÇÃO DE CRIAR O NÓ NA MEMÓRIA PRINCIPAL
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TABM *TABM_cria_no(int t){
    TABM* novo = (TABM*)malloc(sizeof(TABM));
    novo->nchaves = 0;
    novo->folha = 1;
    strcpy(novo->prox, "Prox");
    return novo;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//          FUNÇÃO DE DIVIDIR
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TABM *divisao(TABM *S, int i, TABM* T, int t, int * cont){
    TABM *z = TABM_cria_no(t);
    char *z_arq = (char*)malloc(sizeof(char)*30);
    TABM_cria(t, cont, &z_arq);
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
    FILE* fz = fopen(z_arq,"wb+");
    TABM aux;
    copia(z,&aux,t);
    fwrite(&aux,sizeof(TABM),1,fz);
    fclose(fz);
    free(z_arq);
    TABM_libera_no(z);
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

    FILE* fp = fopen(S->filhos[i],"rb+");
    TABM* S_filho = TABM_cria_no(t);
    fread(S_filho,sizeof(TABM),1,fp);
    fclose(fp);

    if(S_filho->nchaves == ((2*t)-1)){
        fp = fopen(S->filhos[i],"wb");
        S = divisao(S, (i+1), S_filho, t, cont);
        if(jogador->id > S->chaves[i].id) i++;
        TABM aux;
        copia(S_filho,&aux,t);
        fwrite(&aux,sizeof(TABM),1,fp);
        fclose(fp);
    }
    

    fp = fopen(S->filhos[i],"rb+");  
    //S_filho = TABM_cria_no(t);
    fread(S_filho,sizeof(TABM),1,fp);
    fclose(fp);
    
    S_filho = insere_nao_completo(S_filho, jogador, t, cont);

    TABM aux;
    copia(S_filho,&aux,t);
    fp = fopen(S->filhos[i],"wb");
    fwrite(&aux,sizeof(TABM),1,fp);
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
        TABM_cria(t, cont, raiz);// Esse cara é o nosso "retorno", visto que temos uma variável raiz para controlar qual o nó do topo
        FILE * fraiz = fopen(*raiz, "rb+");
        if(!fraiz) exit(1);
        TABM *T = TABM_cria_no(t);
        fread(T,sizeof(TABM),1,fraiz);
        T->chaves[0] = *jogador;
        T->nchaves = 1;
        rewind(fraiz);
        TABM aux;
        copia(T,&aux,t);
        fwrite(&aux, sizeof(TABM), 1, fraiz);
        TABM_libera_no(T);
        fclose(fraiz);
        return *raiz;
    }
    
    TABM *T = TABM_cria_no(t);
    fread(T,sizeof(TABM),1,fp);
    fclose(fp);

    if(T->nchaves == (2*t)-1){ //tá lotado
        char * S_arq = (char*)malloc(sizeof(char)*30);
        TABM_cria(t, cont, &S_arq);
        FILE *fs = fopen(S_arq, "rb+");
        if(!fs) exit(1);
        TABM* S = (TABM*)malloc(sizeof(TABM));
        fread(S, sizeof(TABM),1,fs);
        fclose(fs);
        S->nchaves = 0;
        S->folha = 0;
        strcpy(S->filhos[0],(*raiz));
        S = divisao(S,1,T,t, cont);
        fp = fopen(*raiz, "wb");
        TABM aux_3;
        copia(T, &aux_3, t);
        fwrite(&aux_3, sizeof(TABM), 1, fp);
        fclose(fp);
        S = insere_nao_completo(S, jogador, t, cont);
        TABM aux;
        copia(S,&aux,t);
        fs = fopen(S_arq,"wb");
        fwrite(&aux, sizeof(TABM),1,fs); //Escreve S
        fclose(fs);

        TABM_libera_no(T);
        TABM_libera_no(S);
        strcpy(*raiz, S_arq);
        free(S_arq);
        return *raiz;
    }

    T = insere_nao_completo(T, jogador, t,cont);
    TABM aux;
    copia(T,&aux,t);
    fp = fopen(*raiz, "wb");
    fwrite(&aux,sizeof(TABM),1,fp);
    fclose(fp);
    TABM_libera_no(T);
    return *raiz;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//          CRIA O ARQUIVO "VAZIO"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TABM_cria(int t, int *cont, char ** arq){
    sprintf(*arq, "Arquivos/%04d.bin", (*cont));
    FILE * fp = fopen(*arq, "wb");
    if(!fp) exit(1);
    TABM novo;
    TJ jogador;
    novo.folha = 1;
    novo.nchaves = 0;
    novo.prox;
    strcpy(novo.prox, "Arquivos/Prox");
    for(int i = 0; i < (t*2)-1; i++) strcpy(novo.chaves[i].nome,"Chave");
    for(int i = 0; i < (t*2); i++) strcpy(novo.filhos[i],"Filh");
    fwrite(&novo, sizeof(TABM), 1, fp);
    fclose(fp);
    (*cont)++;
    return;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//          PRINTAR CONTEÚDO DO ARQUIVO BINÁRIO
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void printa_arqb(char* entrada, int t){
    FILE* fp = fopen(entrada, "rb");
    TABM novo;
    fread(&novo, sizeof(TABM),1,fp);
    printf("Arquivo atual: %s\n",entrada);
    printf("Folha: %d\n", novo.folha);
    printf("N Chaves: %d\n", novo.nchaves);
    printf("Proximo: %s\n", novo.prox);
    for (int i = 0; i < novo.nchaves; i++) printf("%d/%d/%s/%s/%d %s %d (aged %d)/%d/%d/%s/%s\n", 
            novo.chaves[i].id, novo.chaves[i].num_camisa, novo.chaves[i].posicao, novo.chaves[i].nome, 
            novo.chaves[i].dia, novo.chaves[i].mes, novo.chaves[i].ano, novo.chaves[i].idade, novo.chaves[i].part_sel, 
            novo.chaves[i].gol_sel, novo.chaves[i].pais_time, novo.chaves[i].time);
    for (int i = 0; i < 2*t; i++) printf("%s\n",novo.filhos[i]);
    printf("\n\n\n");
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
    int contar = 284;
    char tmp[30];
    while(fscanf(fp, "%s", tmp) == 1){ //lendo por seleção
        while(contar && (fscanf(fp, "%d/%d/%4[^/]/%30[^/]/%d %10s %d (aged %d)/%d/%d/%20[^/]/%30[^\n]", &jogador->id, &jogador->num_camisa, jogador->posicao, jogador->nome, &jogador->dia, jogador->mes, &jogador->ano, &jogador->idade, &jogador->part_sel, &jogador->gol_sel, jogador->pais_time, jogador->time) == 12)){ //lendo por jogador
            if(strstr(jogador->nome, "(captain)")) jogador->capitao = 1;
            else jogador->capitao = 0;
            strcpy((*raiz),TABM_insere(jogador, t, raiz, &cont));
            contar--;
        }
    }
    fclose(fp);
    free(jogador);
    return;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//          MAIN
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(void){
    int t, x;
    char * raiz = (char*)malloc(sizeof(char)*30);
    mkdir("Arquivos", 0777);
    mkdir("Tabelas", 0777);
    printf("Insira o valor de t para a construcao da arvore: ");
    scanf("%d", &t);
    le_dados("EURO.txt", &raiz, t);
    TABM_imprime(&raiz,t);
    printf("Qual jogador voce deseja?: ");
    scanf("%d",&x);
    char resp[20];
    strcpy(resp,TABM_busca(raiz,x));
    printa_arqb(resp,t);
    free(raiz);
    // tabela_nacionalidade("EURO.txt");
    // printa_nacionalidades("Tabelas/Nacionalidades.bin");
    // tabela_posicoes("EURO.txt");
    // printa_posicoes("Tabelas/Posições.bin");
    return 0;
}