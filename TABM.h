#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_T 50

typedef struct jogador{
    int id;
    int num_camisa;
    char posicao[5];
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


/*
int folha; //4 0-3
int nchaves; //4 4-7
char* prox; //sizeof(char)*5 8-12
TJ * chaves; // 
char** filhos; //arq de 0000 até 9999

*/
typedef struct arvbm{
    int folha; //4 0-3
    int nchaves; //4 4-7
    char prox[30]; //sizeof(char)*5 8-12
    TJ chaves[(2*MAX_T)-1]; // 
    char filhos[2*MAX_T][30]; //arq de 0000 até 9999
}TABM;

void TABM_cria(int t, int * cont, char **arq);
char* TABM_insere(TJ *jogador, int t, char ** raiz, int * cont);
void le_dados(char * arquivo, char ** raiz, int t, int * cont);
void printa_arqb(char * entrada, int t);
void TABM_libera_no(TABM * no);
TABM *TABM_cria_no(int t);


// char data[] = "11 January 1996 (aged 28)";
// // Usando sscanf para extrair os valores da string
// sscanf(data, "%d %s %d (aged %d)", &day, month, &year, &age);

// fscanf(file, "%d/%d/%2s/%30[^/]/%d %10s %d (aged %d)/%d/%d/%20[^/]/%30[^\n]",
//            &id, &num_camisa, posicao, name, &dia, mes, &ano, &idade, &part_sel, &gol_sel, pais_time, time);

// scanf(" %30[^\n]", j1.nome);

// %d lê um inteiro.
// %2s lê uma string de até 2 caracteres (para a posição do jogador).
// %49[^/] lê até 49 caracteres ou até encontrar um / (para o nome).
// %d %19s %d (aged %d) lê o dia (inteiro), o mês (string de até 19 caracteres), o ano (inteiro) e a idade (inteiro).
// %d/%d lê dois inteiros (para jogos e gols).
// %49[^/] lê até 49 caracteres ou até encontrar um / (para o país).
// %49[^\n] lê até 49 caracteres ou até encontrar uma nova linha (para o clube)