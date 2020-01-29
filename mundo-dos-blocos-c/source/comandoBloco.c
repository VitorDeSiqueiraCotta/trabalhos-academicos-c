#include "comandoBloco.h"

void moveOnto(TPilha *listaPilhas, const int tamanhoLista, const int blocoA, const int blocoB) {
    int pilha = 0, posicao = 0, novaPosicao;
    TBlocos *blocoTemp;

    /* ENCONTRA O BLOCO A */
    for(int i = 0; i < tamanhoLista; ++i) {
        blocoTemp = localizarPilha(listaPilhas, i);
        if(NAO_ENCONTRADO != obterPosicaoBloco(blocoTemp, blocoA)) {
            pilha = i;
            posicao = obterPosicaoBloco(blocoTemp, blocoA);
        }
    }

    blocoTemp = localizarPilha(listaPilhas, pilha);
    novaPosicao = obterBloco(blocoTemp, posicao + 1);

    /* TODOS OS BLOCOS ACIMA DO "BLOCO A" DEVOLVIDA NO LUGUAR */
    while(novaPosicao != NAO_ENCONTRADO) {
        removerBloco(&blocoTemp, posicao + 1);
        blocoTemp = localizarPilha(listaPilhas, novaPosicao);
        adicionarBloco(&blocoTemp, novaPosicao);
        blocoTemp = localizarPilha(listaPilhas, pilha);
        novaPosicao = obterBloco(blocoTemp, posicao + 1);
    } while(novaPosicao != NAO_ENCONTRADO);

    removerBloco(&blocoTemp, posicao);

    /* ENCONTRA O BLOCO B */
    for(int i = 0; i < tamanhoLista; ++i) {
        blocoTemp = localizarPilha(listaPilhas, i);
        if(NAO_ENCONTRADO != obterPosicaoBloco(blocoTemp, blocoB)) {
            pilha = i;
            posicao = obterPosicaoBloco(blocoTemp, blocoB);
        }
    }

    blocoTemp = localizarPilha(listaPilhas, pilha);
    novaPosicao = obterBloco(blocoTemp, posicao + 1);

    /* TODOS OS BLOCOS ACIMA DO "BLOCO B" DEVOLVIDA NO LUGUAR */
    while(novaPosicao != NAO_ENCONTRADO) {
        removerBloco(&blocoTemp, posicao + 1);
        blocoTemp = localizarPilha(listaPilhas, novaPosicao);
        adicionarBloco(&blocoTemp, novaPosicao);
        blocoTemp = localizarPilha(listaPilhas, pilha);
        novaPosicao = obterBloco(blocoTemp, posicao + 1);
    }

    /* BLOCO A ACIMA DO B */
    blocoTemp = localizarPilha(listaPilhas, pilha);
    adicionarBloco(&blocoTemp, blocoA);
}

void moveOver(TPilha *listaPilhas, const int tamanhoLista, const int blocoA, const int blocoB) {
    int pilha = 0, posicao = 0, novaPosicao;
    TBlocos *blocoTemp;

    /* ENCONTRA O BLOCO A */
    for(int i = 0; i < tamanhoLista; ++i) {
        blocoTemp = localizarPilha(listaPilhas, i);
        if(NAO_ENCONTRADO != obterPosicaoBloco(blocoTemp, blocoA)) {
            pilha = i;
            posicao = obterPosicaoBloco(blocoTemp, blocoA);
        }
    }

    blocoTemp = localizarPilha(listaPilhas, pilha);
    novaPosicao = obterBloco(blocoTemp, posicao + 1);

    /* TODOS OS BLOCOS ACIMA DO "BLOCO B" DEVOLVIDA NO LUGUAR */
    while(novaPosicao != NAO_ENCONTRADO) {
        removerBloco(&blocoTemp, posicao + 1);
        blocoTemp = localizarPilha(listaPilhas, novaPosicao);
        adicionarBloco(&blocoTemp, novaPosicao);
        blocoTemp = localizarPilha(listaPilhas, pilha);
        novaPosicao = obterBloco(blocoTemp, posicao + 1);
    }

    removerBloco(&blocoTemp, posicao);

    /* ENCONTRA O BLOCO B */
    for(int i = 0; i < tamanhoLista; ++i) {
        blocoTemp = localizarPilha(listaPilhas, i);
        if(NAO_ENCONTRADO != obterPosicaoBloco(blocoTemp, blocoB)) {
            pilha = i;
            posicao = obterPosicaoBloco(blocoTemp, blocoB);
        }
    }

    blocoTemp = localizarPilha(listaPilhas, pilha);
    adicionarBloco(&blocoTemp, blocoA);
}

void pileOnto(TPilha *listaPilhas, const int tamanhoLista, const int blocoA, const int blocoB) {
    int pilhaA = 0, pilhaB = 0, posicao = 0, novaPosicao;
    TBlocos *blocoTemp;

    /* ENCONTRA O BLOCO B */
    for(int i = 0; i < tamanhoLista; ++i) {
        blocoTemp = localizarPilha(listaPilhas, i);
        if(NAO_ENCONTRADO != obterPosicaoBloco(blocoTemp, blocoB)) {
            pilhaB = i;
            posicao = obterPosicaoBloco(blocoTemp, blocoB);
        }
    }

    blocoTemp = localizarPilha(listaPilhas, pilhaB);
    novaPosicao = obterBloco(blocoTemp, posicao + 1);

    /* DEVOLVE OS BLOCOS ACIMA DE "B" */
    while(novaPosicao != NAO_ENCONTRADO) {
        removerBloco(&blocoTemp, posicao + 1);
        blocoTemp = localizarPilha(listaPilhas, novaPosicao);
        adicionarBloco(&blocoTemp, novaPosicao);
        blocoTemp = localizarPilha(listaPilhas, pilhaB);
        novaPosicao = obterBloco(blocoTemp, posicao + 1);
    }

    /* ENCONTRA O BLOCO A */
    for(int i = 0; i < tamanhoLista; ++i) {
        blocoTemp = localizarPilha(listaPilhas, i);
        if(NAO_ENCONTRADO != obterPosicaoBloco(blocoTemp, blocoA)) {
            pilhaA = i;
            posicao = obterPosicaoBloco(blocoTemp, blocoA);
        }
    }

    blocoTemp = localizarPilha(listaPilhas, pilhaA);
    novaPosicao = obterBloco(blocoTemp, posicao);

    /* MOVE A PILHA DO "BLOCO A" ACIMA DO "BLOCO B" */
    while(novaPosicao != NAO_ENCONTRADO) {
        removerBloco(&blocoTemp, posicao);
        blocoTemp = localizarPilha(listaPilhas, pilhaB);
        adicionarBloco(&blocoTemp, novaPosicao);
        blocoTemp = localizarPilha(listaPilhas, pilhaA);
        novaPosicao = obterBloco(blocoTemp, posicao);
    }
}

void pileOver(TPilha *listaPilhas, const int tamanhoLista, const int blocoA, const  int blocoB) {
    int pilhaA, pilhaB, novaPosicao, posicao;
    TBlocos *blocoTemp;

    /* ENCONTRA O BLOCO B */
    for(int i = 0; i < tamanhoLista; ++i) {
        blocoTemp = localizarPilha(listaPilhas, i);
        if(NAO_ENCONTRADO != obterPosicaoBloco(blocoTemp, blocoB))
            pilhaB = i;
    }

    /* ENCONTRA O BLOCO A */
    for(int i = 0; i < tamanhoLista; ++i) {
        blocoTemp = localizarPilha(listaPilhas, i);
        if(NAO_ENCONTRADO != obterPosicaoBloco(blocoTemp, blocoA)) {
            pilhaA = i;
            posicao = obterPosicaoBloco(blocoTemp, blocoA);
        }
    }

    blocoTemp = localizarPilha(listaPilhas, pilhaA);
    novaPosicao = obterBloco(blocoTemp, posicao);

    /* MOVE A PILHA DO "BLOCO A" ACIMA DO "BLOCO B" */
    while(novaPosicao != NAO_ENCONTRADO) {
        removerBloco(&blocoTemp, posicao);
        blocoTemp = localizarPilha(listaPilhas, pilhaB);
        adicionarBloco(&blocoTemp, novaPosicao);
        blocoTemp = localizarPilha(listaPilhas, pilhaA);
        novaPosicao = obterBloco(blocoTemp, posicao);
    }
}
