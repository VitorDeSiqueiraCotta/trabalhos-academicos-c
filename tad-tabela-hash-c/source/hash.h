#ifndef HASH_H_INCLUDED
#define HASH_H_INCLUDED

#define SUCESSO 1
#define FRACASSO 0

#ifdef _WIN32
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif

void menu(void);

void inicializarTabelaHash(void);
int criarElementos(void);
int gerarHash(const int chave);
int indiceCondicaoParada(const int chave);
void calcularCusto(void);

int inserir(const int chave, const float valor);
int removerElemento(const int chave);
int pesquisar(const int chave);
int alterar(const int chave, const float valor);
void exibirTabelaHash(void);
void exibirClusters(void);

void limpaTelaPausa(void);

#endif
