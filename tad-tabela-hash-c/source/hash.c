#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include "hash.h"

int tamanhoHash = 0;
int qtElementos = 0;
int *ptChaves;
int *ptValores;

void inicializarTabelaHash(void) {
    int entrada;

    tamanhoHash = 0;
    qtElementos = 0;

    printf("\nInforme o tamanho da tabela hash: ");
    scanf("%d", &tamanhoHash);

    ptChaves  = (int *)malloc(sizeof(int) * tamanhoHash);
    ptValores = (int *)malloc(sizeof(int) * tamanhoHash);

    for(int i = 0; i < tamanhoHash; ++i)  {
        ptChaves[i]  = -1;
        ptValores[i] = -1;
    }

    printf("\nDeseja gerar elementos aleatorios?\n\n1. Sim \n2. Nao\n\n-->");
    scanf("%d", &entrada);

    if(entrada < 1 && entrada > 2)
        printf("\n[ WARNING ] - Por favor insira a entrada correta.\n\n");

    if(entrada == 1)
        criarElementos();
}

int criarElementos(void) {
    int entrada;

    printf("\nPor favor, informe a quantidade de elementos: ");
    scanf("%d", &entrada);

    if(entrada > tamanhoHash) {
        printf("\n[ WARNING ] - Nao foi possivel gerar, a quantidade de "
               "elementos deve ser menor do que o tamanho da tabela.\n\n");
        return FRACASSO;
    }

    srand(time(NULL));

    /* A razão de usar a função rand() duas vezes é devido para expandir o
       intervalo, pois somente com 1 rand() só irá gerar até 32767
       possibilidades diferentes */
    for(int i = 0; i < entrada; ++i)
        inserir(rand() * rand(), i);

    return SUCESSO;
}

int gerarHash(const int chave) {
    return (chave & INT_MAX) % tamanhoHash;
}

int indiceCondicaoParada(const int chave) {
    int indice = gerarHash(chave);
    /* Caso indice seja diferente de 0 */
    if(indice)
        return tamanhoHash - 1;
    /* Indice anterior */
    else
        return indice - 1;
}

int inserir(const int chave, const float valor) {
    int i;
    int indiceFinal = indiceCondicaoParada(chave);

    for(i = gerarHash(chave); ptChaves[i] != -1; i = (i + 1) % tamanhoHash) {
        if(ptChaves[i] == chave)
            break;
        else if(i == indiceFinal)
            return FRACASSO;
    }

    ptChaves[i] = chave;
    ptValores[i] = valor;
    ++qtElementos;

    return SUCESSO;
}

void exibirTabelaHash(void) {
    printf("\n*============================================================*\n"
           "| Indice  | Chave      | Indice gerado | Distancia | Valor   |\n"
           "*============================================================*\n");

    for(int i = 0; i < tamanhoHash; ++i) {
        if(ptChaves[i] != -1) {
            printf("| %7d | %10d | %13d | %9d | %7d |\n",
                   i, ptChaves[i], gerarHash(ptChaves[i]),
                   i - gerarHash(ptChaves[i]), ptValores[i]);
        }
    }
    printf("*============================================================*\n");
}

void calcularCusto(void) {
    float custoSearchMiss = 0.0;
    float custoSearchInsert = 0.0;
    int cluster = 0;
    int flag = 0;

    for(int i = 0; i < tamanhoHash; ++i) {
        if(ptChaves[i] == -1)
            flag = 0;

        if(flag == 0 && ptChaves[i] != -1) {
            ++cluster;
            flag = 1;
        }

        /* Cálculo do custo médio de SEARCH INSERT */
        if(ptChaves[i] != -1) {
            if(i == gerarHash(ptChaves[i])) {
                /* Elemento está no indice HASH correto */
                custoSearchInsert = custoSearchInsert + (1/(float)qtElementos);
            }
            else {
                /* Elemento distante do indice HASH */
                custoSearchInsert = custoSearchInsert + (1/(float)qtElementos) *
                (1 + i - gerarHash(ptChaves[i]));
            }
        }
    }

    /* Cálculo de SEARCH MISS. */
    custoSearchMiss = (float)qtElementos/cluster;

    printf("\nTamanho da tabela: %d\n", tamanhoHash);
    printf("Quantidade de elementos: %d\n", qtElementos);
    printf("Quantidade de grupos: %d\n", cluster);
    printf("Custo medio do Search Miss: %.3f\n", custoSearchMiss);
    printf("Custo medio do Search Insert: %.3f\n", custoSearchInsert);
}

void exibirClusters(void) {
    printf("\nCLUSTERS\n");

    for(int i = 0; i < tamanhoHash; ++i) {
        if(i % 50 == 0)
            printf("\n");

        ptChaves[i] != -1 ? printf("*") : printf("_");
    }
}

int removerElemento(const int chave) {
    int i = 0;
    int auxChave = 0;
    float auxValor = 0;

    for(i = gerarHash(chave); ptChaves[i] != -1; i = (i + 1) % tamanhoHash)
        if (chave == ptChaves[i])
            break;

    if(ptChaves[i] == -1)
        return FRACASSO;

    /* Elemento localizado e removido. */
    ptChaves[i] = -1;
    ptValores[i] = -1;
    --qtElementos;

    /* Reposiciona elementos com mesmo índice do elemento removido. */
    for(i = (i + 1) % tamanhoHash; ptChaves[i] != -1; i = (i + 1) % tamanhoHash) {
        auxChave = ptChaves[i];
        auxValor = ptValores[i];

        ptChaves[i] = -1;
        ptValores[i] = -1;

        inserir(auxChave, auxValor);
        --qtElementos;
    }
    return SUCESSO;
}

int alterar(const int chave, const float valor) {
    int i;

    for(i = gerarHash(chave); ptChaves[i] != -1; i = (i + 1) % tamanhoHash)
        if(chave == ptChaves[i])
            break;

    if(ptChaves[i] == -1)
        return FRACASSO;

    /* Valor alterado. */
    ptValores[i] = valor;

    return SUCESSO;
}

int pesquisar(const int chave) {
    int i;

    for(i = gerarHash(chave); ptChaves[i] != -1; i = (i + 1) % tamanhoHash)
        if (chave == ptChaves[i])
            break;

    if(ptChaves[i] == -1)
        return FRACASSO ;

    printf("\nIndice: %d\n", i);
    printf("Chave: %d\n", chave);
    printf("Valor: %d\n", ptValores[i]);

    return SUCESSO;
}

void menu(void) {
    int chave = 0;
    float valor = 0;

    for(int OP = 1; OP != 0;) {
        printf("[ MENU TAD HASH ]\n\n"
               "0 - Sair do programa\n"
               "1 - Gerar tabela hash\n"
               "2 - Inserir elemento\n"
               "3 - Remover elemento\n"
               "4 - Alterar elemento\n"
               "5 - Pesquisar elemento\n"
               "6 - Exibir clusters\n"
               "7 - Exibir elementos da tabela hash\n"
               "8 - Calcular custo medio\n\n"
               "-> ");

        scanf("%d", &OP);

        system(CLEAR);

        switch(OP) {

        case 0:
            printf("\nEncerrando o programa.\n");
            break;

        case 1:
            inicializarTabelaHash();
            break;

        case 2:
            printf("\nChave do elemento a ser inserido: ");
            scanf("%d", &chave);

            printf("\nValor do elemento a ser inserido: ");
            scanf("%f", &valor);

            if(inserir(chave, valor))
                printf("\nSucesso na insercao.\n");
            else
                printf("\n[ WARNING ] - Fracasso na insercao.\n");

            break;

        case 3:
            printf("\nPor favor, insira a chave do elemento a ser removido: ");
            scanf("%d", &chave);

            if(removerElemento(chave))
                printf("\nSucesso na remocao.\n");
            else
                printf("\n[ WARNING ] - Fracasso na remocao.\n");

            break;

        case 4:
            printf("\nChave do elemento a ser alterado: ");
            scanf("%d", &chave);

            printf("\nValor do elemento a ser alterado: ");
            scanf("%f", &valor);

            if(alterar(chave, valor))
                printf("\nSucesso na alteracao.\n");
            else
                printf("\n[ WARNING ] - Fracasso na alteracao.\n");

            break;

        case 5:
            printf("\nChave do elemento a ser pesquisado: ");
            scanf("%d", &chave);

            if(!pesquisar(chave))
                printf("\n[ WARNING ] - Chave nao encontrada.");

            break;

        case 6:
            exibirClusters();
            break;

        case 7:
            exibirTabelaHash();
            break;

        case 8:
            calcularCusto();
            break;

        default:
            printf("\n[ WARNING ] - Entrada invalida, tente novamente.\n");
            break;
        }
        limpaTelaPausa();
    }
}

void limpaTelaPausa(void) {
    setbuf(stdin, NULL);
    printf("\n\nPressione ENTER para continuar...");
    getchar();
    system(CLEAR);
}
