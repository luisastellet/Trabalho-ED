#include "TABM.c"
#include <limits.h>

int compara_Q4(const void *a, const void *b) {
    char **pa = (char**)a;
    char **pb = (char**)b;
    return strcmp(*pa, *pb);
}

void Q4(char* tabela){
    FILE * fp = fopen(tabela, "rb");
    if(!fp) exit(1);
    int qtd, respM = INT_MIN, respm = INT_MAX, num;
    char maior_sel[20], menor_sel[20], aux[20], tmp=0;

    while(fread(&aux, sizeof(char)*20, 1, fp) == 1){
        fread(&qtd, sizeof(int), 1, fp);
        tmp = 0;
        while(fread(&num, sizeof(int), 1, fp) == 1){
            tmp++;
            if(tmp == qtd) break;
        }
        if(qtd > respM){
            respM = qtd;
            strcpy(maior_sel, aux);
        }
        if(qtd < respm){
            respm = qtd;
            strcpy(menor_sel, aux);
        }
    }
    rewind(fp);
    int contm = 0, contM = 0;
    //vendo quantos tem essa quantidade
    while(fread(&aux, sizeof(char)*20, 1, fp) == 1){
        fread(&qtd, sizeof(int), 1, fp);
        tmp = 0;
        while(fread(&num, sizeof(int), 1, fp) == 1){
            tmp++;
            if(tmp == qtd) break;
        }
        if(qtd == respM) contM++;
        if(qtd == respm) contm++;
    }
    
    if(contM == 1){
        printf("\n\t%s eh a maior selecao com %d jogadores\n",maior_sel,respM);
    }
    if (contm == 1){
        printf("\n\t%s eh a menor selecao com %d jogadores\n",menor_sel,respm);
    }
    
    if(contM > 1 || contm > 1){
        char **vetm;
        char **vetM;
        if(contm > 1){
            vetm = (char**)malloc((sizeof(char*))*contm);
            for(int i = 0; i < contm; i++) vetm[i] = malloc(sizeof(char)*21);
        }
        if(contM > 1) {
            vetM = (char**)malloc((sizeof(char*))*contM);
            for(int i = 0; i < contM; i++) vetM[i] = malloc(sizeof(char)*21);
        }

        rewind(fp);
        int m=0, M=0;
        while(fread(&aux, sizeof(char)*20, 1, fp) == 1){
            fread(&qtd, sizeof(int), 1, fp);
            tmp = 0;
            while(fread(&num, sizeof(int), 1, fp) == 1){
                tmp++;
                if(tmp == qtd) break;
            }
            if(contM > 1 && qtd == respM){
                strcpy(vetM[M], aux);
                M++;
            }
            if(contm > 1 && qtd == respm){
                strcpy(vetm[m], aux);
                m++;
            }
        }
        if(contM > 1)qsort(vetM, contM, sizeof(char*), compara_Q4);
        if(contm > 1)qsort(vetm, contm, sizeof(char*), compara_Q4);

        if(contM > 1){
            printf("\n\tMaiores selecoes empatadas em ordem alfabetica com %d jogadores: \n",respM);
            for(int i=0; i<contM; i++) printf("\n\t%s",vetM[i]);
        }
        if (contm > 1){
            printf("\n\tMenores selecoes empatadas em ordem alfabetica com %d jogadores: \n",respm);
            for(int i=0; i<contm; i++) printf("\n\t%s",vetm[i]);        }
        
        if(contM > 1){
            for(int i = 0; i < contM; i++) free(vetM[i]);
            free(vetM);
        }
        if(contm > 1){
            for(int i = 0; i < contm; i++) free(vetm[i]);
            free(vetm);
        }
    }
    return;
}

void Q7(char* raiz, int ano){
    FILE* fp = fopen(raiz,"rb");
    if(fp){
        TABM no;
        fread(&no,sizeof(TABM),1,fp);
        if(!no.folha){
            Q7(no.filhos[0],ano);
        }
        if(no.folha){
            for(int i = 0; i < no.nchaves; i++){
                if(no.chaves[i].ano == ano) printf("\n\t%d. %s",no.chaves[i].id,no.chaves[i].nome);
            }
            Q7(no.prox,ano);
        }
    }
    return;
}

void Q8(char* raiz, char* Mes){
    FILE* fp = fopen(raiz,"rb");
    if(fp){
        TABM no;
        fread(&no,sizeof(TABM),1,fp);
        if(!no.folha){
            Q8(no.filhos[0],Mes);
        }
        if(no.folha){
            for(int i = 0; i < no.nchaves; i++){
                if(strcmp(no.chaves[i].mes,Mes) == 0) printf("\n\t%d. %s",no.chaves[i].id,no.chaves[i].nome);
            }
            Q8(no.prox,Mes);
        }
    }
    return;
}

void Q11(char* arv,int ch){
    FILE* fp = fopen(arv,"rb");
    if(!fp) exit(1);
    fclose(fp);
    
    char resp[21];
    strcpy(resp,TABM_busca(arv,ch));

    fp = fopen(resp,"rb");
    if(!fp){
        printf("\tPREZADO USUARIO: O jogador nao se encontra na arvore");
        return;
    }
    TABM no;
    fread(&no,sizeof(TABM),1,fp);
    fclose(fp);

    int i = 0;
    while(i < no.nchaves && no.chaves[i].id != ch) i++;


    printf("\n\n\tINFOS SUBORDINADAS");
    printf("\n\tNome: %s",no.chaves[i].nome);
    printf("\n\tNumero da camisa: %d", no.chaves[i].num_camisa);
    printf("\n\tPosicao: %s", no.chaves[i].posicao);
    printf("\n\tData de nascimento: %d %s %d", no.chaves[i].dia, no.chaves[i].mes, no.chaves[i].ano);
    printf("\n\tIdade: %d", no.chaves[i].idade);
    printf("\n\tPartidas pela selecao: %d", no.chaves[i].part_sel);
    printf("\n\tGols pela selecao: %d", no.chaves[i].gol_sel);
    printf("\n\tTime regular: %s", no.chaves[i].time);
    printf("\n\tPais do time regular: %s", no.chaves[i].pais_time);
    if(no.chaves[i].capitao) printf("\n\tCapitao: SIM");
    else(printf("\n\tCapitao: NAO"));
    return;
}

