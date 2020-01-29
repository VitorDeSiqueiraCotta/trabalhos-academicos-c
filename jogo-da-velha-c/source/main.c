#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#ifdef _WIN32
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif

void limpaTelaPausa(void);
void drawTab(const char tab[]);
int check(const int tab[]);
int jogoPC(int tabLog[], const int player);
void movPC(int tab[], char tabPrint[], const char symbol);
void movPlayer(int tab[], char tabPrint[], const char symbol, const int value);

int main(void) {
    char FLAG;

    do {
        int tabLog[9] = {0,0,0,0,0,0,0,0,0};
        int OP;
        char tabPrint[9] = {'1','2','3','4','5','6','7','8','9'};
        char symbol;

        while(true) {
            setbuf(stdin, NULL);
            printf("Deseja ser O ou X? ");
            scanf("%c", &symbol);

            if(symbol == '0')
                symbol = 'O';

            symbol = toupper(symbol);

            if(symbol != 'O' && symbol != 'X') {
                printf("[ WARNING ] - Entrada invalida.\n");
                continue;
            }
            break;
        }

        while(true) {
            system(CLEAR);

            printf("[ MENU ]\n\n"
                   "1 - Singleplay\n"
                   "2 - Multiplay local\n"
                   "3 - Encerrar\n\n"
                   "OP: ");

            scanf("%d", &OP);
            setbuf(stdin, NULL);

            printf("\n");

            if(OP == 3) {
                printf("[ INFORM ] - Encerrando o programa.\n");
                getchar();
                return 0;
            }
            else if(OP != 1 && OP != 2) {
                printf("[ WARNING ] - Entrada invalida.\n");
                getchar();
                continue;
            }
            break;
        }

        for(int i = 0; i < 9 && check(tabLog) == 0; i++) {
            system(CLEAR);

            if(i % 2 == 0) {
                if( OP == 1)
                    movPC(tabLog, tabPrint, symbol == 'X' ? 'O' : 'X');
                else
                    movPlayer(tabLog, tabPrint, symbol == 'X' ? 'O' : 'X', 1);
            }
            else
                movPlayer(tabLog, tabPrint, symbol, -1);
        }

        system(CLEAR);
        drawTab(tabPrint);

        switch(check(tabLog)) {

        case 0:
            printf("[ INFORM ] - Empate.\n");
            break;

        case 1:
            printf("[ INFORM ] - Jogador %c venceu.\n", symbol == 'X' ? 'O' : 'X');
            break;

        case -1:
            printf("[ INFORM ] - Jogador %c venceu.\n", symbol == 'X' ? 'X' : 'O');
            break;
        }
        limpaTelaPausa();

        printf("Jogar novamente (S/N)? ");
        scanf("%c", &FLAG);
        system(CLEAR);
    }
    while(toupper(FLAG) == 'S');

    printf("[ INFORM ] - Encerrando o programa.\n");
    getchar();

    return EXIT_SUCCESS;
}

void limpaTelaPausa(void) {
    setbuf(stdin, NULL);
    printf("\n\nPressione ENTER para continuar...");
    getchar();
    system(CLEAR);
}

void drawTab(const char tab[]) {
    printf("      |      |\n");
    printf("  %c   |  %c   |  %c\n", tab[0], tab[1], tab[2]);
    printf("      |      |\n");
    printf("------+------+-----\n");
    printf("      |      |\n");
    printf("  %c   |  %c   |  %c\n", tab[3], tab[4], tab[5]);
    printf("      |      |\n");
    printf("------+------+-----\n");
    printf("      |      |\n");
    printf("  %c   |  %c   |  %c\n", tab[6], tab[7], tab[8]);
    printf("      |      |\n\n");
}

int check(const int tab[]) {
    int win[8][3] = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};

    for(int i = 0; i < 8; ++i)
        if(tab[win[i][0]] != 0 && tab[win[i][0]] == tab[win[i][1]] && tab[win[i][0]] == tab[win[i][2]])
            return tab[win[i][2]];

    return 0;
}

int jogoPC(int tabLog[], const int player) {
    if(check(tabLog) != 0)
        return check(tabLog) * player;

    int mov = -1;
    int pont = -2;

    for(int i = 0; i < 9; ++i) {
        if(tabLog[i] == 0) {
            tabLog[i] = player;

            int pontAtual = -jogoPC(tabLog, player * -1);

            if(pontAtual > pont) {
                pont = pontAtual;
                mov = i;
            }
            tabLog[i] = 0;
        }
    }

    if(mov == -1)
        return 0;

    return pont;
}

void movPC(int tab[], char tabPrint[], const char symbol) {
    int mov = -1;
    int score = -2;

    for(int i = 0; i < 9; ++i) {
        if(tab[i] == 0) {
            tab[i] = 1;

            int scoreTemp = -jogoPC(tab, -1);

            tab[i] = 0;

            if(scoreTemp > score) {
                score = scoreTemp;
                mov = i;
            }
        }
    }
    tab[mov] = 1;
    tabPrint[mov] = symbol;
}

void movPlayer(int tab[], char tabPrint[], const char symbol, const int value) {
    int mov = 0;

    while(true) {
        drawTab(tabPrint);
        printf("Partida %c \n\nDigite a posicao: ", symbol);

        if(scanf("%d", &mov) != 1 || 0 > --mov || mov > 8 || tab[mov] != 0) {
            printf("\n[ WARNING ] - Entrada invalida.\n");
            limpaTelaPausa();
            continue;
        }
        break;
    }
    tab[mov] = value;
    tabPrint[mov] = symbol;
}
