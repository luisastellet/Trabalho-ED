#include "Funcoes.c"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//          MAIN
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(void){
    int t, x,opcao=1,id,ano,mes;
    int cont = 1;
    char * raiz = (char*)malloc(sizeof(char)*30);
    mkdir("Arquivos", 0777);
    mkdir("Tabelas",0777);
    printf("Insira o valor de t para a construcao da arvore: ");
    scanf("%d", &t);
    le_dados("EURO.txt", &raiz, t, &cont);
    tabela_nacionalidade("EURO.txt");
    tabela_posicoes("EURO.txt");
    //printa_nacionalidades("Tabelas/Nacionalidades.bin");
    //TABM_imprime(&raiz,t);
    do{
        printf("\n\n\t0 - Sair\n\n\t1 ao 20 - Questoes\n\n\t21 - Menu");
        printf("\n");
        printf("\n\n\tDigite uma das opcoes: ");
        scanf("%d", &opcao);
        switch (opcao)
        {
        case 1:
            /* (1) Retorno do jogador mais novo e mais velho da competição, ilustrando essas mesmas informações
            por seleções e por posições; */
            break;
        case 2:
            /* (2) Os jogadores que mais e menos atuaram em suas equipes; */
            break;
        case 3:
            /* (3) Os jogadores que mais e menos atuaram no total; */
            break;
        case 4:
            printf("\n\n\t=====================================================================================================");
            printf("\n\tSELECAO COM MAIS OU MENOS JOGADORES: \n");
            Q4("Tabelas/Nacionalidades.bin");
            printf("\n\n\t=====================================================================================================");
            printf("\n");
            break;
        case 5:
            /* (5) Busca de todos os jogadores que atuam fora do seu país de origem; */
            break;
        case 6:
            /* (6) Busca de todos os jogadores que atuam no seu país de origem; */
            break;
        case 7:
            printf("\n\tDigite o ano: ");
            scanf("%d",&ano);
            printf("\n\n\t=====================================================================================================");
            printf("\n\n\tJogadores nascidos em %d:", ano);
            Q7(raiz,ano);
            printf("\n\n\t=====================================================================================================");
            printf("\n");
            break;
        case 8:
            printf("\n\tDigite o mes(numerico): ");
            scanf("%d",&mes);
            char Mes[21];
            if(mes == 1) strcpy(Mes,"January");
            if(mes == 2) strcpy(Mes,"February");
            if(mes == 3) strcpy(Mes,"March");
            if(mes == 4) strcpy(Mes,"April");
            if(mes == 5) strcpy(Mes,"May");
            if(mes == 6) strcpy(Mes,"June");
            if(mes == 7) strcpy(Mes,"July");
            if(mes == 8) strcpy(Mes,"August");
            if(mes == 9) strcpy(Mes,"September");
            if(mes == 10) strcpy(Mes,"October");
            if(mes == 11) strcpy(Mes,"November");
            if(mes == 12) strcpy(Mes,"December");
            printf("\n\n\t=====================================================================================================");
            printf("\n\n\tJogadores nascidos em %s:", Mes);
            Q8(raiz,Mes);
            printf("\n\n\t=====================================================================================================");
            printf("\n");
            printf("\n");
            break;
        case 9:
            /* (9) Busca da(s) seleção(ções) com mais jogadores que atuam fora do seu país de origem; */
            break;
        case 10:
            /* (10) Busca da(s) seleção(ções) com mais jogadores que atuam no seu país de origem; */
            break;
        case 11:
                printf("\tDigite o id para obter as infos subordinadas a ele: ");
                scanf("%d",&id);
                printf("\n\n\t=====================================================================================================");
                Q11(raiz,id);
                printf("\n\n\t=====================================================================================================");
                printf("\n");
                break;
            break;
        case 12:
            /* (12) Alteração SOMENTE de algumas informações, por exemplo, número da camisa que ele usa em
            sua respectiva seleção, a posição que ele joga (EXCETO GK), o número de partidas pela seleção, o
            número de gols, o jogador passar a (ou deixar de) ser capitão, o país do seu time atual e o nome do
            time atual; */
            break;
        case 13:
            /* (13) Busca de todos os jogadores de uma seleção; */
            break;
        case 14:
            /* (14) Busca e remoção de todos os capitães; */
            break;
        case 15:
            /* (15) Remoção de jogadores a partir de uma determinada idade; */
            break;
        case 16:
            /* (16) Retirada de todos os jogadores de uma seleção que atuam num determinado país; */
            break;
        case 17:
            /* (17) Retirada de todos os os jogadores de uma seleção que não atuam no país de origem; */
            break;
        case 18:
            /* (18) Retirada de todos os os jogadores de uma seleção atuam fora do país de origem; */
            break;
        case 19:
            /* (19) Retirada de todos os os jogadores de uma seleção; */
            break;
        case 20:
            /* (20) Remoção de jogadores, dado um conjunto contendo suas chaves primárias. */
            break;
        case 21:
            printf("\n");
            printf("\t=====================================================================================================");
            printf("\n\n\t1 - Os jogador mais novo e mais velho\n\n\t2 - OS jogadores que mais e menos atuaram por suas equipes\n\n\t3 - Jogadores que mais e menos atuaram no geral\n\n\t4 - A maior e menor seleção\n\n\t5 - Busca de jogadores que atuam fora do seu país de origem\n\n\t6 - Busca de jogadores que atuam no seu país de origem\n\n\t7 - Busca de jogadores que nasceram no mesmo ano\n\n\t8 - Busca de jogadores que nasceram no mesmo mês\n\n\t9 - Busca das seleções com mais jogadores que atuam fora do seu páis de origem\n\n\t10 - Busca das seleções com mais jogadores que atuam no seu país de origem\n\n\t11 - Dados de um jogador pelo ID\n\n\t12 - Alteração de informações\n\n\t13 - Busca de todos os jogadores de uma seleção\n\n\t14 - Busca e remoção de todos os capitães\n\n\t15 - Remoção de jogadores a partir de uma determinada idade\n\n\t16 - Retirada de todos os jogadores de uma seleção que atuam num determinado país\n\n\t17 - Retirada de todos os os jogadores de uma seleção que não atuam no país de origem\n\n\t18 - Retirada de todos os os jogadores de uma seleção atuam fora do país de origem\n\n\t19 - Retirada de todos os os jogadores de uma seleção\n\n\t20 - Remoção de jogadores, dado um conjunto contendo suas chaves primárias.");
            printf("\n\n");
            printf("\t=====================================================================================================");
            break;
        default:
            if(opcao != 0) printf("Opcao invalida!!!\n");
            break;
        }
    } while (opcao);


    free(raiz);

    system("rm -fr Arquivos");
    system("rm -rf Tabelas");
    return 0;
}