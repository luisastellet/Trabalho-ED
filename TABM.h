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
}TJ;

typedef struct arvbm{
    int folha;
    int nchaves;
    struct arvbm * prox;
    TJ * chaves;
    struct arvbm ** filhos;
}TABM;

TABM *TABM_cria(int t);
TABM *TABM_inicializa(void);
TABM *TABM_busca(TABM *a, int mat);
TABM *TABM_insere(TABM *T, int mat, int t);
TABM* TABM_retira(TABM* arv, int k, int t);
void TABM_libera(TABM *a);
void TABM_imprime(TABM *a);
void TABM_imprime_chaves(TABM *a);

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