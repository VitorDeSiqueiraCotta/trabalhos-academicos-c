#ifndef OPERATION_H_INCLUDED
#define OPERATION_H_INCLUDED

#define NAO_ENCONTRADO -9999

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct struct_bloco {
    int dado;
    struct struct_bloco *PTR_PROXIMO_BLOCO;
};

typedef struct struct_bloco TBlocos;

struct struct_pilha {
    TBlocos bloco;
    struct struct_pilha *PTR_PROXIMA_PILHA;
};

typedef struct struct_pilha TPilha;

void adicionarPilha(TPilha **listaPilhas, const TBlocos primeiroBloco);
TBlocos inicializarBloco(void);
TBlocos *localizarPilha(TPilha *listaPilhas, const int pilha);
void adicionarBloco(TBlocos** blocos, const int dado);
void removerBloco(TBlocos **blocos, const int posicaoBlocoRemovido);
void depuracao(TBlocos *blocos, const int pilha);
char * iteracaoLinha(TBlocos *blocos, const int pilha);
int obterPosicaoBloco(TBlocos *blocos, const int bloco);
int obterBloco(TBlocos *blocos, const int posicaoBloco);

#endif
