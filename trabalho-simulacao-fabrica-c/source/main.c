#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "func.h"

int main(void) {
    srand(time(NULL));

    int qtMaquinas = 0;
    int tempo = 0;
    int op = 0;

    while(true) {
        printf("Insira a quantidade de maquinas: ");

        if(scanf("%d", &qtMaquinas) != 1) {
            printf("[ ERROR ] - Insira somente numeros!\n");
            setbuf(stdin, NULL);
            continue;
        }

        if(qtMaquinas <= 0) {
            printf("[ ERROR ] - Insira valores maiores do que 0!\n");
            continue;
        }
        break;
    }

    T_ListaMaquina listaMaquina;
    instanciarListaMaquina(&listaMaquina);

    for(int i = 0; i < qtMaquinas; i++)
        inserirMaquina(&listaMaquina);

    T_Maquina *AUX, *maquinaMenorFila;
    T_Maquina estatisticaDiario = instanciarMaquina();
    T_Maquina estatisticaFinal = instanciarMaquina();

    float lucroTotal = 0, prejuizoTotal = 150000 * qtMaquinas;

    /* 15.552.000 equivale 6 meses em segundos. */
    for(tempo = 1; tempo <= 15552000; ++tempo) {
        /* Cada 2 segundos um produto e inserido. */
        if(tempo % 2 == 0) {
            AUX = listaMaquina.primeiro->prox;
            maquinaMenorFila = AUX;

            while(AUX != NULL) {
                if(maquinaMenorFila->campo.qtProduto > AUX->campo.qtProduto)
                    maquinaMenorFila = AUX;

                AUX = AUX->prox;
            }
            inserirProduto(probabilidade(tempo), maquinaMenorFila);
        }

        /* Hora de funcionamento para calcular energia, uma hora tem 3600
        segundos, se o resto da divisao for igual a 0 logo teremos uma hora. */
        if(tempo % 3600 == 0) {
            for(AUX = listaMaquina.primeiro->prox; AUX != NULL; AUX = AUX->prox) {
                AUX->campo.horaFuncionamento++;
                estatisticaFinal.campo.horaFuncionamento++;
            }
        }

        /* Confere se o produto sera descartado ou embalado e armazena o
        resultado da operacao da variavel op nas estatittica diario e final. */
        for(AUX = listaMaquina.primeiro->prox; AUX != NULL; AUX = AUX->prox) {
            op = empacotar(AUX, tempo);
            atualizarEstatistica(&estatisticaDiario, op);
            atualizarEstatistica(&estatisticaFinal, op);
        }

        /* Estatistica diária, um dia tem 86400 segundos, se o resto da divisão
        for 0, logo teremos um dia completo. */
        if(tempo % 86400 == 0) {
            int dia = tempo/86400;
            /* 22 = consumo por maquina KWh, 24 = horas do dia. */
            float energia = qtMaquinas * 22 * 24;
            float lucroDiario = estatisticaDiario.campo.qtAlmondega * 0.4 +
                                estatisticaDiario.campo.qtCoxinha * 0.65 +
                                estatisticaDiario.campo.qtPeixe * 1.3;
            float prejuizoDiario = estatisticaDiario.campo.qtDescarteAlmondega * 0.4 +
                                   estatisticaDiario.campo.qtDescarteCoxinha * 0.8 +
                                   estatisticaDiario.campo.qtDescartePeixe * 0.7;
            float saldo = lucroDiario - prejuizoDiario - energia;

            lucroTotal += lucroDiario;
            prejuizoTotal += prejuizoDiario + energia;

            printEstatisticaDiaria(estatisticaDiario, saldo, energia, lucroDiario, prejuizoDiario, dia);

            /* Limpa a estatistica para recomecar o proximo dia. */
            estatisticaDiario = instanciarMaquina();
        }

        if(lucroTotal >= prejuizoTotal) {
            resultadoFinal(estatisticaFinal, listaMaquina, tempo/86400);
            return EXIT_SUCCESS;
        }
    }

    printf("\n\n####### RESULTADO DA SIMULACAO #######\n\n");
    printf("Simulacao de %d maquinas gera prejuizo.\n\n", qtMaquinas);

    return EXIT_SUCCESS;
}
