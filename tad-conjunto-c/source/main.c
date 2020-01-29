#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "TConj.h"

int main(void) {
    int OP;
    int elem;
    int pos;
    char conjunto;

    TConj a;
    TConj b;
    TConj resultado;

    inicializar(&a);
    inicializar(&b);
    inicializar(&resultado);

    do {
        printf("Conjunto A: ");
        print_conj(a);

        printf("Conjunto B: ");
        print_conj(b);

        printf("Conjunto Resultado: ");
        print_conj(resultado);

        printf("\n[ MENU ]\n\n"
               "0  - Sair\n"
               "1  - Inserir elemento\n"
               "2  - Inserir elemento aleatorios\n"
               "3  - Remover elemento\n"
               "4  - Uniao elemento\n"
               "5  - Intersecao elemento\n"
               "6  - Elemento exclusivo\n"
               "7  - Comparar conjuntos\n"
               "8  - Buscar elemento\n"
               "9  - Testar elemento\n"
               "10 - Alterar elemento\n\n"
               "-> ");

        scanf("%d", &OP);

        if(OP == 1 || OP == 2 || OP == 3 || OP == 6 || OP == 8 || OP == 9 || OP == 10) {
            setbuf(stdin, NULL);

            printf("\nConjunto A ou B? ");
            scanf("%c", &conjunto);

            conjunto = tolower(conjunto);

            if(conjunto != 'a' && conjunto != 'b') {
                printf("[ ERROR ] - Entrada %c invalida.\n", conjunto);
                continue;
            }

            if(OP == 1 || OP == 3 || OP == 9 || OP == 10) {
                printf("Insira elemento: ");
                scanf("%d", &elem);
            }

            if(OP == 8 || OP == 10) {
                printf("Insira a posicao: ");
                scanf("%d", &pos);
            }
        }

        switch(OP) {
        case 0:
            printf("\n[ INFORM ] - Encerrando o programa.\n");
            break;

        case 1:
            'a' == conjunto ? inserir_elemento(&a, elem) : inserir_elemento(&b, elem);
            break;

        case 2:
            'a' == conjunto ? inicializar(&a) : inicializar(&b);
            'a' == conjunto ? gerar_conjunto(&a) : gerar_conjunto(&b);
            break;

        case 3:
            'a' == conjunto ? remove_element(&a, elem) : inserir_elemento(&b, elem);
            break;

        case 4:
            resultado = uniao(a, b);
            break;

        case 5:
            resultado = inter(a, b);
            break;

        case 6:
            resultado = 'a' == conjunto ? subtrair(a, b) : subtrair(b, a);
            break;

        case 7:
            if(conj_iguais(a, b))
                printf("\n[ INFORM ] - Conjuntos iguais.\n");
            else
                printf("\n[ INFORM ] - Conjuntos diferentes.\n");

            break;

        case 8:
            if(('a' == conjunto ? get_elemento(a, pos, &elem) : get_elemento(b, pos, &elem)))
                printf("[ INFORM ] - Elemento obtido: %d.\n", elem);
            else
                printf("[ INFORM ] - Elemento na posica %d nao encontrado.\n", elem);

            break;

        case 9:
            if('a' == conjunto)
                pos = check_element(a, elem);
            else
                pos = check_element(b, elem);

            if(pos != -1)
                printf("[ INFORM ] - Elemento %d encontrado na posicao %d.\n", elem, pos);
            else
                printf("[ INFORM ] - Elemento %d nao encontrado.\n", elem);

            break;

        case 10:
            if('a' == conjunto) {
                if(set_elemento(&a, elem, pos))
                    printf("[ INFORM ] - Alterado com sucesso.\n");
                else
                    printf("[ INFORM ] - Elemento nao alterado.\n");
            }
            else {
                if(set_elemento(&b, elem, pos))
                    printf("[ INFORM ] - Alterado com sucesso.\n");
                else
                    printf("[ INFORM ] - Elemento nao alterado.\n");
            }
            break;

        default:
            printf("[ ERROR ] - Entrada %c invalida.\n", OP);
        }

        limpaTelaPausa();
    }
    while(OP != 0);

    return EXIT_SUCCESS;
}
