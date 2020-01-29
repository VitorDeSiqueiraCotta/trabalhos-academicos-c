#include "ordenacao.h"

StructEscola busca_sequencial(const StructEscola *registros, const int ID, const int qtRegistros) {
     for(int i = 0; i < qtRegistros; ++i)
        if(registros[i].ID == ID)
            return registros[i];

    printf("ID %d nao encontrado.\n", ID);

    return resgistro_vazio();
}

StructEscola busca_binaria(const StructEscola *registros, const int ID, const int qtRegistros) {
    int inferior = 0;
    int superior = qtRegistros - 1;
    int metade;

    while(inferior <= superior) {
        metade = (inferior + superior) / 2;
        if (ID == registros[metade].ID)
            return registros[metade];

        ID < registros[metade].ID ? (superior = metade - 1) : (inferior = metade + 1);
    }

    printf("So funciona se estiver ordenado.\n");
    printf("ID %d nao encontrado.\n", ID);

    return resgistro_vazio();
}

void temporizar_busca(const StructEscola *registros, const int qtRegistros, const int tamanho_busca, const char *tipoBusca) {
    srand(time(NULL));

    clock_t START = clock();

    if(!strcmp(tipoBusca, "bb"))
        for(int i = 0; i < tamanho_busca; ++i)
            busca_binaria(registros, 1 + rand() % qtRegistros, qtRegistros);
    else if(!strcmp(tipoBusca, "qs"))
        for(int i = 0; i < tamanho_busca; ++i)
            busca_sequencial(registros, 1 + rand() % qtRegistros, qtRegistros);

    clock_t END = clock();

    double TIME = ((double) (END - START)) / CLOCKS_PER_SEC;

    if(!strcmp(tipoBusca, "bb"))
        printf("\nBusca Binaria ");
    else if(!strcmp(tipoBusca, "qs"))
        printf("\nBusca Sequencial ");

    printf("\nElementos buscados [ %8d ] tempo de busca %lfs\n", tamanho_busca, TIME);
}

void quick_sort(StructEscola *registros, const int primeiro, const int ultimo){
    int i;
    int j;
    int pivo;
    StructEscola temp;

    if(primeiro < ultimo){
        pivo = primeiro;
        i = primeiro;
        j = ultimo;

        while(i < j) {
            while(registros[i].ID <= registros[pivo].ID && i < ultimo)
                ++i;

            while(registros[j].ID > registros[pivo].ID)
                --j;

            if(i < j) {
                temp = registros[i];
                registros[i] = registros[j];
                registros[j] = temp;
            }
        }
        temp = registros[pivo];
        registros[pivo] = registros[j];
        registros[j] = temp;
        quick_sort(registros, primeiro, j - 1);
        quick_sort(registros, j + 1, ultimo);
    }
}

void insertion_sort(StructEscola *registros, const int qtRegistros) {
    StructEscola temp;

    for(int i = 1, j; i < qtRegistros; ++i) {
        temp = registros[i];
        j = i - 1;

        while (j >= 0 && registros[j].ID > temp.ID) {
            registros[j + 1] = registros[j];
            j = j - 1;
        }
        registros[j + 1] = temp;
    }
}

void heap_sort(StructEscola *registros, int qtRegistros) {
    int i = qtRegistros / 2;
    int pai;
    int filho;
    StructEscola temp;

    while(true) {
        if (i > 0) {
            --i;
            temp = registros[i];
        }
        else {
            --qtRegistros;

            if (qtRegistros <= 0)
                return;

            temp = registros[qtRegistros];
            registros[qtRegistros] = registros[0];
        }

        pai = i;
        filho = i * 2 + 1;

        while(filho < qtRegistros) {
            if ((filho + 1 < qtRegistros) && (registros[filho + 1].ID > registros[filho].ID))
                ++filho;

            if (registros[filho].ID > temp.ID) {
                registros[pai] = registros[filho];
                pai = filho;
                filho = pai * 2 + 1;
            }
            else break;
        }
        registros[pai] = temp;
    }
}

void temporizar_ordenacao(StructEscola *registros, const int qtRegistros, const char *tipo) {
    clock_t START = clock();

    if(!strcmp(tipo, "qs"))
        quick_sort(registros, 0, qtRegistros - 1);
    else if(!strcmp(tipo, "hs"))
        heap_sort(registros, qtRegistros);
    else if(!strcmp(tipo, "is"))
        insertion_sort(registros, qtRegistros);
    else
        printf("[ ERROR ] - Ordenacao invalida.");

    clock_t END = clock();

    double TIME = ((double) (END - START)) / CLOCKS_PER_SEC;

    !strcmp(tipo, "qs") ? printf("Quick Sort ") :
    !strcmp(tipo, "hs") ? printf("Heap Sort ") :
    !strcmp(tipo, "is") ? printf("Insertion Sort ") :
    printf("[ ERROR ] - Ordenacao invalida.");

    printf("tempo para ordenar: %lfs\n\n", TIME);
}
