#include "manipularArquivo.h"

char *lerEntradaTXT(const char *nomeArqvEntradaTXT, const char *paramentroTela) {
    FILE *arqvEntradaTXT = fopen(nomeArqvEntradaTXT, "r");

    if (arqvEntradaTXT == NULL)
        return 0;

    char operacao[128], subOperacao[128], leitura[128];
    int blocoA, blocoB, tamanhoPilha;

    /* PEGA A PRIMEIRA LINHA QUE REPRESENTA O NUMERO DE PILHAS */
    fgets(leitura, 128, arqvEntradaTXT);
    tamanhoPilha = atoi(leitura);

    TPilha *pilhas = NULL;
    TBlocos *auxBloco = NULL;

    /* INICIALIZA AS PILHAS COM O BLOCOS */
    for(int i = 0; i < tamanhoPilha; ++i) {
        adicionarPilha(&pilhas, inicializarBloco());
        auxBloco = localizarPilha(pilhas, i);
        adicionarBloco(&auxBloco, i);
    }

    /* IMPRIME ANTES DA PRIMEIRA ITERACAO */
    if(!strcmp("-p", paramentroTela)) {
        for(int i = 0; i < tamanhoPilha; ++i) {
            auxBloco = localizarPilha(pilhas, i);
            depuracao(auxBloco, i);
        }
        printf("\n");
    }

    while (!feof(arqvEntradaTXT)) {
        fgets(leitura, 128, arqvEntradaTXT);
        strcpy(operacao, strtok(leitura , " "));

        /* ENCERRA O PROGRAMA */
        if(!strcmp(operacao, "quit"))
            break;

        blocoA = atoi(strtok(NULL , " "));
        strcpy(subOperacao, strtok(NULL, " "));
        blocoB = atoi(strtok(NULL , " "));

        /* REALIZA A OPERACAO */
        if(!strcmp(operacao,"pile")) {
            if(!strcmp(subOperacao,"onto"))
                pileOnto(pilhas, tamanhoPilha, blocoA, blocoB);
            else if(!strcmp(subOperacao,"over"))
                pileOver(pilhas, tamanhoPilha, blocoA, blocoB);
        }
        else if(!strcmp(operacao,"move")) {
            if(!strcmp(subOperacao,"onto"))
                moveOnto(pilhas, tamanhoPilha, blocoA, blocoB);
            else if(!strcmp(subOperacao,"over"))
                moveOver(pilhas, tamanhoPilha, blocoA, blocoB);
        }

        /* IMPRIME A ITERACAO */
        if(!strcmp("-p", paramentroTela)) {
            for(int i = 0; i < tamanhoPilha; i++) {
                auxBloco = localizarPilha(pilhas, i);
                depuracao(auxBloco, i);
            }
            printf("\n");
        }
    }

    fclose(arqvEntradaTXT);
    arqvEntradaTXT = NULL;

    char *resultadoTXT = malloc(sizeof(char) * 512);
    sprintf(resultadoTXT, "%s","");

    /* CONSTROI A STRING QUE SERA O ARQUIVO DE SAIDA */
    for(int i = 0; i < tamanhoPilha; ++i) {
        auxBloco = localizarPilha(pilhas, i);
        sprintf(resultadoTXT, "%s%s",resultadoTXT, iteracaoLinha(auxBloco, i));
    }

    return resultadoTXT;
}

void gerarSaidaTXT(const char *nomeArqvSaidaTXT, char *iteracaoLinha) {
    FILE *arqvSaidaTXT = fopen(nomeArqvSaidaTXT, "w");

    if(arqvSaidaTXT != NULL) {
        fprintf(arqvSaidaTXT, "%s", iteracaoLinha);
        fclose(arqvSaidaTXT);
        arqvSaidaTXT = NULL;
    }
}
