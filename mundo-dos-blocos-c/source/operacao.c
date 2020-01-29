#include "operacao.h"
#include "comandoBloco.h"

void adicionarPilha(TPilha **listaPilhas, const TBlocos primeiroBloco) {
    TPilha *novaPilha = (TPilha *)malloc(sizeof(TPilha));
    TPilha *ultimaPosicao = *listaPilhas;

    novaPilha->bloco = primeiroBloco;
    novaPilha->PTR_PROXIMA_PILHA = NULL;

    /* CASO SEJA A PRIMEIRA PILHA SER ADICIONADO */
    if (*listaPilhas == NULL) {
        *listaPilhas = novaPilha;
        return;
    }

    /* ENCONTRA O ULTIMO PONTEIRO QUE SERA ADICIONADO A PILHA */
    while (ultimaPosicao->PTR_PROXIMA_PILHA != NULL)
        ultimaPosicao = ultimaPosicao->PTR_PROXIMA_PILHA;

    ultimaPosicao->PTR_PROXIMA_PILHA = novaPilha;
}

TBlocos inicializarBloco(void) {
    TBlocos *tempo = (TBlocos *)malloc(sizeof(TBlocos));
    tempo->PTR_PROXIMO_BLOCO = NULL;
    tempo->dado = NAO_ENCONTRADO;
    return *tempo;
}

TBlocos *localizarPilha(TPilha *listaPilhas, const int pilha) {
    for(int i = 0; i < pilha; ++i)
        listaPilhas = listaPilhas->PTR_PROXIMA_PILHA;
    return &listaPilhas->bloco;
}

void adicionarBloco(TBlocos** blocos, const int dado) {
    if(dado == NAO_ENCONTRADO)
        return;

    TBlocos *blocoNovo = (TBlocos *)malloc(sizeof(TBlocos));;
    TBlocos *ultimoBloco = *blocos;

    blocoNovo->dado = dado;
    blocoNovo->PTR_PROXIMO_BLOCO = NULL;

    /* ASSEGURA QUE O BLOCO NAO SEJA NULO */
    if(*blocos == NULL) {
        *blocos = blocoNovo;
        return;
    }

    /* ENCONTRA O ULTIMO PONTEIRO QUE SERA ADICIONADO O BLOCO */
    while (ultimoBloco->PTR_PROXIMO_BLOCO != NULL)
        ultimoBloco = ultimoBloco->PTR_PROXIMO_BLOCO;

    ultimoBloco->PTR_PROXIMO_BLOCO = blocoNovo;
}

void removerBloco(TBlocos **blocos, const int posicaoBlocoRemovido) {
    TBlocos* tempBloco = *blocos;

    if(*blocos == NULL)
        return;

    /* CASO O BLOCO A SER REMOVIDO SEJA A BASE DA PILHA */
    if(posicaoBlocoRemovido == 0) {
        *blocos = tempBloco->PTR_PROXIMO_BLOCO;
        free(tempBloco);
        return;
    }

    /* LOCALIZA O PONTEIRO DO BLOCO A SER REMOVIDO */
    for(int i = 0; tempBloco != NULL && i < posicaoBlocoRemovido - 1; ++i)
        tempBloco = tempBloco->PTR_PROXIMO_BLOCO;

    /* CONFERE SE EH VALIDO O PONTEIRO */
    if(tempBloco == NULL || tempBloco->PTR_PROXIMO_BLOCO == NULL)
        return;

    TBlocos *PTR_BLOCO_SUBSTITUTO;

    PTR_BLOCO_SUBSTITUTO = tempBloco->PTR_PROXIMO_BLOCO->PTR_PROXIMO_BLOCO;

    /* BLOCO APAGADO */
    free(tempBloco->PTR_PROXIMO_BLOCO);
    tempBloco->PTR_PROXIMO_BLOCO = NULL;

    /* REFERENCIA REPOSICIONADO */
    tempBloco->PTR_PROXIMO_BLOCO = PTR_BLOCO_SUBSTITUTO;
}

/* EXIBE NA TELA COMO ESTA A PILHA */
void depuracao(TBlocos *blocos, const int pilha) {
    blocos = blocos->PTR_PROXIMO_BLOCO;
    printf("%d: ", pilha);

    while (blocos != NULL) {
        printf("%d ", blocos->dado);
        blocos = blocos->PTR_PROXIMO_BLOCO;
    }
    printf("\n");
}

/*  RETORNA UMA LINHA DA STRING QUE SERA ARMAZENADO NO ARQUIVO SAIDA.TXT
    E ESSA LINHA REPRESENTA A PILHA
*/
char *iteracaoLinha(TBlocos *blocos, const int pilha) {
    char *operaLinha = (char *)malloc(sizeof(char) * 128);

    strcpy(operaLinha,"");
    sprintf(operaLinha, "%s%d: ", operaLinha, pilha);

    blocos = blocos->PTR_PROXIMO_BLOCO;

    while (blocos != NULL) {
        sprintf(operaLinha, "%s%d ", operaLinha, blocos->dado);
        blocos = blocos->PTR_PROXIMO_BLOCO;
    }

    sprintf(operaLinha, "%s%s",operaLinha, "\n");

    return operaLinha;
}

int obterPosicaoBloco(TBlocos *blocos, const int bloco) {
    int i = 0;

    if(blocos == NULL)
        return NAO_ENCONTRADO;

    do {
        if(blocos->dado == bloco)
            return i;

        ++i;
        blocos = blocos->PTR_PROXIMO_BLOCO;
    }
    while(blocos != NULL);

    return NAO_ENCONTRADO;
}

int obterBloco(TBlocos *blocos, const int posicaoBloco) {
    for(int i = 0; i < posicaoBloco; ++i)
        if(blocos != NULL)
            blocos = blocos->PTR_PROXIMO_BLOCO;

    if(blocos == NULL)
        return NAO_ENCONTRADO;

    return blocos->dado;
}
