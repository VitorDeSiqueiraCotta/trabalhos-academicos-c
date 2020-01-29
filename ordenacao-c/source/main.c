#include <stdio.h>
#include <stdlib.h>
#include "estrutura.h"
#include "ordenacao.h"
#include "manipularArquivo.h"

int main(const int argc, const char *argv[]) {
    int qtRegistros = obter_qt_registros("dados-enem.txt");

    StructEscola *registros = (StructEscola *)malloc(sizeof(StructEscola) * qtRegistros);

    carregar_arquivo_enem(registros, "dados-enem.txt");

    limpar_tela_pausar();

    if(argc > 1)
        carregar_argumentos(registros, qtRegistros ,argc, argv);
    else
        menu(registros, qtRegistros);

    free(registros);

    return EXIT_SUCCESS;
}
