#include <stdio.h>
#include <stdlib.h>

#include "operacao.h"
#include "comandoBloco.h"
#include "manipularArquivo.h"

int main(const int argc, const char *argv[]) {

    gerarSaidaTXT(argv[2], (lerEntradaTXT(argv[1], argv[3])));

    return EXIT_SUCCESS;
}
