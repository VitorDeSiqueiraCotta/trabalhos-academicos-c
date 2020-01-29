#ifndef ESTRUTURA_H_INCLUDED
#define ESTRUTURA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

#ifdef _WIN32
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif

struct StructArgv {
    int id;
    char tipoBusca[3];
    char tipoOrdenacao[3];
    char imprimir[3];
    char diretorio[256];
};
typedef struct StructArgv StructArgv;

struct StructEscola {
    int ID;
    char estado[3];
    char municipio[32];
    char rede[16];
    float media_ciencias_natureza;
    float media_ciencias_humanas;
    float media_linguagem;
    float media_matematica;
    float media_redacao;
};
typedef struct StructEscola StructEscola;

StructEscola resgistro_vazio(void);

void imprimir_registro(const StructEscola registro);
void imprimir_todos_registros(const StructEscola *registros, const int qtRegistros);

void ordenar(StructEscola *registros, const int qtRegistros);
void busca(const StructEscola *registros, const int ID, const int qtRegistros);

void carregar_argumentos(StructEscola *registros, const int qtRegistros, const int argc, const char *argv[]);
void menu(StructEscola *registros, const int qtRegistros);

void limpar_tela_pausar(void);
void limpar_tela(void);

#endif
