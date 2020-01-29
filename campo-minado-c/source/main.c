#include <stdio.h>
#include <stdlib.h>
#include "TCampo.h"

int main(void) {
    int OP = 0;
    int flagTeste = 0;

    TCampo campoMinado;

    do {
        flagTeste = 0;
        campoMinado = menu(&flagTeste);
        partida(campoMinado, qtRodadas(campoMinado), flagTeste);

        printf("Deseja jogar novamente?\n\n"
               "1 - SIM\n"
               "0 - NAO\n\n"
               "OP: ");
        scanf("%d", &OP);
    }
    while(OP == 1);

    freeTAB(&campoMinado);

    return EXIT_SUCCESS;
}
