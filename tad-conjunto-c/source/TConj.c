#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "TConj.h"

/* Aloca mais 10 elementos no conjunto */
void alocar_elementos(TConj *x) {
    TConj aux;
    inicializar(&aux);
    /* Aloca um novo conjunto maior */
    aux.elementos = (int *)malloc(((x->tamanho / 10) * 10) * sizeof(int));

    /* Copia os dados do conjunto antigo */
    for (int i = 0; i < x->tamanho; ++i)
        inserir_elemento(&aux, x->elementos[i]);

    x = &aux;
}

void inicializar(TConj *x) {
    x->tamanho = 0;
    x->elementos = (int *)calloc(10, sizeof(int));
}

int inserir_elemento(TConj *x, const int elem){
    /* Expande o conjunto em 10 */
    if (x->tamanho % 10 == 0 && x->tamanho != 0)
        alocar_elementos(x);

    if (set_elemento(x, elem, x->tamanho)) {
        x->tamanho++;
        return SUCESSO;
    }
    return FRACASSO;
}

void gerar_conjunto(TConj *x) {
    srand(time(NULL));

    int n = 1 + rand() % 25;

    for(int i = 0; i < n; ++i)
        inserir_elemento(x, rand() % 25);
}

int remove_element(TConj *x, const int elem) {
    int pos = check_element(*x, elem);

    if(pos != -1) {
        for(int i = pos; i + 1 < x->tamanho; i++)
            x->elementos[i] = x->elementos[i + 1];

        x->tamanho--;
        return SUCESSO;
    }
    return FRACASSO;
}

/* Altera o valor de um elemento atraves da posicao */
int set_elemento(TConj *x, const int elem, const int pos) {
    if(pos >= 0 && pos <= x->tamanho && check_element(*x, elem) == -1) {
        x->elementos[pos] = elem;
        return SUCESSO;
    }
    return FRACASSO;
}

/* Localiza o elemento do conjunto atraves de uma posicao */
int get_elemento(TConj const x, const int pos, int *elem) {
    if(pos >= 0 && x.tamanho > pos) {
        *elem = x.elementos[pos];
        return SUCESSO;
    }
    return FRACASSO;
}

/* Verificar se o elemento pertence ao conjunto */
int check_element(TConj const x, const int elem) {
    for(int i = 0; i < x.tamanho; ++i)
        if(x.elementos[i] == elem)
            return i;

    return -1;
}

int conj_iguais(TConj const a, TConj const b) {
    if(a.tamanho == b.tamanho) {
        for(int i = 0; i < a.tamanho; ++i)
            if(check_element(b, a.elementos[i]) == -1)
                return FRACASSO;

        return SUCESSO;
    }
    return FRACASSO;
}

/* Exibe os elementos contidos no conjunto */
void print_conj(TConj const x) {
    if(x.tamanho == 0) {
        printf("[ ERROR ] - Nao ha elementos para ser exibido.\n");
        return;
    }

    printf("Tamanho: %d - [ ", x.tamanho);

    for(int i = 0; i < x.tamanho - 1; ++i)
        printf(" %d ", x.elementos[i]);

    /* Exibe ultimo elemento */
    printf(" %d ]\n", x.elementos[x.tamanho - 1]);
}

TConj uniao(TConj const a, TConj const b) {
    TConj resultado;
    inicializar(&resultado);

    for(int i = 0; i < a.tamanho; ++i)
        inserir_elemento(&resultado, a.elementos[i]);

    for(int i = 0; i < b.tamanho; ++i)
        inserir_elemento(&resultado, b.elementos[i]);

    return resultado;
}

/* Gera conjunto de intersecao a partir dos conjuntos A e B */
TConj inter(TConj const a, TConj const b) {
    TConj resutlado;
    inicializar(&resutlado);

    for(int i = 0; i < a.tamanho; ++i)
        if(check_element(b, a.elementos[i]) != -1)
            inserir_elemento(&resutlado, a.elementos[i]);

    return resutlado;
}

/* Gera um conjunto de elementos exclusivos de A em relacao ao B */
TConj subtrair(TConj const a, TConj const b) {
    TConj resultado;
    inicializar(&resultado);

    for(int i = 0; i < a.tamanho; ++i)
        if(check_element(b, a.elementos[i]) == -1)
            inserir_elemento(&resultado, a.elementos[i]);

    return resultado;
}

void limpaTelaPausa(void) {
    setbuf(stdin, NULL);
    printf("\n\nPressione ENTER para continuar...");
    getchar();
    system(CLEAR);
}
