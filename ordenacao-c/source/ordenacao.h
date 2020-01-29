#ifndef ORDENACAO_H_INCLUDED
#define ORDENACAO_H_INCLUDED

#include "estrutura.h"

void quick_sort(StructEscola *registros, int primeiro, int ultimo);
void insertion_sort(StructEscola *registros, int qtRegistros);
void heap_sort(StructEscola *registros, int qtRegistros);
void temporizar_ordenacao(StructEscola *registros, const int qtRegistros, const char *tipo);

StructEscola busca_sequencial(const StructEscola *registros, const int id, const int qtRegistros);
StructEscola busca_binaria(const StructEscola *registros, const int id, const int qtRegistros);
void temporizar_busca(const StructEscola *registros, const int qtRegistros, const int tamanho_busca, const char *tipoBusca);

#endif
