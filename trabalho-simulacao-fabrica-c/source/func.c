#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "func.h"

T_Produto probabilidade(const int instanteEntrada) {
    int PROB = 1 + rand() % 10;

    if(PROB >= 1 && PROB <= 5)
        return instanciarCoxinha(instanteEntrada);
    else if(PROB >= 6 && PROB <= 8)
        return instanciarPeixe(instanteEntrada);

    return instanciarAlmondega(instanteEntrada);
}

void instanciarListaMaquina(T_ListaMaquina *listaMaquina) {
    listaMaquina->primeiro = (T_Maquina *) malloc(sizeof(T_Maquina));
    listaMaquina->ultimo = listaMaquina->primeiro;
    listaMaquina->primeiro->prox = NULL;
    listaMaquina->qtMaquina = 0;
}

T_Maquina instanciarMaquina() {
    T_Maquina m = {.campo.qtCoxinha = 0,
                   .campo.qtPeixe = 0,
                   .campo.qtAlmondega = 0,
                   .campo.embalado = 0,
                   .campo.qtDescarteCoxinha = 0,
                   .campo.qtDescartePeixe = 0,
                   .campo.qtDescarteAlmondega = 0,
                   .campo.descartado = 0,
                   .campo.tempoFuncionando = 0,
                   .campo.tempoOcioso = 0,
                   .campo.horaFuncionamento = 0,
                   .campo.qtProduto = 0,
                   .campo.entrada = 1,
                   .campo.saida = 1,
                   .prox = NULL};

    return m;
}

void inserirMaquina(T_ListaMaquina *listaMaquina) {
    listaMaquina->ultimo->prox = (T_Maquina *) malloc(sizeof(T_Maquina));
    listaMaquina->ultimo = listaMaquina->ultimo->prox;
    listaMaquina->ultimo->campo = instanciarMaquina().campo;
    listaMaquina->ultimo->prox = NULL;
    listaMaquina->qtMaquina++;
}

void inserirProduto(const T_Produto p, T_Maquina *m) {
    if(m->campo.entrada % TAM_MAX + 1 == m->campo.saida)
        printf("[ WARNING ] - Fila de produtos cheia!\n");
    else {
        m->campo.filaProdutos[m->campo.entrada - 1] = p;
        m->campo.entrada = m->campo.entrada % TAM_MAX + 1;
        m->campo.qtProduto++;
    }
}

void retirarProduto(T_Maquina *m) {
    if(m->campo.saida == m->campo.entrada)
        printf("[ WARNING ] - Fila de produtos vazia!\n");
    else {
        m->campo.saida = m->campo.saida % TAM_MAX + 1;
        m->campo.qtProduto--;
    }
}

T_Produto instanciarCoxinha(const int instanteEntrada) {
    T_Produto p = {.tipo = 1,
                   .custoProducao = 0.80,
                   .precoAtacado = 1.45,
                   .tempoDeteoriacao = 50,
                   .instanteEntrada = instanteEntrada,
                   .tempoEmpacotamento = 18};

    return p;
}

T_Produto instanciarPeixe(const int instanteEntrada) {
    T_Produto p = {.tipo = 2,
                   .custoProducao = 0.70,
                   .precoAtacado = 2.00,
                   .tempoDeteoriacao = 20,
                   .instanteEntrada = instanteEntrada,
                   .tempoEmpacotamento = 12};

    return p;
}

T_Produto instanciarAlmondega(const int instanteEntrada) {
    T_Produto p = {.tipo = 3,
                   .custoProducao = 0.40,
                   .precoAtacado = 0.80,
                   .tempoDeteoriacao = 90,
                   .instanteEntrada = instanteEntrada,
                   .tempoEmpacotamento = 15};
    return p;
}

int empacotar(T_Maquina *m, const int tempo) {
    if(m->campo.qtProduto == 0) {
        m->campo.tempoOcioso++;
        return 0;
    }

    m->campo.tempoFuncionando++;

    /* Confere se o produto deteriorou */
    if(m->campo.filaProdutos[m->campo.saida - 1].instanteEntrada +
       m->campo.filaProdutos[m->campo.saida - 1].tempoDeteoriacao <= tempo)
    {
        m->campo.descartado++;

        switch(m->campo.filaProdutos[m->campo.saida - 1].tipo) {

        case 1:
            m->campo.qtDescarteCoxinha++;
            retirarProduto(m);
            return 1;

        case 2:
            m->campo.qtDescartePeixe++;
            retirarProduto(m);
            return 2;

        case 3:
            m->campo.qtDescarteAlmondega++;
            retirarProduto(m);
            return 3;
        }
    }
    /* Confere se o produto pode ser empacotado */
    else if( m->campo.filaProdutos[m->campo.saida - 1].instanteEntrada +
             m->campo.filaProdutos[m->campo.saida - 1].tempoEmpacotamento
             == tempo)
    {
        m->campo.embalado++;

        switch(m->campo.filaProdutos[m->campo.saida - 1].tipo) {

        case 1:
            m->campo.qtCoxinha++;
            retirarProduto(m);
            return 4;

        case 2:
            m->campo.qtPeixe++;
            retirarProduto(m);
            return 5;

        case 3:
            m->campo.qtAlmondega++;
            retirarProduto(m);
            return 6;
        }
    }
    return 7;
}

void atualizarEstatistica(T_Maquina *m, const int OP) {
    switch(OP) {

    case 0:
        m->campo.tempoOcioso++;
        break;

    case 1:
        m->campo.tempoFuncionando++;
        m->campo.qtDescarteCoxinha++;
        m->campo.descartado++;
        break;

    case 2:
        m->campo.tempoFuncionando++;
        m->campo.qtDescartePeixe++;
        m->campo.descartado++;
        break;

    case 3:
        m->campo.tempoFuncionando++;
        m->campo.qtDescarteAlmondega++;
        m->campo.descartado++;
        break;

    case 4:
        m->campo.tempoFuncionando++;
        m->campo.embalado++;
        m->campo.qtCoxinha++;
        break;

    case 5:
        m->campo.tempoFuncionando++;
        m->campo.embalado++;
        m->campo.qtPeixe++;
        break;

    case 6:
        m->campo.tempoFuncionando++;
        m->campo.embalado++;
        m->campo.qtAlmondega++;
        break;

    case 7:
        m->campo.tempoFuncionando++;
        break;
    }
}

void printEstatisticaMaquina(T_Maquina const m, const int i) {
    float totalPrejuizo = m.campo.qtDescarteAlmondega * 0.4 +
                          m.campo.qtDescarteCoxinha * 0.8 +
                          m.campo.qtDescartePeixe * 0.7;
    float totalLucro = m.campo.qtAlmondega * 0.4 +
                       m.campo.qtCoxinha * 0.65 +
                       m.campo.qtPeixe * 1.3;
    float saldo = totalLucro - totalPrejuizo - m.campo.horaFuncionamento * 22;

    printf("*_________________________________________________________________________*\n");
    printf("| MAQUINA %5d |  ALMONDEGA  |   COXINHA   | FILE DE PEIXE |    TOTAL    |\n", i);
    printf("| EMPACOTADO    | %11d | %11d | %13d | %11d |\n", m.campo.qtAlmondega,
           m.campo.qtCoxinha, m.campo.qtPeixe, m.campo.embalado);
    printf("| LUCRO R$      | %11.2f | %11.2f | %13.2f | %11.2f |\n",
           m.campo.qtAlmondega * 0.4, m.campo.qtCoxinha * 0.65, m.campo.qtPeixe * 1.3,
           totalLucro);
    printf("| DESCARTADO    | %11d | %11d | %13d | %11d |\n",m.campo.qtDescarteAlmondega,
           m.campo.qtDescarteCoxinha, m.campo.qtDescartePeixe, m.campo.descartado);
    printf("| PREJUIZO R$   | %11.2f | %11.2f | %13.2f | %11.2f |\n",
           m.campo.qtDescarteAlmondega * 0.4, m.campo.qtDescarteCoxinha * 0.8,
           m.campo.qtDescartePeixe * 0.7, totalPrejuizo);
    printf("| ************* |\n");
    printf("| CUSTO ENERGIA | %11d |\n", m.campo.horaFuncionamento * 22);
    printf("| TEMPO OCIOSO  | %11d |\n", m.campo.tempoOcioso);
    printf("| TEMPO ATIVO   | %11d |\n", m.campo.tempoFuncionando);
    printf("| SALDO         | %11.2f |\n", saldo);
}

void printEstatisticaDiaria(T_Maquina const m, float const saldo, float const energia,
                            float const lucroDiario, float const prejuizoDiario, const int dia) {
    printf("*_________________________________________________________________________*\n");
    printf("| DIA %4d      |  ALMONDEGA  |   COXINHA   | FILE DE PEIXE |    TOTAL    |\n", dia);
    printf("| EMPACOTADO    | %11d | %11d | %13d | %11d |\n", m.campo.qtAlmondega,
           m.campo.qtCoxinha, m.campo.qtPeixe, m.campo.embalado);
    printf("| LUCRO R$      | %11.2f | %11.2f | %13.2f | %11.2f |\n", m.campo.qtAlmondega * 0.4,
           m.campo.qtCoxinha * 0.65, m.campo.qtPeixe * 1.3, lucroDiario);
    printf("| DESCARTADO    | %11d | %11d | %13d | %11d |\n", m.campo.qtDescarteAlmondega,
           m.campo.qtDescarteCoxinha, m.campo.qtDescartePeixe, m.campo.descartado);
    printf("| PREJUIZO R$   | %11.2f | %11.2f | %13.2f | %11.2f |\n",
           m.campo.qtDescarteAlmondega * 0.4, m.campo.qtDescarteCoxinha * 0.8,
           m.campo.qtDescartePeixe * 0.7, prejuizoDiario);
    printf("| CUSTO ENERGIA | %11.2f |\n", energia);
    printf("| SALDO         | %11.2f |\n", saldo);
}

void resultadoFinal(T_Maquina const estatisticaFinal, const T_ListaMaquina listaMaquina, const int dia) {
    printf("\n\n####### RELATORIO FINAL #######\n\n");

    T_Maquina *AUX;
    int i = 1;

    for(AUX = listaMaquina.primeiro->prox, i = 1; AUX != NULL; AUX = AUX->prox, ++i)
        printEstatisticaMaquina(*AUX, i);

    printf("\n\n####### TOTAL #######\n\n");
    printEstatisticaMaquina(estatisticaFinal, 0);
    printf("\n\n####### RESULTADO DA SIMULACAO #######\n\n");
    printf("Lucro a partir do dia: %3d\n", dia);
    printf("Cada %3.2f dias uma maquina sera quitado\n", (float)dia/listaMaquina.qtMaquina);
}
