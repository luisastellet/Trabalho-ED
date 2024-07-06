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
            printf("\n\n\t=====================================================================================================");
            printf("\n\tJOGADORES QUE ATUAM FORA DO SEU PAIS DE ORIGEM: \n");
            Q5("Tabelas/Nacionalidades.bin",raiz);
            printf("\n\n\t=====================================================================================================");
            printf("\n");
            break;
        case 6:
            printf("\n\n\t=====================================================================================================");
            printf("\n\tJOGADORES QUE ATUAM NO SEU PAIS DE ORIGEM: \n");
            Q6("Tabelas/Nacionalidades.bin",raiz);
            printf("\n\n\t=====================================================================================================");
            printf("\n");
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
            int resp = 1;
            do{
                printf("\n\n\t=====================================================================================================");
                printf("\n\n\t0 - Sair\n\n\t1 - Numero da camisa\n\n\t2 - Posicao\n\n\t3 - Idade\n\n\t4 - Partidas pela selecao\n\n\t5 - Gols pela selecao\n\n\t6 - Time\n\n\t7 - Capitao");
                printf("\n\n\t=====================================================================================================");
                printf("\n");
                printf("\n\n\tDigite uma das opcoes: ");
                scanf("%d", &resp);
                switch (resp){
                case 1:
                    int novo_num;
                    printf("\tDigite o id do jogador e o novo numero da camisa: ");
                    scanf("%d %d",&id,&novo_num);
                    printf("\n\n\t=====================================================================================================");
                    Q12_1(raiz,id,novo_num);
                    break;
                case 2:
                    char nova_pos[20];
                    printf("\tDigite o id do jogador e a nova posicao: ");
                    scanf("%d %s",&id,nova_pos);
                    printf("\n\n\t=====================================================================================================");
                    Q12_2(raiz,id,nova_pos);
                    break;
                case 3:
                   int nova_idade;
                    printf("\tDigite o id do jogador e a nova idade: ");
                    scanf("%d %d",&id,&nova_idade);
                    printf("\n\n\t=====================================================================================================");
                    Q12_3(raiz,id,nova_idade);
                    break;
                case 4:
                    int nova_qtd;
                    printf("\tDigite o id do jogador e a nova quantidade de partidas: ");
                    scanf("%d %d",&id,&nova_qtd);
                    printf("\n\n\t=====================================================================================================");
                    Q12_4(raiz,id,nova_qtd);
                    break;
                case 5:
                    int nova_qtd_gols;
                    printf("\tDigite o id do jogador e a nova quantidade de partidas: ");
                    scanf("%d %d",&id,&nova_qtd_gols);
                    printf("\n\n\t=====================================================================================================");
                    Q12_5(raiz,id,nova_qtd_gols);
                    break;
                case 6:
                    char novo_time[20];
                    printf("\tDigite o id do jogador e o novo time: ");
                    scanf("%d %s",&id,novo_time);
                    printf("\n\n\t=====================================================================================================");
                    Q12_6(raiz,id,novo_time);
                    break;
                case 7:
                    int op;
                    printf("\tDigite o id e 1 para tornar e 0 para retirar: ");
                    scanf("%d %d", &id, &op);
                    printf("\n\n\t=====================================================================================================");
                    Q12_7(raiz, id, op, t);
                    break;  
                default:
                    if(resp != 0) printf("\tOpcao invalida!!!\n");
                    break;      
                }

            }while(resp);
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