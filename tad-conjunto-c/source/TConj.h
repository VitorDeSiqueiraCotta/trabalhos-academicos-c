#ifndef TCONJ_H_INCLUDED
#define TCONJ_H_INCLUDED

#define SUCESSO 1
#define FRACASSO 0

#ifdef _WIN32
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif

typedef struct TConj {
    int tamanho;
    int *elementos;
} TConj;

void inicializar(TConj *x);
int inserir_elemento(TConj *x, const int elem);
int remove_element(TConj *x, const int elem);

int set_elemento(TConj *x, const int elem, const int pos);
int get_elemento(const TConj x, const int pos, int *elem);
int check_element(const TConj x, const int elem);

int conj_iguais(const TConj a, const TConj b);
void print_conj(const TConj x);
void gerar_conjunto(TConj *x);

TConj inter(const TConj a, const TConj b);
TConj uniao(const TConj a, const TConj b);
TConj subtrair(const TConj a, const TConj b);

/* Funcoes auxiliares */
void alocar_elementos(TConj* pA);
void limpaTelaPausa(void);

#endif
