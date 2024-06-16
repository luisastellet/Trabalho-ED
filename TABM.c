#include "TABM.h"

TABM *TABM_cria(int t);



void inicializa(int cont){
    char filename[21];
    sprintf(filename, "arq%d.b", cont);
    FILE * fp = fopen(filename, "wb");
    fclose(fp);
}

int main(void){
    int cont = 0;
    inicializa(cont);
    return 0;
}

TABM *TABM_busca(TABM *a, int mat);
TABM *TABM_insere(TABM *T, int mat, int t);
TABM* TABM_retira(TABM* arv, int k, int t);
void TABM_libera(TABM *a);
void TABM_imprime(TABM *a);
void TABM_imprime_chaves(TABM *a);