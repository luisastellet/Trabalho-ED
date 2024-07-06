#include "TABM.c"
#include <limits.h>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//          (3) Os jogadores que mais e menos atuaram no total;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int compara_Q3(const void* a, const void* b){
    TJ* pa = (TJ*)a;
    TJ* pb = (TJ*)b;

    return strcmp((pa)->nome,(pb)->nome);
}

void Q3_percorre(char*arv,TJ* jogadorM, TJ* jogadorm,int* contM,int* contm){
    FILE* fp = fopen(arv,"rb");
    if(fp){
        TABM no;
        fread(&no,sizeof(TABM),1,fp);
        if(!no.folha){
            Q3_percorre(no.filhos[0],jogadorM,jogadorm,contM,contm);
        }
        if(no.folha){
            for(int i = 0; i < no.nchaves; i++){
                if(no.chaves[i].part_sel == jogadorM->part_sel) (*contM)++;
                if(no.chaves[i].part_sel > jogadorM->part_sel){
                    *jogadorM = copia_chaves(*jogadorM,no.chaves[i]);
                    *contM = 1;
                }
                if(no.chaves[i].part_sel == jogadorm->part_sel) (*contm)++;
                if(no.chaves[i].part_sel < jogadorm->part_sel){
                    *jogadorm = copia_chaves(*jogadorm,no.chaves[i]);
                    *contm = 1;
                }
            }
            Q3_percorre(no.prox,jogadorM,jogadorm,contM,contm);
        }
    }
    return;
}

void Q3_preenche(char * arv, TJ jogadorM, TJ jogadorm, int * indiceM, int * indicem, TJ * vetM, TJ * vetm,int contM, int contm){
    FILE* fp = fopen(arv,"rb");
    if(fp){
        TABM no;
        fread(&no,sizeof(TABM),1,fp);
        if(!no.folha){
            Q3_preenche(no.filhos[0], jogadorM, jogadorm, indiceM, indicem, vetM, vetm,contM,contm);
        }
        if(no.folha){
            for(int i = 0; i < no.nchaves; i++){
                if((contM > 1) && (no.chaves[i].part_sel == jogadorM.part_sel)){
                    vetM[(*indiceM)] = copia_chaves(vetM[(*indiceM)],no.chaves[i]);
                    (*indiceM)++;
                }
                if(contm > 1 && no.chaves[i].part_sel == jogadorm.part_sel){
                    vetm[(*indicem)] = copia_chaves(vetm[(*indicem)],no.chaves[i]);
                    (*indicem)++;
                }
            }
            Q3_preenche(no.prox, jogadorM, jogadorm, indiceM, indicem, vetM, vetm,contM,contm);
        }
    }
    return;
}

void Q3(char* arv){
    TJ jogadorM, jogadorm;
    int contM = 0, contm = 0;
    jogadorm.part_sel = INT_MAX;
    jogadorM.part_sel = INT_MIN;

    Q3_percorre(arv,&jogadorM,&jogadorm,&contM,&contm);


    if(contM == 1){
        printf("\n\t%s eh o jogador que mais atuou na sua equipe, com %d partidas.\n",jogadorM.nome,jogadorM.part_sel);
    }
    if (contm == 1){
        printf("\n\t%s eh o jogador que menos atuou na sua equipe, com %d partidas.\n",jogadorm.nome,jogadorm.part_sel);
    }

    if(contM > 1 || contm > 1){
        TJ * vetm;
        TJ * vetM;
        if(contm > 1){
            vetm = (TJ*)malloc((sizeof(TJ))*contm);
        }
        if(contM > 1) {
            vetM = (TJ*)malloc((sizeof(TJ))*contM);
        }

        int indicem = 0, indiceM = 0;
        Q3_preenche(arv, jogadorM, jogadorm, &indiceM, &indicem, vetM, vetm,contM, contm);


        if(contM > 1)qsort(vetM, contM, sizeof(TJ), compara_Q3);
        if(contm > 1)qsort(vetm, contm, sizeof(TJ), compara_Q3);

        if(contM > 1){
            printf("\n\tJogadores que mais atuaram no total em ordem alfabetica com %d partidas:\n", jogadorM.part_sel);
            for(int i=0; i<contM; i++) printf("\n\t%s",vetM[i].nome);
        }
        if (contm > 1){
            printf("\n\tJogadores que menos atuaram no total em ordem alfabetica com %d partidas:\n", jogadorm.part_sel);
            for(int i=0; i<contm; i++) printf("\n\t%s",vetm[i].nome);        
        }
        if(contM > 1) free(vetM);
        if(contm > 1) free(vetm);
    }
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//          (4) A menor e a maior seleção, isto é, com menos ou mais convocados
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int compara_Q4(const void *a, const void *b) {
    char **pa = (char**)a;
    char **pb = (char**)b;
    return strcmp(*pa, *pb);
}

void Q4(char* tabela){
    FILE * fp = fopen(tabela, "rb");
    if(!fp) exit(1);
    int qtd, respM = INT_MIN, respm = INT_MAX, num, tmp=0, lim;
    char maior_sel[20], menor_sel[20], aux[20];

    while(fread(&aux, sizeof(char)*20, 1, fp) == 1){
        fread(&qtd, sizeof(int), 1, fp);
        tmp = 0;
        lim = qtd;
        while(fread(&num, sizeof(int), 1, fp) == 1){
            tmp++;
            if(num == -1) qtd--;
            if(tmp == lim) break;
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
    fclose(fp);
    return;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//          (5) Busca de todos os jogadores que atuam fora do seu país de origem
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Q5(char* tabela, char* arv){
    FILE * fp = fopen(tabela, "rb");
    if(!fp) exit(1);

    int qtd, num, tmp = 0;
    char sele[20],aux[20];
    TABM a;

    while(fread(&sele, sizeof(char)*20, 1, fp) == 1){
        fread(&qtd, sizeof(int), 1, fp);
        tmp = 0;
        printf("\n");
        printf("\n\t%s: ",sele);
        while(tmp != qtd && fread(&num, sizeof(int), 1, fp) == 1){
            strcpy(aux,TABM_busca(arv,num));
            if(strcmp(aux,"NULL") != 0){
                FILE* fj = fopen(aux,"rb");
                if(!fj) exit(1);
                fread(&a,sizeof(TABM),1,fj);
                fclose(fj);

                int i;
                for(i = 0; a.chaves[i].id != num; i++);
                if(strcmp(a.chaves[i].pais_time,sele) != 0) printf("\n\t%d. %s (%s)",a.chaves[i].id, a.chaves[i].nome, a.chaves[i].pais_time);
            }
            tmp++;
        }
    }
    fclose(fp);
    return;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//          (6) Busca de todos os jogadores que atuam no seu país de origem
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Q6(char* tabela,char* arv){
    FILE * fp = fopen(tabela, "rb");
    if(!fp) exit(1);

    int qtd, num, tmp = 0;
    char sele[20],aux[20];
    TABM a;

    while(fread(&sele, sizeof(char)*20, 1, fp) == 1){
        fread(&qtd, sizeof(int), 1, fp);
        tmp = 0;
        printf("\n");
        printf("\n\t%s: ",sele);
        while(tmp != qtd && fread(&num, sizeof(int), 1, fp) == 1){
            strcpy(aux,TABM_busca(arv,num));
            if(strcmp(aux,"NULL") != 0){
                FILE* fj = fopen(aux,"rb");
                if(!fj) exit(1);
                fread(&a,sizeof(TABM),1,fj);
                fclose(fj);

                int i;
                for(i = 0; a.chaves[i].id != num; i++);
                if(strcmp(a.chaves[i].pais_time,sele) == 0) printf("\n\t%d. %s",a.chaves[i].id, a.chaves[i].nome);
            }
            tmp++;
        }
    }
    fclose(fp);
    return;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//          (7) Busca de todos os jogadores que nasceram no mesmo ano
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//          (8) Busca de todos os jogadores que nasceram no mesmo mês
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//          (11) Busca das informações subordinadas, dadas a chave primária (identificador único do jogador)
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
    printf("\n\tSelecao: %s", no.chaves[i].sele);
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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//          (12.1) Alteração do número da camisa de um jogador
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Q12_1(char* arv, int id, int novo_num){
    char resp[20], sele_tmp[20], aux[20];
    int qtd, tmp, num, ver = 0;
    strcpy(resp,TABM_busca(arv,id));
    FILE* fj = fopen(resp,"rb");
    if(!fj) exit(1);
    TABM a, b;
    fread(&a,sizeof(TABM),1,fj);
    fclose(fj);

    int i = 0;
    for(i = 0; a.chaves[i].id != id; i++);

    char selecao[20];
    strcpy(selecao,a.chaves[i].sele);

    FILE* fp = fopen("Tabelas/Nacionalidades.bin", "rb");
    if(!fp) exit(1);

    while(fread(&sele_tmp, sizeof(char)*20, 1, fp) == 1){
        fread(&qtd, sizeof(int), 1, fp);
        tmp = 0;
        while((tmp != qtd) && (fread(&num, sizeof(int), 1, fp) == 1)){
            if(strcmp(sele_tmp,selecao) == 0){
                strcpy(aux,TABM_busca(arv,num));
                if(strcmp(aux,"NULL") != 0){
                    fj = fopen(aux,"rb");
                    if(!fj) exit(1);
                    fread(&b,sizeof(TABM),1,fj);
                    fclose(fj);

                    int j;
                    for(j = 0; b.chaves[j].id != num; j++);
                    if(b.chaves[j].num_camisa == novo_num){
                        printf("\n");
                        printf("\n\tPREZADO USUARIO: Ja existe um jogador desta selecao com este numero!");
                        fclose(fp);
                        return;
                    }
                }
            }
            tmp++;
        }
    }
    a.chaves[i].num_camisa = novo_num;
    printf("\n");
    printf("\n\tAlterado com sucesso!");
    fj = fopen(resp, "wb");
    fwrite(&a,sizeof(TABM),1,fj);
    fclose(fj);
    fclose(fp);
    return;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//          (12.2) Alteração da posição do jogador
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Q12_2(char* arv, int id, char* pos){
    char resp[20];
    strcpy(resp,TABM_busca(arv,id));
    FILE* fj = fopen(resp,"rb");
    if(!fj) exit(1);
    TABM a;
    fread(&a,sizeof(TABM),1,fj);
    fclose(fj);

    int i = 0;
    for(i = 0; a.chaves[i].id != id; i++);

    if(strcmp(a.chaves[i].posicao,"GK") == 0){
        printf("\n\tPREZADO USUARIO: Nao eh possivel alterar a posicao de um goleiro!");
        return;
    }

    if(strcmp(pos, a.chaves[i].posicao)){ //times diferentes
        strcpy(a.chaves[i].posicao, pos);
        tabela_posicoes_alterar("EURO.txt", id, pos);
        printf("\n\n\tAlterado com sucesso e tabela de posicoes atualizada!");
        fj = fopen(resp, "wb");
        fwrite(&a, sizeof(TABM), 1, fj);
        fclose(fj);
    }else printf("\n\n\tPREZADO USUARIO: O jogador ja joga nesta posicao!");
    
    return;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//          (12.3) Alteração da idade de um jogador
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Q12_3(char* arv, int id, int nova_idade){
    char resp[20];
    strcpy(resp,TABM_busca(arv,id));
    FILE* fj = fopen(resp,"rb");
    if(!fj) exit(1);
    TABM a;
    fread(&a,sizeof(TABM),1,fj);
    fclose(fj);

    int i = 0;
    for(i = 0; a.chaves[i].id != id; i++);

    if(nova_idade >= a.chaves[i].idade){
        a.chaves[i].idade = nova_idade;
        printf("\n");
        printf("\n\tAlterado com sucesso!");
        fj = fopen(resp,"wb");
        fwrite(&a,sizeof(TABM),1,fj);
        fclose(fj);
    }
    else{
        printf("\n");
        printf("\n\tPREZADO USUARIO: Nao eh possivel retrocedor uma idade!");
    }
    return;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//          (12.4) Alteração da quantidade de partidas de um jogador
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Q12_4(char* arv, int id, int novas_partidas){
    char resp[20], sele_tmp[20], aux[20];
    strcpy(resp,TABM_busca(arv,id));
    FILE* fj = fopen(resp,"rb");
    if(!fj) exit(1);
    TABM a, b;
    fread(&a,sizeof(TABM),1,fj);
    fclose(fj);

    int i = 0;
    for(i = 0; a.chaves[i].id != id; i++);

    if(novas_partidas >= a.chaves[i].part_sel){
        a.chaves[i].part_sel = novas_partidas;
        printf("\n\n\tAlterado com sucesso!");
        fj = fopen(resp, "wb");
        fwrite(&a, sizeof(TABM), 1, fj);
        fclose(fj);
    }else printf("\n\n\tPREZADO USUARIO: Não eh possivel retroceder a quantidade de partidas!");
    
    return;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//          (12.5) Alteração do número de gols de um jogador
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Q12_5(char* arv, int id, int novos_gols){
    char resp[20], sele_tmp[20], aux[20];
    strcpy(resp,TABM_busca(arv,id));
    FILE* fj = fopen(resp,"rb");
    if(!fj) exit(1);
    TABM a, b;
    fread(&a,sizeof(TABM),1,fj);
    fclose(fj);

    int i = 0;
    for(i = 0; a.chaves[i].id != id; i++);

    if(novos_gols >= a.chaves[i].gol_sel){
        a.chaves[i].gol_sel = novos_gols;
        printf("\n\n\tAlterado com sucesso!");
        fj = fopen(resp, "wb");
        fwrite(&a, sizeof(TABM), 1, fj);
        fclose(fj);
    }else printf("\n\n\tPREZADO USUARIO: Não eh possivel retroceder a quantidade de gols!");
    
    return;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//          (12.6) Alteração do time de um jogador
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Q12_6(char* arv, int id, char * novo_time){
    char resp[20];
    strcpy(resp,TABM_busca(arv,id));
    FILE* fj = fopen(resp,"rb");
    if(!fj) exit(1);
    TABM a;
    fread(&a,sizeof(TABM),1,fj);
    fclose(fj);
    
    //time e o pais
    char novo_pais[21];
    printf("\n\n\tQual o pais desse time? ");
    scanf("%s", novo_pais);

    int i = 0;
    for(i = 0; a.chaves[i].id != id; i++);

    if(strcmp(novo_time, a.chaves[i].time)){ //times diferentes
        strcpy(a.chaves[i].time, novo_time);
        strcpy(a.chaves[i].pais_time, novo_pais);
        printf("\n\n\tAlterado com sucesso!");
        fj = fopen(resp, "wb");
        fwrite(&a, sizeof(TABM), 1, fj);
        fclose(fj);
    }else printf("\n\n\tPREZADO USUARIO: O jogador ja joga neste time!");
    
    return;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//          (12.7) Alteração da opção capitão de um jogador
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void vira_capitao(char * arv, int id){
    char resp[20], sele_tmp[20], aux[20];
    int qtd, tmp, num, ver = 0;
    strcpy(resp,TABM_busca(arv,id));
    FILE* fj = fopen(resp,"rb");
    if(!fj) exit(1);
    TABM a, b;
    fread(&a,sizeof(TABM),1,fj);
    fclose(fj);

    int i = 0;
    for(i = 0; a.chaves[i].id != id; i++);

    if(a.chaves[i].capitao){
        printf("\n\n\tPREZADO USUARIO: O %s ja eh capitao!",a.chaves[i].nome);
        return;
    }

    char selecao[20];
    strcpy(selecao,a.chaves[i].sele);

    FILE* fp = fopen("Tabelas/Nacionalidades.bin", "rb");
    if(!fp) exit(1);

    while(fread(&sele_tmp, sizeof(char)*20, 1, fp) == 1){
        fread(&qtd, sizeof(int), 1, fp);
        tmp = 0;
        while((tmp != qtd) && (fread(&num, sizeof(int), 1, fp) == 1)){
            if(strcmp(sele_tmp,selecao) == 0){ //Tornar alguem capitao
                strcpy(aux,TABM_busca(arv,num));
                if(strcmp(aux,"NULL") != 0){
                    fj = fopen(aux,"rb");
                    if(!fj) exit(1);
                    fread(&b,sizeof(TABM),1,fj);
                    fclose(fj);

                    int j;
                    for(j = 0; b.chaves[j].id != num; j++);
                    if((b.chaves[j].capitao) && (b.chaves[j].id != id)){
                        b.chaves[j].capitao = 0;
                        FILE* fb = fopen(aux,"wb");
                        fwrite(&b,sizeof(TABM),1,fb);
                        fclose(fb);
                    }
                }
            }
            tmp++;
        }
    }
    a.chaves[i].capitao = 1;
    printf("\n");
    printf("\n\tAlterado com sucesso!");
    printf("\n\t%s eh o novo capitao do(a) %s",a.chaves[i].nome, a.chaves[i].sele);
    fj = fopen(resp, "wb");
    fwrite(&a,sizeof(TABM),1,fj);
    fclose(fj);
    fclose(fp);
    return;
    
}

void deixa_capitao(char * arv, int id, int t){
    char resp[20], sele_tmp[20], aux[20], arq_maior[25];
    int qtd, tmp, num, partidas = INT_MIN, id_maior;
    strcpy(resp,TABM_busca(arv,id));
    FILE* fj = fopen(resp,"rb");
    if(!fj) exit(1);
    TABM a, b, jog_maior;
    fread(&a,sizeof(TABM),1,fj);
    fclose(fj);

    int i = 0;
    for(i = 0; a.chaves[i].id != id; i++);
    
    if(!a.chaves[i].capitao){
        printf("\n\n\tPREZADO USUARIO: O %s nao eh capitao!",a.chaves[i].nome);
        return;
    }
    a.chaves[i].capitao = 0;
    fj = fopen(resp, "wb");
    fwrite(&a,sizeof(TABM),1,fj);
    fclose(fj);

    char selecao[20];
    strcpy(selecao,a.chaves[i].sele);

    FILE* fp = fopen("Tabelas/Nacionalidades.bin", "rb");
    if(!fp) exit(1);

    while(fread(&sele_tmp, sizeof(char)*20, 1, fp) == 1){
        fread(&qtd, sizeof(int), 1, fp);
        tmp = 0;
        while((tmp != qtd) && (fread(&num, sizeof(int), 1, fp) == 1)){
            if(strcmp(sele_tmp,selecao) == 0){ //Tirar o capitão
                strcpy(aux,TABM_busca(arv,num));
                if(strcmp(aux,"NULL") != 0){
                    fj = fopen(aux,"rb");
                    if(!fj) exit(1);
                    fread(&b,sizeof(TABM),1,fj);
                    fclose(fj);

                    int j;
                    for(j = 0; b.chaves[j].id != num; j++);
                    if((b.chaves[j].part_sel > partidas) && (b.chaves[j].id != id)){

                        partidas = b.chaves[j].part_sel;
                        id_maior = b.chaves[j].id;
                        copia(&b,&jog_maior,t);
                        strcpy(arq_maior,aux);
                    }
                }
            }
            tmp++;
        }
    }
    int j;
    for(j = 0; jog_maior.chaves[j].id != id_maior; j++);
    jog_maior.chaves[j].capitao = 1;
    fj = fopen(arq_maior,"wb");
    fwrite(&jog_maior,sizeof(TABM),1,fj);
    fclose(fj);
    printf("\n");
    printf("\n\tAlterado com sucesso!");
    printf("\n\t%s eh o novo capitao do(a) %s",jog_maior.chaves[j].nome, jog_maior.chaves[j].sele);
    return;
}


void Q12_7(char* arv, int id, int op, int t){

    if(op) vira_capitao(arv, id);
    else deixa_capitao(arv, id, t);

    return;
}

void Q13(char* arv, char*pais, char* tabela){
    FILE * fp = fopen(tabela, "rb");
    if(!fp) exit(1);

    int qtd, num, tmp = 0;
    char sele[20],aux[20];
    TABM a;

    printf("\n");
    printf("\n\t%s: ",pais);
    while(fread(&sele, sizeof(char)*20, 1, fp) == 1){
        fread(&qtd, sizeof(int), 1, fp);
        tmp = 0;
        while(tmp != qtd && fread(&num, sizeof(int), 1, fp) == 1){
            if(strcmp(sele,pais) == 0){
                strcpy(aux,TABM_busca(arv,num));
                if(strcmp(aux,"NULL") != 0){
                    FILE* fj = fopen(aux,"rb");
                    if(!fj) exit(1);
                    fread(&a,sizeof(TABM),1,fj);
                    fclose(fj);

                    int i;
                    for(i = 0; a.chaves[i].id != num; i++);
                    printf("\n\t%d. %s",a.chaves[i].id, a.chaves[i].nome);
                }
            }    
            tmp++;
        }
    }
    fclose(fp);
    return;
}

