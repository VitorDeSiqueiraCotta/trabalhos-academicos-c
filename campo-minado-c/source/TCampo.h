#ifndef TCAMPO_H_INCLUDED
#define TCAMPO_H_INCLUDED

#ifdef _WIN32
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif

typedef struct TQuadrado {
    char zona;
    int visitado;
} TQuadrado;

typedef struct TCampo {
    TQuadrado **TAB;
    int m;
    int n;
} TCampo;

void inicializar(TCampo *tabuleiro);
void imprimir(const TCampo tabuleiro);
void imprimirVisitado(TCampo tabuleiro);
void imprimirTeste(TCampo tabuleiro);
int validar_posicao(const int n, const int m, const int x, const int y);
int validar_bomba_adjacente(const TCampo tabuleiro, const int x, const int y);
int inserir_bomba(TCampo *tabuleiro, const int posx, const int posy);
int visitar_quadrado(TCampo *tabuleiro, const int posx, const int posy);
int bombas_adjacentes(TCampo *tabuleiro, const int posx, const int posy);
void solucionar_campo(TCampo tabuleiro);
TCampo gerar_campo_bombas(const int n, const int m, const int qt_bombas);
void freeTAB(TCampo *tabuleiro);
int qtRodadas(const TCampo tabuleiro);
TCampo menu(int *flagTeste);
void partida(TCampo tabuleiro, const int rodadas, const int flagTeste);
void limpaTelaPausa();

#endif
