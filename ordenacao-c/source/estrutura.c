#include "estrutura.h"
#include "manipularArquivo.h"
#include "ordenacao.h"

StructEscola resgistro_vazio(void) {
    StructEscola temp =  {  .ID = -1,
                            .estado = "",
                            .municipio = "",
                            .rede = "",
                            .media_ciencias_natureza = 0.0,
                            .media_ciencias_humanas = 0.0,
                            .media_linguagem = 0.0,
                            .media_matematica = 0.0,
                            .media_redacao = 0.0};
    return temp;
}

StructArgv argumentos_vaizo(void) {
    StructArgv argumentos = {   .id = -1,
                                .diretorio = "",
                                .imprimir = "",
                                .tipoBusca = "",
                                .tipoOrdenacao = ""};
    return argumentos;
}

void imprimir_registro(const StructEscola registro) {
    printf("ID: %d\n", registro.ID);
    printf("Estado: %s\n", registro.estado);
    printf("Municipio: %s\n", registro.municipio);
    printf("Rede: %s\n", registro.rede);
    printf("Media Ciencias Natureza: %f\n", registro.media_ciencias_natureza);
    printf("Media Ciencias Humanas: %f\n", registro.media_ciencias_humanas);
    printf("Media Linguagem: %f\n", registro.media_linguagem);
    printf("Media Matematica: %f\n", registro.media_matematica);
    printf("Media Redacao: %f\n\n", registro.media_redacao);
}

void imprimir_todos_registros(const StructEscola *registros, const int qtRegistros) {
    for(int i = 0; i < qtRegistros; ++i)
        imprimir_registro(registros[i]);
}

void menu(StructEscola *registros, const int qtRegistros) {
    int OP = 0;
    int tamanho_busca = 0;

    do {
        printf("[ MENU ]\n\n"
               "0 - Sair\n"
               "1 - Cronometrar a ordenacao\n"
               "2 - Cronometrar a busca\n"
               "3 - Buscar por ID\n"
               "4 - Listar todos os registros\n\n"
               "-> ");
        if(scanf("%d", &OP) == 1) {
            limpar_tela();

            switch(OP) {

            case 0:
                printf("\n[ INFORM ] - Encerrando o programa.\n\n");
                break;

            case 1:
                printf("[ TIPO DE ORDENACAO ]\n\n"
                       "1 - Quick Sort\n"
                       "2 - Heap Sort\n"
                       "3 - Insertion Sort\n\n"
                       "-> ");
                if(scanf("%d", &OP) == 1) {
                    printf("\n");
                    carregar_arquivo_enem(registros, "dados-enem.txt");

                if(OP == 1)
                    temporizar_ordenacao(registros, qtRegistros, "qs");
                else if(OP == 2)
                    temporizar_ordenacao(registros, qtRegistros, "hs");
                else if(OP == 3)
                    temporizar_ordenacao(registros, qtRegistros, "is");
                }
                else
                    printf("\n\n[ ERROR ] - Entrada invalida.\n");

                break;

            case 2:
                printf("[ TIPO DE BUSCA ]\n\n"
                       "1 - Binaria\n"
                       "2 - Sequencial\n\n"
                       "-> ");
                scanf("%d", &OP);

                printf("\nQual quantidade de elementos buscados? ");
                scanf("%d", &tamanho_busca);

                printf("\n");

                if(OP == 1)
                    temporizar_busca(registros, qtRegistros, tamanho_busca, "bb");
                else if(OP == 2)
                    temporizar_busca(registros, qtRegistros, tamanho_busca, "bs");
                break;

            case 3:
                printf("\nQual ID do elemento buscado? ");
                scanf("%d", &OP);

                printf("\n");

                imprimir_registro(busca_binaria(registros, OP, qtRegistros));
                break;

            case 4:
                imprimir_todos_registros(registros, qtRegistros);
                break;

            default:
                printf("\n\n[ WARNING ] - Entrada [ %d ] invalida.\n", OP);
                break;
            }

        }
        else
           printf("\n\n[ ERROR ] - Entrada invalida.\n");

       limpar_tela_pausar();
    }
    while(OP != 0);
}

void carregar_argumentos(StructEscola *registros, const int qtRegistros, const int argc, const char *argv[]) {
    StructArgv argumentos = argumentos_vaizo();
    int posicaoArgumento = 1;

    if(strcmp("buscaenem", argv[posicaoArgumento]))
        return;

    ++posicaoArgumento;

    if(!strcmp("bb", argv[posicaoArgumento]))
        strcpy(argumentos.tipoBusca, argv[posicaoArgumento]);
    else if(!strcmp("bs", argv[posicaoArgumento]))
        strcpy(argumentos.tipoBusca, argv[posicaoArgumento]);
    else
        return;

    ++posicaoArgumento;

    if(!strcmp("-s", argv[posicaoArgumento])) {
        ++posicaoArgumento;

        if(!strcmp("qs", argv[posicaoArgumento]))
            strcpy(argumentos.tipoOrdenacao, argv[posicaoArgumento]);
        else if(!strcmp("hs", argv[posicaoArgumento]))
            strcpy(argumentos.tipoOrdenacao, argv[posicaoArgumento]);
        else if(!strcmp("is", argv[posicaoArgumento]))
            strcpy(argumentos.tipoOrdenacao, argv[posicaoArgumento]);
        else
            return;

        posicaoArgumento++;
    }

    if(!strcmp("-b", argv[posicaoArgumento])) {
        ++posicaoArgumento;
        strcpy(argumentos.diretorio, argv[posicaoArgumento]);
        ++posicaoArgumento;
    }
    else {
        argumentos.id = atoi(argv[posicaoArgumento]);
        posicaoArgumento++;
    }

    if(posicaoArgumento < argc && !strcmp("-p", argv[posicaoArgumento]))
        strcpy(argumentos.imprimir, argv[posicaoArgumento]);

    if(strcmp(argumentos.tipoOrdenacao, ""))
        temporizar_ordenacao(registros, qtRegistros, argumentos.tipoOrdenacao);

    if(strcmp(argumentos.diretorio,"")) {
        printf("Lendo os indices %s\n\n", argumentos.diretorio);
        carregar_arquivo_indice(registros, qtRegistros, argumentos);
    }
    else {
        if(!strcmp(argumentos.tipoBusca, "bb")) {
            printf("Busca binaria\n\n");
            imprimir_registro(busca_binaria(registros, argumentos.id, qtRegistros));
        }
        else if(!strcmp(argumentos.tipoBusca, "bs")) {
            printf("Busca sequencial\n\n");
            imprimir_registro(busca_sequencial(registros, argumentos.id, qtRegistros));
        }
    }
}

void limpar_tela(void) {
    system(CLEAR);
}

void limpar_tela_pausar(void) {
    setbuf(stdin, NULL);
    printf("\nPressione ENTER para continuar...");
    getchar();
    system(CLEAR);
}
