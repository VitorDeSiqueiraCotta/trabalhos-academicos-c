#ifndef COMANDOBLOCO_H_INCLUDED
#define COMANDOBLOCO_H_INCLUDED

#include "operacao.h"

void moveOnto(TPilha *listaPilhas, const int tamanhoLista, const int blocoA, const int blocoB);
void moveOver(TPilha *listaPilhas, const int tamanhoLista, const int blocoA, const int blocoB);
void pileOnto(TPilha *listaPilhas, const int tamanhoLista, const int blocoA, const int blocoB);
void pileOver(TPilha *listaPilhas, const int tamanhoLista, const int blocoA, const  int blocoB);

#endif
