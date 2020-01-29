#ifndef MANIPULARARQUIVO_H_INCLUDED
#define MANIPULARARQUIVO_H_INCLUDED

#include "ordenacao.h"

int obter_qt_registros(const char *diretorio);
void carregar_arquivo_enem(StructEscola *registros, const char *diretorio);
void carregar_arquivo_indice(StructEscola *registros, const int qtRegistros, const StructArgv argumentos);

#endif
