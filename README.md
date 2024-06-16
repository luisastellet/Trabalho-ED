# Trabalho-ED
  O trabalho consistirá do gerenciamento de, pelo menos, algumas equipes da EURO 2024, usando uma
Árvore B em memória secundária. Seu programa deve receber como entrada os seguintes parâmetros:
→ o grau mínimo da árvore B (t); e
→ o catálogo inicial, seguindo o formato pré-definido.

  O formato do catálogo é o que segue:
-> nome do país em uma linha; e
-> nas n linhas restantes (UM POR LINHA, COM CAMPOS SEPARADOS POR ‘/’):

1. o identificador único do jogador;
2. o número da camisa que ele usa em sua respectiva seleção;
3. a posição que ele joga (GK - Goleiro, DF – Defensor, MF – Meio-campo e FW – Atacante);
4. o nome do jogador;
5. a sua data de nascimento;
6. o número de partidas pela seleção;
7. o número de gols pela respectiva seleção;
8. o país do seu time atual; e
9. o nome do time atual em que o jogador atua.

  O catálogo inicial deve ser salvo usando a estrutura de Árvore B em memória secundária. Isso quer informar
que cada nó da árvore B estará representada em um arquivo. Você só deve manter em memória principal as
informações dos arquivos que façam parte da operação a ser realizada no momento. Por exemplo, se você
está inserindo nessa árvore B, os arquivos do caminho da raiz até a folha onde ocorrerá a inserção podem
estar em memória principal.

As seguintes operações devem ser implementadas nesse trabalho:
1. Retorno do jogador mais novo e mais velho da competição, ilustrando essas mesmas informações
por seleções e por posições;
2. Os jogadores que mais e menos atuaram em suas equipes;
3. Os jogadores que mais e menos atuaram no total;
4. A menor e a maior seleção, isto é, com menos ou mais convocados;
5. Busca de todos os jogadores que atuam fora do seu país de origem;
6. Busca de todos os jogadores que atuam no seu país de origem;
7. Busca de todos os jogadores que nasceram no mesmo ano;
8. Busca de todos os jogadores que nasceram no mesmo mês;
9. Busca da(s) seleção(ções) com mais jogadores que atuam fora do seu país de origem;
10. Busca da(s) seleção(ções) com mais jogadores que atuam no seu país de origem;
11. Busca das informações subordinadas, dadas a chave primária (identificador único do jogador);
12. Alteração SOMENTE de algumas informações, por exemplo, número da camisa que ele usa em
sua respectiva seleção, a posição que ele joga (EXCETO GK), o número de partidas pela seleção, o
número de gols, o jogador passar a (ou deixar de) ser capitão, o país do seu time atual e o nome do
time atual;
13. Busca de todos os jogadores de uma seleção;
14. Busca e remoção de todos os capitães;
15. Remoção de jogadores a partir de uma determinada idade;
16. Retirada de todos os jogadores de uma seleção que atuam num determinado país;
17. Retirada de todos os os jogadores de uma seleção que não atuam no país de origem;
18. Retirada de todos os os jogadores de uma seleção atuam fora do país de origem;
19. Retirada de todos os os jogadores de uma seleção; e
20. Remoção de jogadores, dado um conjunto contendo suas chaves primárias.
