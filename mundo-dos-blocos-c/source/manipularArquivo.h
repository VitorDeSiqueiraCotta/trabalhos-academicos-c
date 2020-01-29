#ifndef MANIPULARARQUIVO_H_INCLUDED
#define MANIPULARARQUIVO_H_INCLUDED

#include "operacao.h"
#include "comandoBloco.h"

char *lerEntradaTXT(const char *nomeArqvEntradaTXT, const char *paramentroTela);
void gerarSaidaTXT(const char *nomeArqvSaidaTXT, char *iteracaoLinha);

#endif
