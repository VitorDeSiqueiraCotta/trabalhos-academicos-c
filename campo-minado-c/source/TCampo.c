#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "TCampo.h"

void inicializar(TCampo *tabuleiro) {
    if(tabuleiro->n <= 0 || tabuleiro->m <= 0 || tabuleiro->n > 100 || tabuleiro->m > 100) {
        printf("\n[ WARNING ] - Insira valores entre 1 e 100.\n");
        return;
    }

    tabuleiro->TAB = (TQuadrado **) malloc (tabuleiro->n * sizeof(TQuadrado *));

    if(tabuleiro->TAB == NULL) {
        printf("\n[ ERROR ] - Falha na alocao do tabuleiro.\n");
        return;
    }

    for(int i = 0; i < tabuleiro->n; ++i) {
        tabuleiro->TAB[i] = (TQuadrado*) malloc (tabuleiro->m * sizeof(TQuadrado));

        if(tabuleiro->TAB[i] == NULL) {
            printf("\n[ ERROR ] - Falha na alocao de linha do tabuleiro.\n");
            return;
        }
    }

    for(int i = 0; i < tabuleiro->n; ++i) {
        for(int j = 0; j < tabuleiro->m; ++j) {
            tabuleiro->TAB[i][j].visitado = -2;
            tabuleiro->TAB[i][j].zona = '.';
        }
    }
}

void imprimir(const TCampo tabuleiro) {
    for(int i = 0; i < tabuleiro.n; ++i, printf("\n"))
        for(int j = 0; j < tabuleiro.m; ++j)
            printf("%c ", tabuleiro.TAB[i][j].zona);
}

void imprimirVisitado(TCampo tabuleiro) {
    for(int i = 0; i < tabuleiro.n; ++i) {
        for(int j = 0; j < tabuleiro.m; ++j) {
            if(tabuleiro.TAB[i][j].visitado == -2)
                printf(". ");
            else
                printf("%d ", bombas_adjacentes(&tabuleiro, i, j));
        }
        printf("\n");
    }
}

void imprimirTeste(TCampo A) {
    for(int i = 0; i < A.n; ++i)  {
        for(int j = 0; j < A.m; ++j) {
            if(A.TAB[i][j].visitado == -2)
                printf("%c ", A.TAB[i][j].zona);
            else
                printf("%d ", bombas_adjacentes(&A, i, j));
        }
        printf("\n");
    }
}

int validar_posicao(const int n, const int m, const int x, const int y) {
    if(x < 0 || y < 0) {
        printf("\n[ WARNING ] - Tem que ser maior ou igual a 0.\n");
        return 0;
    }

    if(x > n) {
        printf("\n[ WARNING ] - LINHA %d invalido. \nValores aceitos 0-%d\n", x, n);
        return 0;
    }

    if(y > m) {
        printf("\n[ WARNING ] - COLUNA %d invalido. \nValores aceitos 0-%d\n", y, m);
        return 0;
    }
    return 1;
}

int validar_bomba_adjacente(const TCampo tabuleiro, const int x, const int y) {
    if(x < 0 || y < 0 || x > tabuleiro.n - 1 || y > tabuleiro.m - 1 || tabuleiro.TAB[x][y].zona != '*')
        return 0;
    return 1;
}

int inserir_bomba(TCampo *tabuleiro, const int posx, const int posy) {
    if(!validar_posicao(tabuleiro->n - 1, tabuleiro->m - 1, posx, posy))
        return 0;
    else if(tabuleiro->TAB[posx][posy].zona == '*') {
        printf("\n[ WARNING ] - Ja existe bomba nesta posicao.\n");
        return 0;
    }

    tabuleiro->TAB[posx][posy].zona = '*';  /* Bomba inserida. */
    return 1;
}

int visitar_quadrado(TCampo *tabuleiro, const int posx, const int posy) {
    if(!validar_posicao(tabuleiro->n - 1, tabuleiro->m - 1, posx, posy))  {
        return -1;
    }
    else if(tabuleiro->TAB[posx][posy].zona != '*') {
        tabuleiro->TAB[posx][posy].visitado = 1;
        return 1;
    }

    tabuleiro->TAB[posx][posy].visitado = 0;
    return 0;
}

int bombas_adjacentes(TCampo *tabuleiro, const int posx, const int posy) {
    int i = 0;

    if(validar_bomba_adjacente(*tabuleiro, posx, posy - 1))
        ++i;
    if(validar_bomba_adjacente(*tabuleiro, posx - 1, posy))
        ++i;
    if(validar_bomba_adjacente(*tabuleiro, posx - 1, posy + 1))
        ++i;
    if(validar_bomba_adjacente(*tabuleiro, posx - 1, posy - 1))
        ++i;
    if(validar_bomba_adjacente(*tabuleiro, posx, posy + 1))
        ++i;
    if(validar_bomba_adjacente(*tabuleiro, posx + 1, posy))
        ++i;
    if(validar_bomba_adjacente(*tabuleiro, posx + 1, posy + 1))
        ++i;
    if(validar_bomba_adjacente(*tabuleiro, posx + 1, posy - 1))
        ++i;

    if(tabuleiro->TAB[posx][posy].zona != '*')
        tabuleiro->TAB[posx][posy].zona = i + '0'; /* Converte inteiro em caractere */

    return i;
}

void solucionar_campo(TCampo tabuleiro) {
    for(int i = 0; i < tabuleiro.n; ++i)
        for(int j = 0; j < tabuleiro.m; ++j)
            bombas_adjacentes(&tabuleiro, i, j);
    imprimir(tabuleiro);
}

TCampo gerar_campo_bombas(const int n, const int m, const int qt_bombas) {
    srand(time(NULL));

    int x = 0;
    int y = 0;

    TCampo temp = {.n = n, .m = m};
    inicializar(&temp);

    if(qt_bombas < 0 && qt_bombas > 1) {
        printf("\n[ WARNING ] - Valor invalido, insira o valor entre 0 ate 1.\n");
        return temp;
    }

    for(int i = 0; i < qt_bombas; ++i)  {
        x = rand() % n;
        y = rand() % m;

        if(temp.TAB[x][y].zona == '*') {
            --i;
            continue;
        }
        temp.TAB[x][y].zona = '*';
    }
    return temp;
}

void freeTAB(TCampo *tabuleiro) {
    if(tabuleiro->TAB == NULL) {
        printf("\n[ WARNING ] - Tabuleiro esta NULO.\n");
        return;
    }

    for(int i = 0; i < tabuleiro->n; ++i) {
        free(tabuleiro->TAB[i]);
        tabuleiro->TAB[i] = NULL;
    }

    free(tabuleiro->TAB);
    tabuleiro->TAB = NULL;
}

int qtRodadas(const TCampo tabuleiro) {
    int qt = 0;
    for(int i = 0; i < tabuleiro.n; ++i)
        for(int j = 0; j < tabuleiro.m; ++j)
            if(tabuleiro.TAB[i][j].zona == '.')
                ++qt;
    return qt;
}

TCampo menu(int *flagTeste) {
    int OP = 0;

    system(CLEAR);

    while(1) {
        printf("Jogo campo Minado\n\n"
               "Qual nivel de dificuldade que deseja jogar?\n\n"
               "[ 1 ] - FACIL\n"
               "[ 2 ] - MEDIO\n"
               "[ 3 ] - DIFICIL\n"
               "[ 4 ] - TESTE\n\n"
               "OP: ");

        if(scanf("%d", &OP) != 1) {
            printf("\n[ WARNING ] - Insira valores validos.\n\n");
            limpaTelaPausa();
            continue;
        }

        system(CLEAR);

        switch(OP) {

        case 1:
            return gerar_campo_bombas(4, 4, 4);

        case 2:
            return gerar_campo_bombas(4, 4, 6);

        case 3:
            return gerar_campo_bombas(5, 5, 8);

        case 4:
            *flagTeste = 1;
            return gerar_campo_bombas(5, 5, 6);

        default:
            printf("\n[ WARNING ] - Entrada [ %d ] invalida. Valores aceitos "
                   "entre 1 e 4.\n", OP);
            limpaTelaPausa();
            break;
        }
    }
}

void partida(TCampo tabuleiro, const int rodadas, const int flagTeste) {
    int posx;
    int posy;

    for(int i = 0; ; ++i, posx = -1, posy = -1) {
        printf("Rodada: %d\n\n", i + 1);

        if(flagTeste == 0)
            imprimirVisitado(tabuleiro);
        else if(flagTeste == 1)
            imprimirTeste(tabuleiro);

        printf("\nValores validos para linha entre 0 a %d\n"
               "Valores validos para coluna entre 0 a %d\n\n\n"
               "Linha: ", tabuleiro.n - 1, tabuleiro.m -1);

        if(scanf("%d", &posx) != 1 || 0 > posx || posx >= tabuleiro.n) {
            printf("\n[ WARNING ] - Insira valores validos.\n\n");
            --i;
            limpaTelaPausa();
            continue;
        }

        printf("Coluna: ");

        if(scanf("%d", &posy) != 1 || 0 > posy || posy >= tabuleiro.m) {
            printf("\n[ WARNING ] - Insira valores validos.\n\n");
            --i;
            limpaTelaPausa();
            continue;
        }

        setbuf(stdin, NULL);

        if(tabuleiro.TAB[posx][posy].visitado != -2) {
            printf("\n\n[ WARNING ] - Quadrado ja foi visitado!\n\n");
            --i;
            getchar();
            system(CLEAR);
            continue;
        }

        if(visitar_quadrado(&tabuleiro, posx, posy) == 0) {
            printf("\n\n[ WARNING ] - A bomba explodiu!\n\n"
                   "A solucao era:\n\n");
            solucionar_campo(tabuleiro);
            break;
        }

        if(i + 1 == rodadas) {
            printf("\nParabens, voce venceu!\n\n");
            solucionar_campo(tabuleiro);
            break;
        }
        system(CLEAR);
    }
    limpaTelaPausa();
}

void limpaTelaPausa(void) {
    setbuf(stdin, NULL);
    printf("\n\nPressione ENTER para continuar...");
    getchar();
    system(CLEAR);
}
